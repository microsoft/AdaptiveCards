//using System;
//using System.Collections.Generic;
//using System.Linq;
//using System.Windows;
//using System.Windows.Controls;
//using WPF = System.Windows.Controls;
//using System.Windows.Controls.Primitives;
//using System.Windows.Media;
//using System.Windows.Media.Imaging;

//namespace Adaptive
//{
//    public partial class AdaptiveCard
//    {
//        /// <summary>
//        /// AdaptiveCard
//        /// </summary>
//        /// <param name="card"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var grid = new Grid();
//            grid.Style = context.GetStyle("Adaptive.Card");
//            if (this.BackgroundImage != null)
//            {
//                Uri uri = new Uri(this.BackgroundImage);
//                grid.Background = new ImageBrush(new BitmapImage(uri));
//            }
//            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

//            var inputControls = new List<FrameworkElement>();
//            Container.AddContainerElements(grid, this.Body, this.Actions, context);
//            return grid;
//        }
//    }

//    public partial class Container
//    {
//        public static void AddContainerElements(Grid grid, List<CardElement> elements, List<ActionBase> actions, RenderContext context)
//        {
//            bool hasActions = actions != null && actions.Any();
//            if (hasActions)
//            {
//                // collect our input controls
//                context.InputControls = new List<FrameworkElement>();
//            }

//            foreach (var cardElement in elements)
//            {
//                // each element has a row
//                FrameworkElement uiElement = cardElement.Render(context);
//                if (cardElement is Container && grid.RowDefinitions.Count > 0)
//                {
//                    Container container = (Container)cardElement;
//                    if (container.StartGroup == true)
//                    {
//                        var sep = new Separator();
//                        grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
//                        Grid.SetRow(sep, grid.RowDefinitions.Count - 1);
//                        sep.Style = context.GetStyle("Adaptive.Separator");
//                        grid.Children.Add(sep);
//                    }
//                }
//                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
//                Grid.SetRow(uiElement, grid.RowDefinitions.Count - 1);
//                grid.Children.Add(uiElement);
//            }

//            if (hasActions)
//            {
//                var uiActionBar = new UniformGrid();
//                uiActionBar.Rows = 1;
//                uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
//                uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

//                int iCol = 0;
//                foreach (var action in actions)
//                {
//                    // add actions
//                    var uiAction = action.Render(context);
//                    Grid.SetColumn(uiAction, iCol++);
//                    uiActionBar.Children.Add(uiAction);
//                }
//                uiActionBar.Style = context.GetStyle("Adaptive.Actions");
//                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
//                Grid.SetRow(uiActionBar, grid.RowDefinitions.Count - 1);
//                grid.Children.Add(uiActionBar);
//            }
//        }


//        /// <summary>
//        /// Container
//        /// </summary>
//        /// <param name="container"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiContainer = new Grid();
//            uiContainer.Style = context.GetStyle("Adaptive.Container");

//            Container.AddContainerElements(uiContainer, this.Items, this.Actions, context);

//            if (this.SelectAction != null)
//            {
//                var uiButton = (Button)this.SelectAction.Render(context.NewActionContext());
//                uiButton.Content = uiContainer;
//                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
//                return uiButton;
//            }

//            return uiContainer;
//        }

//    }


//    public partial class ColumnSet
//    {

//        /// <summary>
//        /// ColumnSet
//        /// </summary>
//        /// <param name="columnSet"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiColumnSet = new Grid();
//            uiColumnSet.Style = context.GetStyle("Adaptive.ColumnSet");

//            int iCol = 0;
//            foreach (var column in this.Columns)
//            {
//                FrameworkElement uiElement = column.Render(context);

//                // do some sizing magic using the magic GridUnitType.Star
//                var size = column.Size?.ToLower();
//                if (size == ColumnSize.Stretch.ToLower())
//                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
//                else if (size == ColumnSize.Auto.ToLower())
//                    uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
//                else
//                {
//                    double val;
//                    if (double.TryParse(size, out val))
//                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) });
//                    else
//                        uiColumnSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
//                }

//                Grid.SetColumn(uiElement, iCol++);
//                uiColumnSet.Children.Add(uiElement);
//            }

//            return uiColumnSet;
//        }
//    }


//    public partial class FactSet
//    {
//        /// <summary>
//        /// FactSet
//        /// </summary>
//        /// <param name="factSet"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiFactSet = new Grid();
//            // grid.Margin = this.Theme.FactSetMargins;
//            uiFactSet.Style = context.GetStyle("Adaptive.FactSet");

//            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
//            uiFactSet.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
//            int iRow = 0;
//            foreach (var fact in this.Facts)
//            {
//                Tuple<FrameworkElement, FrameworkElement> uiElements = fact.Render(context);
//                uiFactSet.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

//                Grid.SetColumn(uiElements.Item1, 0);
//                Grid.SetRow(uiElements.Item1, iRow);
//                uiFactSet.Children.Add(uiElements.Item1);

//                Grid.SetColumn(uiElements.Item2, 1);
//                Grid.SetRow(uiElements.Item2, iRow++);
//                uiFactSet.Children.Add(uiElements.Item2);
//            }
//            return uiFactSet;
//        }
//    }

//    public partial class Fact
//    {
//        /// <summary>
//        /// Fact
//        /// </summary>
//        /// <param name="fact"></param>
//        /// <returns></returns>
//        public virtual Tuple<FrameworkElement, FrameworkElement> Render(RenderContext context)
//        {
//            return new Tuple<FrameworkElement, FrameworkElement>(new WPF.TextBlock()
//            {
//                Text = this.Title,
//                Style = context.GetStyle("Adaptive.Fact.Name")
//            },
//            new WPF.TextBlock()
//            {
//                Text = this.Value,
//                Style = context.GetStyle("Adaptive.Fact.Value")
//            });
//        }
//    }

//    public partial class ImageSet
//    {

//        /// <summary>
//        /// ImageGallery
//        /// </summary>
//        /// <param name="imageGallery"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiGallery = new ListBox();
//            uiGallery.Style = context.GetStyle("Adaptive.ImageGallery");

//            ScrollViewer.SetHorizontalScrollBarVisibility(uiGallery, ScrollBarVisibility.Disabled);
//            var itemsPanelTemplate = new ItemsPanelTemplate();
//            var factory = new FrameworkElementFactory(typeof(WrapPanel));
//            // factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
//            itemsPanelTemplate.VisualTree = factory;
//            uiGallery.ItemsPanel = itemsPanelTemplate;

//            foreach (var image in this.Images)
//            {
//                if (this.ImageSize != null)
//                    image.Size = this.ImageSize;
//                var uiImage = image.Render(context);
//                uiGallery.Items.Add(uiImage);
//            }
//            return uiGallery;
//        }
//    }
//}