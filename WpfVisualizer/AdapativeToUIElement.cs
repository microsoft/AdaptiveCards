using System;
using System.Collections.Generic;
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
    class AdaptiveRenderer
    {
        // constrols text size
        public double TextSmall = 10;
        public double TextNormal = 12;
        public double TextMedium = 14;
        public double TextLarge = 16;
        public double TextExtraLarge = 18;

        public Brush AccentColor = Brushes.Blue;
        public Brush AttentionColor = Brushes.Red;
        public Brush DarkColor = Brushes.Black;
        public Brush LightColor = Brushes.White;
        public Brush DefaultColor = Brushes.Black;
        public Brush GoodColor = Brushes.Green;
        public Brush WarningColor = Brushes.Yellow;

        public Size SmallImageSize = new Size(60, 60);
        public Size MediumImageSize = new Size(60, 60);
        public Size LargeImageSize = new Size(160, 180);

        public UIElement Render(ADP.AdaptiveCard card)
        {
            var grid = new Grid();
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

            return null;
        }

        public UIElement Render(ADP.Container container)
        {
            var grid = new Grid();
            int iRow = 0;
            foreach (var cardElement in container.Items)
            {
                UIElement uiElement = RenderUnknownElement(cardElement);
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, iRow++);
                grid.Children.Add(uiElement);
            }
            return grid;
        }

        public UIElement Render(ADP.ColumnGroup columnGroup)
        {
            var grid = new Grid();
            int iCol = 0;
            foreach (var column in columnGroup.Columns)
            {
                UIElement uiElement = Render(column as ADP.Column);
                grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                Grid.SetColumn(uiElement, iCol++);
                grid.Children.Add(uiElement);
            }

            return grid;
        }

        public UIElement Render(ADP.FactGroup factGroup)
        {
            var grid = new Grid();
            int iRow = 0;
            foreach (var fact in factGroup.Facts)
            {
                Tuple<UIElement, UIElement> uiElements = Render(fact as ADP.Fact);
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });

                Grid.SetColumn(uiElements.Item1, 0);
                Grid.SetRow(uiElements.Item1, iRow);
                grid.Children.Add(uiElements.Item1);

                Grid.SetColumn(uiElements.Item2, 1);
                Grid.SetRow(uiElements.Item2, iRow++);
                grid.Children.Add(uiElements.Item2);
            }
            return grid;
        }

        public UIElement Render(ADP.Column column)
        {
            var grid = new Grid();
            int iRow = 0;
            foreach (var cardElement in column.Items)
            {
                UIElement uiElement = RenderUnknownElement(cardElement);
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, iRow++);
                grid.Children.Add(uiElement);
            }
            return grid;
        }

        public UIElement Render(ADP.Seperator seperator)
        {
            return new Separator();
        }


        public UIElement Render(ADP.TextBlock textBlock)
        {
            var uiTextBlock = new TextBlock();

            uiTextBlock.Text = textBlock.Text;

            HorizontalAlignment alignment;
            if (Enum.TryParse<HorizontalAlignment>(textBlock.HorizontalAlignment.ToString(), out alignment))
                uiTextBlock.HorizontalAlignment = alignment;

            switch (textBlock.TextSize)
            {
                case ADP.TextSize.Small:
                    uiTextBlock.FontSize = this.TextSmall;
                    break;
                case ADP.TextSize.Normal:
                    uiTextBlock.FontSize = this.TextNormal;
                    break;
                case ADP.TextSize.Medium:
                    uiTextBlock.FontSize = this.TextMedium;
                    break;
                case ADP.TextSize.Large:
                    uiTextBlock.FontSize = this.TextLarge;
                    break;
                case ADP.TextSize.ExtraLarge:
                    uiTextBlock.FontSize = this.TextExtraLarge;
                    break;
            }

            switch (textBlock.TextColor)
            {
                case ADP.TextColor.Accent:
                    uiTextBlock.Foreground = this.AccentColor;
                    break;
                case ADP.TextColor.Attention:
                    uiTextBlock.Foreground = this.AttentionColor;
                    break;
                case ADP.TextColor.Dark:
                    uiTextBlock.Foreground = this.DarkColor;
                    break;
                case ADP.TextColor.Default:
                    uiTextBlock.Foreground = this.DefaultColor;
                    break;
                case ADP.TextColor.Good:
                    uiTextBlock.Foreground = this.GoodColor;
                    break;
                case ADP.TextColor.Light:
                    uiTextBlock.Foreground = this.LightColor;
                    break;
                case ADP.TextColor.Warning:
                    uiTextBlock.Foreground = this.WarningColor;
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
                    uiTextBlock.FontWeight = FontWeights.Normal;
                    break;
            }

            if (textBlock.Wrap)
                uiTextBlock.TextWrapping = TextWrapping.Wrap;
            else
                uiTextBlock.TextWrapping = TextWrapping.NoWrap;

            return uiTextBlock;
        }

        public Tuple<UIElement, UIElement> Render(ADP.Fact fact)
        {
            return new Tuple<UIElement, UIElement>(new TextBlock()
            {
                Text = fact.Name
            },
            new TextBlock()
            {
                Text = fact.Value
            });
        }

        public UIElement Render(ADP.Image image)
        {
            var uiImage = new Image();
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
                    break;

                case ADP.Size.Stretch:
                    uiImage.Stretch = Stretch.Uniform;
                    break;

                case ADP.Size.Small:
                    uiImage.Width = this.SmallImageSize.Width;
                    uiImage.Height = this.SmallImageSize.Height;
                    break;

                case ADP.Size.Medium:
                    uiImage.Width = this.MediumImageSize.Width;
                    uiImage.Height = this.MediumImageSize.Height;
                    break;

                case ADP.Size.Large:
                    uiImage.Width = this.LargeImageSize.Width;
                    uiImage.Height = this.LargeImageSize.Height;
                    break;
            }
            return uiImage;
        }

        public UIElement Render(ADP.ImageGallery imageGallery)
        {
            var uiGallery = new ListBox();
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