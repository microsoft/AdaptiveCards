using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Documents;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using ADP = Adaptive.Schema.Net;

namespace WpfVisualizer
{



    class AdaptiveXamlRenderer
    {
        private ResourceDictionary resources;

        public AdaptiveXamlRenderer(ResourceDictionary resources)
        {
            this.resources = resources;
        }

        public UIElement Render(ADP.AdaptiveCard card)
        {
            var grid = new Grid();
            grid.Style = resources["Adaptive.Card"] as Style;
            if (card.BackgroundImage != null)
            {
                Uri uri = new Uri(card.BackgroundImage);
                grid.Background = new ImageBrush(new BitmapImage(uri));
            }

            int iRow = 0;
            foreach (var cardElement in card.Body)
            {
                UIElement uiElement = RenderUnknownElement(cardElement);
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, iRow++);
                grid.Children.Add(uiElement);
            }
            return grid;
        }

        private UIElement RenderUnknownElement(ADP.CardElement element)
        {
            if (element is ADP.ColumnGroup)
            {
                return Render(element as ADP.ColumnGroup);
            }
            else if (element is ADP.Column)
            {
                return Render(element as ADP.Column);
            }
            else if (element is ADP.ImageGallery)
            {
                return Render(element as ADP.ImageGallery);
            }
            else if (element is ADP.FactGroup)
            {
                return Render(element as ADP.FactGroup);
            }
            else if (element is ADP.TextBlock)
            {
                return Render(element as ADP.TextBlock);
            }
            else if (element is ADP.Input)
            {
                return Render(element as ADP.Input);
            }
            else if (element is ADP.Image)
            {
                return Render(element as ADP.Image);
            }
            else if (element is ADP.Container)
            {
                return Render(element as ADP.Container);
            }
            else if (element is ADP.Action)
            {
                return Render(element as ADP.Action);
            }
            else
                Debug.Print($"Unknown Element type {element.GetType().Name}");
            // return place holder
            return new Grid();
        }

        public UIElement Render(ADP.Container container)
        {
            var uiContainer = new Grid();
            uiContainer.Style = resources["Adaptive.Container"] as Style;

            int iRow = 0;
            foreach (var cardElement in container.Items)
            {
                UIElement uiElement = RenderUnknownElement(cardElement);
                uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, iRow++);
                uiContainer.Children.Add(uiElement);
            }
            return uiContainer;
        }

        public UIElement Render(ADP.ColumnGroup columnGroup)
        {
            var uiColumnGroup = new Grid();
            uiColumnGroup.Style = resources["Adaptive.ColumnGroup"] as Style;

            int iCol = 0;
            foreach (var column in columnGroup.Columns)
            {
                UIElement uiElement = Render(column);

                // do some sizing magic using the magic GridUnitType.Star
                switch (column.Size)
                {
                    case ADP.Size.Stretch:
                        uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                        break;

                    case ADP.Size.Small:
                        uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(.2, GridUnitType.Star) });
                        break;

                    case ADP.Size.Medium:
                        uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(.5, GridUnitType.Star) });
                        break;

                    case ADP.Size.Large:
                        uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(.7, GridUnitType.Star) });
                        break;

                    case ADP.Size.Auto:
                        uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        break;

                    default:
                        double val;
                        if (double.TryParse(column.Size.ToString(), out val))
                            uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(val, GridUnitType.Star) });
                        else
                            uiColumnGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                        break;
                }

                Grid.SetColumn(uiElement, iCol++);
                uiColumnGroup.Children.Add(uiElement);
            }

            return uiColumnGroup;
        }

        public UIElement Render(ADP.FactGroup factGroup)
        {
            var uiFactGroup = new Grid();
            // grid.Margin = this.Theme.FactGroupMargins;
            uiFactGroup.Style = resources["Adaptive.FactGroup"] as Style;

            uiFactGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            uiFactGroup.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            int iRow = 0;
            foreach (var fact in factGroup.Facts)
            {
                Tuple<UIElement, UIElement> uiElements = Render(fact as ADP.Fact);
                uiFactGroup.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                Grid.SetColumn(uiElements.Item1, 0);
                Grid.SetRow(uiElements.Item1, iRow);
                uiFactGroup.Children.Add(uiElements.Item1);

                Grid.SetColumn(uiElements.Item2, 1);
                Grid.SetRow(uiElements.Item2, iRow++);
                uiFactGroup.Children.Add(uiElements.Item2);
            }
            return uiFactGroup;
        }

        public UIElement Render(ADP.Column column)
        {
            var uiColumn = new Grid();
            // grid.Margin = this.Theme.ColumnMargins;
            uiColumn.Style = resources["Adaptive.Column"] as Style;

            int iRow = 0;
            foreach (var cardElement in column.Items)
            {
                UIElement uiElement = RenderUnknownElement(cardElement);
                uiColumn.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, iRow++);
                uiColumn.Children.Add(uiElement);
            }
            return uiColumn;
        }

        public UIElement Render(ADP.TextBlock textBlock)
        {
            Marked marked = new Marked();
            marked.Options.Renderer = new XamlRenderer();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            // uiTextBlock.Text = textBlock.Text;
            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(textBlock.Text)}</TextBlock>";
            StringReader stringReader = new StringReader(xaml);
            XmlReader xmlReader = XmlReader.Create(stringReader);
            var uiTextBlock = (TextBlock)XamlReader.Load(xmlReader);
            uiTextBlock.Style = resources["Adaptive.TextBlock"] as Style;


            if (textBlock.HorizontalAlignment.HasValue)
            {
                HorizontalAlignment alignment;
                if (Enum.TryParse<HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                    uiTextBlock.HorizontalAlignment = alignment;
            }

            switch (textBlock.TextSize)
            {
                case ADP.TextSize.Small:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Small"] as Style;
                    break;
                case ADP.TextSize.Medium:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Medium"] as Style;
                    break;
                case ADP.TextSize.Large:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Large"] as Style;
                    break;
                case ADP.TextSize.ExtraLarge:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.ExtraLarge"] as Style;
                    break;
                case ADP.TextSize.Normal:
                default:
                    uiTextBlock.Style = resources["Adaptive.TextBlock.Normal"] as Style;
                    break;
            }

            switch (textBlock.TextColor)
            {
                case ADP.TextColor.Accent:
                    uiTextBlock.Foreground = resources["Adaptive.AccentBrush"] as Brush;
                    break;
                case ADP.TextColor.Attention:
                    uiTextBlock.Foreground = resources["Adaptive.AttentionBrush"] as Brush;
                    break;
                case ADP.TextColor.Dark:
                    uiTextBlock.Foreground = resources["Adaptive.DarkBrush"] as Brush;
                    break;
                case ADP.TextColor.Good:
                    uiTextBlock.Foreground = resources["Adaptive.GoodBrush"] as Brush;
                    break;
                case ADP.TextColor.Light:
                    uiTextBlock.Foreground = resources["Adaptive.LightBrush"] as Brush;
                    break;
                case ADP.TextColor.Warning:
                    uiTextBlock.Foreground = resources["Adaptive.WarningBrush"] as Brush;
                    break;
                case ADP.TextColor.Default:
                default:
                    uiTextBlock.Foreground = resources["Adaptive.DefaultBrush"] as Brush;
                    break;
            }

            switch (textBlock.TextWeight)
            {
                case ADP.TextWeight.Bolder:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.BolderFontWeight"] ;
                    break;
                case ADP.TextWeight.Lighter:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.LighterFontWeight"];
                    break;
                case ADP.TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.NormalFontWeight"];
                    break;
            }

            if (textBlock.Wrap.HasValue && textBlock.Wrap == true)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
            else
                uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            if (textBlock.IsSubtle.HasValue && textBlock.IsSubtle == true)
                uiTextBlock.Opacity = (double)resources["Adaptive.IsSubtleOpacity"];
            return uiTextBlock;
        }

        public Tuple<UIElement, UIElement> Render(ADP.Fact fact)
        {
            return new Tuple<UIElement, UIElement>(new TextBlock()
            {
                Text = fact.Name,
                Style = this.resources["Adaptive.Fact.Name"] as Style
            },
            new TextBlock()
            {
                Text = fact.Value,
                Style = this.resources["Adaptive.Fact.Value"] as Style
            });
        }

        public UIElement Render(ADP.Image image)
        {
            var uiImage = new Image();
            // uiImage.Margin = this.Theme.ImageMargins;

            uiImage.Source = new BitmapImage(new Uri(image.Url));
            HorizontalAlignment alignment;
            if (Enum.TryParse<HorizontalAlignment>(image.HorizontalAlignment.ToString(), out alignment))
                uiImage.HorizontalAlignment = alignment;
            // How do  I figure image size???
            // image.Size = ADP.Schema.Net.Size.
            string style = $"Adaptive.Image";
            if (image.Size != null)
                style += $".{image.Size.ToString()}";

            if (image.Style == ADP.ImageStyle.Person)
                style += $".{image.Style.ToString()}";
            uiImage.Style = resources[style] as Style;
            return uiImage;
        }

        public UIElement Render(ADP.ImageGallery imageGallery)
        {
            var uiGallery = new ListBox();
            uiGallery.Style = resources["Adaptive.ImageGallery"] as Style;

            ScrollViewer.SetVerticalScrollBarVisibility(uiGallery, ScrollBarVisibility.Disabled);
            var itemsPanelTemplate = new ItemsPanelTemplate();
            var factory = new FrameworkElementFactory(typeof(StackPanel));
            factory.SetValue(StackPanel.OrientationProperty, Orientation.Horizontal);
            itemsPanelTemplate.VisualTree = factory;
            uiGallery.ItemsPanel = itemsPanelTemplate;

            foreach (var image in imageGallery.Images)
            {
                var uiImage = Render(image);
                uiGallery.Items.Add(uiImage);
            }
            return uiGallery;
        }

        public UIElement Render(ADP.Input input)
        {
            return new Grid();
        }

        public UIElement Render(ADP.Action action)
        {
            var uiActionGroup = new Grid();
            return uiActionGroup;
        }
    }
}