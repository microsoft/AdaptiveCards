using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Documents;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using ADP = Adaptive.Schema.Net;

namespace WpfVisualizer
{



    class AdaptiveXamlRenderer
    {
        private ResourceDictionary resources;
        private IAdaptiveTheme Theme = new DefaultTheme();

        public AdaptiveXamlRenderer(IAdaptiveTheme theme, ResourceDictionary resources)
        {
            this.resources = resources;
            this.Theme = theme;
        }

        public UIElement Render(ADP.AdaptiveCard card)
        {
            var grid = new Grid();
            grid.Style = resources["Adaptive.Card"] as Style;
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
            else if (element is ADP.Seperator)
            {
                return Render(element as ADP.Seperator);
            }
            else if (element is ADP.Container)
            {
                return Render(element as ADP.Container);
            }
            else 
                Debug.Print($"Unknown Element type {element.GetType().Name}");
            return null;
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
                    default:
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

        public UIElement Render(ADP.Seperator seperator)
        {
            var uiSeperator = new Separator();
            uiSeperator.Style = resources["Adaptive.Seperator"] as Style;
            return uiSeperator;
        }


        public UIElement Render(ADP.TextBlock textBlock)
        {
            var uiTextBlock = new TextBlock();
            uiTextBlock.Style = resources["Adaptive.TextBlock"] as Style;

            uiTextBlock.Text = textBlock.Text;

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
                    uiTextBlock.Foreground = this.Theme.AccentColor;
                    break;
                case ADP.TextColor.Attention:
                    uiTextBlock.Foreground = this.Theme.AttentionColor;
                    break;
                case ADP.TextColor.Dark:
                    uiTextBlock.Foreground = this.Theme.DarkColor;
                    break;
                case ADP.TextColor.Good:
                    uiTextBlock.Foreground = this.Theme.GoodColor;
                    break;
                case ADP.TextColor.Light:
                    uiTextBlock.Foreground = this.Theme.LightColor;
                    break;
                case ADP.TextColor.Warning:
                    uiTextBlock.Foreground = this.Theme.WarningColor;
                    break;
                case ADP.TextColor.Default:
                default:
                    uiTextBlock.Foreground = this.Theme.DefaultColor;
                    break;
            }

            switch (textBlock.TextWeight)
            {
                case ADP.TextWeight.Bolder:
                    uiTextBlock.FontWeight = FontWeights.Bold;
                    break;
                case ADP.TextWeight.Lighter:
                    uiTextBlock.FontWeight = FontWeights.Thin;
                    break;
                case ADP.TextWeight.Normal:
                default:
                    uiTextBlock.FontWeight = FontWeights.Normal;
                    break;
            }

            if (textBlock.Wrap.HasValue && textBlock.Wrap.Value == true)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
            else
                uiTextBlock.TextWrapping = TextWrapping.NoWrap;

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
            switch (image.Size)
            {
                case ADP.Size.Auto:
                    uiImage.Stretch = Stretch.Uniform;
                    uiImage.Style = resources["Adaptive.Image"] as Style;
                    break;

                case ADP.Size.Stretch:
                    uiImage.Stretch = Stretch.UniformToFill;
                    uiImage.Style = resources["Adaptive.Image"] as Style;
                    break;

                case ADP.Size.Small:
                    uiImage.Style = resources["Adaptive.Image.Small"] as Style;
                    break;

                case ADP.Size.Medium:
                    uiImage.Style = resources["Adaptive.Image.Medium"] as Style;
                    break;

                case ADP.Size.Large:
                    uiImage.Style = resources["Adaptive.Image.Large"] as Style;
                    break;
            }
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
            return null;
        }
    }
}