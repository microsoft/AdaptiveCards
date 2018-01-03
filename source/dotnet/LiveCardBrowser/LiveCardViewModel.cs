using AdaptiveCards;
using AdaptiveCards.Rendering.Wpf;
using LiveCardAPI;
using LiveCardClient;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Threading;

namespace LiveCardBrowser
{
    public class LiveCardViewModel : ObservableObject
    {
        private AdaptiveElementMemory domChanges = new AdaptiveElementMemory();
        private AdaptiveCardRenderer renderer;
        private Dispatcher dispatcher;
        private Grid grid = new Grid();

        public LiveCardViewModel(Dispatcher dispatcher, ResourceDictionary resources)
        {
            this.dispatcher = dispatcher;
            renderer = new AdaptiveCardRenderer()
            {
                Resources = resources
            };
        }

        private string url;
        public string Url { get { return url; } set { url = value; Notify(); } }


        private LiveCard liveCard;
        public LiveCard LiveCard
        {
            get { return liveCard; }
            set
            {
                liveCard = value;
                BindEvents();
                RenderedAdaptiveCard renderedCard = renderer.RenderCard(liveCard.Card);
                this.NativeCard = renderedCard.FrameworkElement;
                Notify();
            }
        }

        FrameworkElement nativeCard;
        public FrameworkElement NativeCard
        {
            get { return nativeCard; }
            protected set
            {
                nativeCard = value;
                Notify();
            }
        }


        private void BindEvents()
        {
            if (domChanges.UnProcessed(this.LiveCard.Card))
            {
                this.LiveCard.Card.PropertyChanged += Card_PropertyChanged;
                this.LiveCard.Card.Body.CollectionChanged += Body_CollectionChanged;
                domChanges.MarkProcessed(this.LiveCard.Card);
            }

            foreach (var element in this.LiveCard.Card.GetAllElements().Where(item => domChanges.UnProcessed(item)))
            {
                domChanges.MarkProcessed(element);
                element.PropertyChanged += Element_PropertyChanged;

                if (element is AdaptiveContainer)
                {
                    AdaptiveContainer container = element as AdaptiveContainer;
                    container.Items.CollectionChanged += Items_CollectionChanged; ;
                }
                else if (element is AdaptiveColumnSet)
                {
                    AdaptiveColumnSet columnSet = element as AdaptiveColumnSet;
                    columnSet.Columns.CollectionChanged += Columns_CollectionChanged; ;
                }
            }
        }

        private void Card_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            if (e.PropertyName == "Body")
                this.LiveCard.Card.Body.CollectionChanged += Body_CollectionChanged;

            BindEvents();

            this.dispatcher.Invoke(() =>
            {
                RenderedAdaptiveCard renderedCard = renderer.RenderCard(liveCard.Card);
                this.NativeCard = renderedCard.FrameworkElement;
            });
        }

        /// <summary>
        /// send property changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Element_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            this.dispatcher.Invoke(() =>
            {
                // render element and replace in element tree
                // TODO add logic to keep focus and input state
                if (sender is AdaptiveElement)
                {
                    AdaptiveElement element = (AdaptiveElement)sender;
                    _updateNativeElement(element);
                }
                else if (sender is AdaptiveCard)
                {
                    RenderedAdaptiveCard renderedCard = renderer.RenderCard(liveCard.Card);
                    this.NativeCard = renderedCard.FrameworkElement;
                }
            });
        }

        private void _updateNativeElement(AdaptiveElement element)
        {

            var oldUiElement = (FrameworkElement)this.NativeCard.FindName(element.Id);
            var parentUiElement = VisualTreeHelper.GetParent(oldUiElement);
            var nameScope = GetNameScope(oldUiElement);
            var newUiElement = renderer.RenderElement(nameScope, element);

            // patch up names
            if (newUiElement.Name != null)
            {
                try { nameScope.UnregisterName(newUiElement.Name); } catch { }
                try { nameScope.RegisterName(newUiElement.Name, newUiElement); } catch { }
            }


            if (parentUiElement is ContentControl)
            {
                ContentControl cc = (ContentControl)parentUiElement;
                cc.Content = newUiElement;
            }
            else if (parentUiElement is Panel)
            {
                Panel panel = (Panel)parentUiElement;
                var index = panel.Children.IndexOf(oldUiElement);
                // transfer grid properties
                Grid.SetRow(newUiElement, Grid.GetRow(oldUiElement));
                Grid.SetRowSpan(newUiElement, Grid.GetRowSpan(oldUiElement));
                Grid.SetColumn(newUiElement, Grid.GetColumn(oldUiElement));
                Grid.SetColumnSpan(newUiElement, Grid.GetColumnSpan(oldUiElement));
                newUiElement.Margin = oldUiElement.Margin;

                panel.Children.RemoveAt(index);
                panel.Children.Insert(index, newUiElement);
            }
            else
                throw new Exception("Unknown parent type");
        }

        private static INameScope GetNameScope(UIElement oldElement)
        {
            var anscestor = (DependencyObject)oldElement;
            INameScope ns;
            do
            {
                anscestor = VisualTreeHelper.GetParent(anscestor);
                ns = NameScope.GetNameScope(anscestor);
            } while (ns == null && anscestor != null);
            return ns;
        }

        /// <summary>
        /// send collection changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Items_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            this.dispatcher.Invoke(() =>
            {
                // render element and replace in element tree
                // special logic to keep focus and input state
                // TODO optomize this
                var container = this.LiveCard.Card.GetAllElements()
                    .Where(el => el is AdaptiveContainer)
                    .Cast<AdaptiveContainer>()
                    .Where(c => c.Items == sender)
                    .FirstOrDefault();

                if (container != null)
                    processCollectionChange(container.Id, e);
            });

        }


        /// <summary>
        /// Send collection changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Body_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            this.dispatcher.Invoke(() =>
            {
                // TODO this is not doing cards correctly, will only work for root card and needs to be mo better
                processCollectionChange(this.LiveCard.Card.Id, e);
            });
        }

        /// <summary>
        /// Send collection changes to client
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Columns_CollectionChanged(object sender, NotifyCollectionChangedEventArgs e)
        {
            this.dispatcher.Invoke(() =>
            {
                // TODO optomize this
                var columnSet = this.LiveCard.Card.GetAllElements()
                    .Where(el => el is AdaptiveColumnSet)
                    .Cast<AdaptiveColumnSet>()
                    .Where(cs => cs.Columns == sender)
                    .FirstOrDefault();
                if (columnSet != null)
                    processCollectionChange(columnSet.Id, e);
            });
        }

        private void processCollectionChange(string containerId, NotifyCollectionChangedEventArgs e)
        {
            BindEvents();
            if (this.LiveCard.Card.TryGetElementById(containerId, out AdaptiveTypedElement sender))
            {
                if (sender is AdaptiveElement)
                {
                    AdaptiveElement element = (AdaptiveElement)sender;
                    _updateNativeElement(element);
                }
                else if (sender is AdaptiveCard)
                {
                    RenderedAdaptiveCard renderedCard = renderer.RenderCard(liveCard.Card);
                    this.NativeCard = renderedCard.FrameworkElement;
                }
            }

            ////FrameworkElement nativeCollection = this.NativeCard.FindName(containerId);
            //switch (e.Action)
            //{
            //    case NotifyCollectionChangedAction.Add:
            //        await this.Client.AddElements(containerId, e.NewStartingIndex, e.NewItems.Cast<AdaptiveElement>().ToArray());
            //        break;
            //    case NotifyCollectionChangedAction.Remove:
            //        await this.Client.RemoveElements(containerId, e.OldItems.Cast<AdaptiveElement>().Select(it => it.Id).ToArray());
            //        break;
            //    case NotifyCollectionChangedAction.Replace:
            //        await this.Client.ReplaceElements(containerId, e.NewItems.Cast<AdaptiveElement>().ToArray());
            //        break;
            //    case NotifyCollectionChangedAction.Reset:
            //        await this.Client.Reset(containerId);
            //        break;
            //    case NotifyCollectionChangedAction.Move:
            //        //TODO
            //        break;
            //}
        }
    }
}
