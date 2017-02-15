using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Adaptive.Schema.Net;
using AC = Adaptive.Schema.Net;

namespace Adaptive.Renderers
{
    public partial class AdaptiveXamlRenderer
    {
        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="card"></param>
        /// <returns></returns>
        public virtual UIElement Render(AdaptiveCard card)
        {
            var grid = new Grid();
            grid.Style = this.GetStyle("Adaptive.Card");
            if (card.BackgroundImage != null)
            {
                Uri uri = new Uri(card.BackgroundImage);
                grid.Background = new ImageBrush(new BitmapImage(uri));
            }
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            var inputControls = new List<FrameworkElement>();
            _addContainerElements(grid, card.Body, card.Actions, inputControls);
            return grid;
        }

        private void _addContainerElements(Grid grid, List<CardItem> elements, List<ActionBase> actions, List<FrameworkElement> inputControls)
        {
            bool hasActions = actions != null && actions.Any();
            if (hasActions)
            {
                // collect our input controls
                inputControls = new List<FrameworkElement>();
            }

            foreach (var cardElement in elements)
            {
                // each element has a row
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                UIElement uiElement = _renderCardElement(cardElement, inputControls);
                Grid.SetRow(uiElement, grid.RowDefinitions.Count - 1);
                Grid.SetColumnSpan(uiElement, 2);

                // if we have input 
                if (cardElement is Input)
                {
                    var input = cardElement as Input;
                    // and a title                    
                    if (input.Title != null)
                    {
                        // Add input title as column[0] peer to input element
                        // this is so all input labels line up nicely
                        var uiTitle = new WPF.TextBlock() { Text = input.Title };
                        uiTitle.Style = this.GetStyle("Adaptive.Input.Title");
                        Grid.SetRow(uiTitle, grid.RowDefinitions.Count - 1);
                        Grid.SetColumn(uiElement, 1);
                        Grid.SetColumnSpan(uiElement, 1);
                        grid.Children.Add(uiTitle);
                    }
                }
                grid.Children.Add(uiElement);
            }

            if (hasActions)
            {
                var uiActionBar = new UniformGrid();
                uiActionBar.Rows = 1;
                uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
                uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

                int iCol = 0;
                foreach (var action in actions)
                {
                    // add actions
                    var uiAction = _renderAction(action, inputControls);
                    Grid.SetColumn(uiAction, iCol++);
                    uiActionBar.Children.Add(uiAction);
                }
                uiActionBar.Style = this.GetStyle("Adaptive.Actions");
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiActionBar, grid.RowDefinitions.Count - 1);
                Grid.SetColumnSpan(uiActionBar, 2);
                grid.Children.Add(uiActionBar);
            }
        }

        /// <summary>
        /// Unknown element based on type
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
        private UIElement _renderCardElement(CardItem element, List<FrameworkElement> inputControls)
        {
            if (element is ColumnSet)
            {
                return Render(element as ColumnSet, inputControls);
            }
            else if (element is Column)
            {
                return Render(element as Container, inputControls);
            }
            else if (element is ImageSet)
            {
                return Render(element as ImageSet);
            }
            else if (element is FactSet)
            {
                return Render(element as FactSet);
            }
            else if (element is AC.TextBlock)
            {
                return Render(element as AC.TextBlock);
            }
            else if (element is TextInput)
            {
                return Render(element as TextInput, inputControls);
            }
            else if (element is ChoiceInput)
            {
                return Render(element as ChoiceInput, inputControls);
            }
            else if (element is AC.Image)
            {
                return Render(element as AC.Image);
            }
            else if (element is Container)
            {
                return Render(element as Container, inputControls);
            }
            else
                Debug.Print($"Unknown Element type {element.GetType().Name}");
            // return place holder
            return new Grid();
        }


        /// <summary>
        /// Container
        /// </summary>
        /// <param name="container"></param>
        /// <returns></returns>
        protected virtual UIElement Render(Container container, List<FrameworkElement> inputControls)
        {
            var uiContainer = new Grid();
            uiContainer.Style = this.GetStyle("Adaptive.Container");

            if (container.Separation == SeparationStyle.Before || container.Separation == SeparationStyle.Both)
                _addSeperator(uiContainer);

            _addContainerElements(uiContainer, container.Items, container.Actions, inputControls);

            if (container.Separation == SeparationStyle.After || container.Separation == Adaptive.Schema.Net.SeparationStyle.Both)
                _addSeperator(uiContainer);

            if (container.SelectAction != null)
            {
                return _renderAction(container.SelectAction, inputControls, uiContainer);
            }

            return uiContainer;
        }

        private void _addSeperator(Grid uiContainer)
        {
            var sep = new Separator();
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(sep, uiContainer.RowDefinitions.Count - 1);
            Grid.SetColumnSpan(sep, 2);
            sep.Style = this.GetStyle("Adaptive.Separator");
            uiContainer.Children.Add(sep);
        }

        /// <summary>
        /// ColumnSet
        /// </summary>
        /// <param name="columnSet"></param>
        /// <returns></returns>
        protected virtual UIElement Render(ColumnSet columnSet, List<FrameworkElement> inputControls)
        {
            var uiColumnSet = new Grid();
            uiColumnSet.Style = this.GetStyle("Adaptive.ColumnSet");

            int iCol = 0;
            foreach (var column in columnSet.Columns)
            {
                UIElement uiElement = Render(column, inputControls);

                // do some sizing magic using the magic GridUnitType.Star
                var size = column.Size?.ToLower();
                if (size == ColumnSize.Stretch.ToLower())
                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                else if (size == ColumnSize.Auto.ToLower())
                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                else
                {
                    double val;
                    if (double.TryParse(size, out val))
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) });
                    else
                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                }

                Grid.SetColumn(uiElement, iCol++);
                uiColumnSet.Children.Add(uiElement);
            }

            return uiColumnSet;
        }

        /// <summary>
        /// FactSet
        /// </summary>
        /// <param name="factSet"></param>
        /// <returns></returns>
        protected virtual UIElement Render(FactSet factSet)
        {
            var uiFactSet = new Grid();
            // grid.Margin = this.Theme.FactSetMargins;
            uiFactSet.Style = this.GetStyle("Adaptive.FactSet");

            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            int iRow = 0;
            foreach (var fact in factSet.Facts)
            {
                Tuple<UIElement, UIElement> uiElements = Render(fact as Fact);
                uiFactSet.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                Grid.SetColumn(uiElements.Item1, 0);
                Grid.SetRow(uiElements.Item1, iRow);
                uiFactSet.Children.Add(uiElements.Item1);

                Grid.SetColumn(uiElements.Item2, 1);
                Grid.SetRow(uiElements.Item2, iRow++);
                uiFactSet.Children.Add(uiElements.Item2);
            }
            return uiFactSet;
        }

        /// <summary>
        /// Fact
        /// </summary>
        /// <param name="fact"></param>
        /// <returns></returns>
        protected virtual Tuple<UIElement, UIElement> Render(Fact fact)
        {
            return new Tuple<UIElement, UIElement>(new WPF.TextBlock()
            {
                Text = fact.Name,
                Style = this.GetStyle("Adaptive.Fact.Name")
            },
            new WPF.TextBlock()
            {
                Text = fact.Value,
                Style = this.GetStyle("Adaptive.Fact.Value")
            });
        }

        /// <summary>
        /// ImageGallery
        /// </summary>
        /// <param name="imageGallery"></param>
        /// <returns></returns>
        protected virtual UIElement Render(ImageSet imageGallery)
        {
            var uiGallery = new ListBox();
            uiGallery.Style = this.GetStyle("Adaptive.ImageGallery");

            ScrollViewer.SetHorizontalScrollBarVisibility(uiGallery, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(WrapPanel));
            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiGallery.ItemsPanel = itemsPanelTemplate;

            foreach (var image in imageGallery.Images)
            {
                if (imageGallery.Size != null)
                    image.Size = imageGallery.Size;
                var uiImage = Render(image);
                uiGallery.Items.Add(uiImage);
            }
            return uiGallery;
        }
    }
}