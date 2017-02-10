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
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Xceed.Wpf.Toolkit;
using ADP = Adaptive.Schema.Net;

namespace WpfVisualizer
{
    public class AdaptiveXamlRenderer
    {
        private ResourceDictionary resources;

        public AdaptiveXamlRenderer(ResourceDictionary resources)
        {
            this.resources = resources;
        }

        /// <summary>
        /// AdaptiveCard
        /// </summary>
        /// <param name="card"></param>
        /// <returns></returns>
        public UIElement Render(ADP.AdaptiveCard card)
        {
            var grid = new Grid();
            grid.Style = resources["Adaptive.Card"] as Style;
            if (card.BackgroundImage != null)
            {
                Uri uri = new Uri(card.BackgroundImage);
                grid.Background = new ImageBrush(new BitmapImage(uri));
            }
            AddContainerElements(grid, card.Body, 0);
            return grid;
        }

        private int AddContainerElements(Grid grid, List<ADP.CardElement> elements, int iRow)
        {
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
            grid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });

            foreach (var cardElement in elements)
            {
                UIElement uiElement = RenderUnknownElement(cardElement);
                grid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                Grid.SetRow(uiElement, iRow);
                if (cardElement is ADP.Input)
                {
                    var input = cardElement as ADP.Input;
                    if (input.Title != null)
                    {
                        var uiTitle = new TextBlock() { Text = input.Title };
                        uiTitle.Style = resources["Adaptive.Input.Title"] as Style;
                        Grid.SetRow(uiTitle, iRow);
                        grid.Children.Add(uiTitle);
                        Grid.SetColumn(uiElement, 1);
                    }
                    else
                    {
                        Grid.SetColumnSpan(uiElement, 2);
                    }
                }
                else
                    Grid.SetColumnSpan(uiElement, 2);
                grid.Children.Add(uiElement);
                iRow++;
            }
            return iRow;
        }

        /// <summary>
        /// Unknown element based on type
        /// </summary>
        /// <param name="element"></param>
        /// <returns></returns>
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
            else if (element is ADP.TextInput)
            {
                return Render(element as ADP.TextInput);
            }
            else if (element is ADP.ChoiceInput)
            {
                return Render(element as ADP.ChoiceInput);
            }
            else if (element is ADP.Image)
            {
                return Render(element as ADP.Image);
            }
            else if (element is ADP.Container)
            {
                return Render(element as ADP.Container);
            }
            else
                Debug.Print($"Unknown Element type {element.GetType().Name}");
            // return place holder
            return new Grid();
        }

        public UIElement RenderAction(ADP.Action action)
        {
            if (action is ADP.HttpAction)
            {
                return Render(action as ADP.HttpAction);
            }
            else if (action is ADP.ShowCardAction)
            {
                return Render(action as ADP.ShowCardAction);
            }
            else if (action is ADP.OpenUrlAction)
            {
                return Render(action as ADP.OpenUrlAction);
            }
            else if (action is ADP.SubmitAction)
            {
                return Render(action as ADP.SubmitAction);
            }
            else if (action is ADP.CancelAction)
            {
                return Render(action as ADP.CancelAction);
            }
            else
                Debug.Print($"Unknown Action {action.GetType().Name}");
            // return place holder
            return new Grid();
        }

        /// <summary>
        /// Container
        /// </summary>
        /// <param name="container"></param>
        /// <returns></returns>
        public UIElement Render(ADP.Container container)
        {
            var uiContainer = new Grid();
            uiContainer.Style = resources["Adaptive.Container"] as Style;

            int iRow = 0;
            if (container.Separation == ADP.SeparationStyle.Before || container.Separation == ADP.SeparationStyle.Both)
                iRow = AddSeperator(uiContainer, iRow);

            iRow = AddContainerElements(uiContainer, container.Items, iRow);

            if (container.Separation == ADP.SeparationStyle.After || container.Separation == Adaptive.Schema.Net.SeparationStyle.Both)
                iRow = AddSeperator(uiContainer, iRow);
            return uiContainer;
        }

        private int AddSeperator(Grid uiContainer, int iRow)
        {
            var sep = new Separator();
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(sep, iRow);
            Grid.SetColumnSpan(sep, 2);
            sep.Style = resources["Adaptive.Separator"] as Style;
            uiContainer.Children.Add(sep);

            return ++iRow;
        }

        /// <summary>
        /// ColumnGroup
        /// </summary>
        /// <param name="columnGroup"></param>
        /// <returns></returns>
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

        /// <summary>
        /// FactGroup
        /// </summary>
        /// <param name="factGroup"></param>
        /// <returns></returns>
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

        /// <summary>
        /// Column
        /// </summary>
        /// <param name="column"></param>
        /// <returns></returns>
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

        /// <summary>
        /// TextBlock
        /// </summary>
        /// <param name="textBlock"></param>
        /// <returns></returns>
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
                    uiTextBlock.FontWeight = (FontWeight)resources["Adaptive.BolderFontWeight"];
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

        /// <summary>
        /// Fact
        /// </summary>
        /// <param name="fact"></param>
        /// <returns></returns>
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


        /// <summary>
        /// Image
        /// </summary>
        /// <param name="image"></param>
        /// <returns></returns>
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

        /// <summary>
        /// ImageGallery
        /// </summary>
        /// <param name="imageGallery"></param>
        /// <returns></returns>
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

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public UIElement Render(ADP.TextInput textInput)
        {
            return RenderTextInputStyle(textInput);
        }

        private UIElement RenderTextInputStyle(ADP.TextInput textInput)
        {
            if (textInput.Style.HasValue)
            {
                switch (textInput.Style)
                {
                    case ADP.TextInputStyle.Week:
                    case ADP.TextInputStyle.Date:
                        {
                            var datePicker = new DatePicker();
                            DateTime value;
                            if (DateTime.TryParse(textInput.Value, out value))
                                datePicker.SelectedDate = value;
                            DateTime minValue;
                            if (DateTime.TryParse(textInput.Min, out minValue))
                                datePicker.DisplayDateStart = minValue;
                            DateTime maxValue;
                            if (DateTime.TryParse(textInput.Max, out maxValue))
                                datePicker.DisplayDateEnd = maxValue;
                            datePicker.Style = this.resources["Adaptive.Input.TextInput.Date"] as Style;
                            return datePicker;
                        }

                    case ADP.TextInputStyle.Datetime:
                        {
                            var dateTimePicker = new DateTimePicker();
                            dateTimePicker.TimePickerVisibility = Visibility.Visible;

                            DateTime value;
                            if (DateTime.TryParse(textInput.Value, out value))
                                dateTimePicker.Value = value;
                            DateTime minValue;
                            if (DateTime.TryParse(textInput.Min, out minValue))
                                dateTimePicker.Minimum = minValue;
                            DateTime maxValue;
                            if (DateTime.TryParse(textInput.Max, out maxValue))
                                dateTimePicker.Maximum = maxValue;
                            dateTimePicker.Watermark = textInput.Placeholder;
                            dateTimePicker.Style = this.resources["Adaptive.Input.TextInput.DateTime"] as Style;
                            return dateTimePicker;
                        }

                    case ADP.TextInputStyle.Time:
                        {
                            var timePicker = new TimePicker();
                            DateTime value;
                            if (DateTime.TryParse(textInput.Value, out value))
                                timePicker.Value = value;
                            TimeSpan minValue;
                            if (TimeSpan.TryParse(textInput.Min, out minValue))
                                timePicker.EndTime = minValue;
                            TimeSpan maxValue;
                            if (TimeSpan.TryParse(textInput.Max, out maxValue))
                                timePicker.EndTime = maxValue;
                            timePicker.Style = this.resources["Adaptive.Input.TextInput.Time"] as Style;
                            return timePicker;
                        }

                    case ADP.TextInputStyle.Number:
                        {
                            IntegerUpDown numberPicker = new IntegerUpDown();
                            float value;
                            if (float.TryParse(textInput.Value, out value))
                                numberPicker.Value = Convert.ToInt32(value);
                            float minValue;
                            if (float.TryParse(textInput.Min, out minValue))
                                numberPicker.Minimum = Convert.ToInt32(minValue);
                            float maxValue;
                            if (float.TryParse(textInput.Max, out maxValue))
                                numberPicker.Maximum = Convert.ToInt32(maxValue);
                            numberPicker.ShowButtonSpinner = true;
                            float step;
                            if (float.TryParse(textInput.Step, out step))
                                numberPicker.Increment = Convert.ToInt32(step);
                            numberPicker.Watermark = textInput.Placeholder;
                            numberPicker.Style = this.resources["Adaptive.Input.TextInput.Number"] as Style;
                            return numberPicker;
                        }


                    case ADP.TextInputStyle.Password:
                        {
                            PasswordBox passwordBox = new PasswordBox() { Password = textInput.Value };

                            if (textInput.MaxLength.HasValue)
                                passwordBox.MaxLength = textInput.MaxLength.Value;

                            passwordBox.Style = this.resources["Adaptive.Input.TextInput.Password"] as Style;
                            return passwordBox;
                        }

                    case ADP.TextInputStyle.Range:
                        {
                            var rangeGrid = new Grid();
                            rangeGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = new GridLength(1, GridUnitType.Star) });
                            rangeGrid.ColumnDefinitions.Add(new ColumnDefinition() { Width = GridLength.Auto });
                            rangeGrid.Style = this.resources["Adapative.Input.TextInput.Range"] as Style;

                            var rangePanel = new StackPanel();
                            rangePanel.Orientation = Orientation.Horizontal;
                            Grid.SetColumn(rangePanel, 1);

                            Slider slider = new Slider();
                            slider.IsSnapToTickEnabled = true;
                            slider.TickPlacement = TickPlacement.BottomRight;
                            double min;
                            if (double.TryParse(textInput.Min, out min))
                                slider.Minimum = min;
                            double max;
                            if (double.TryParse(textInput.Max, out max))
                                slider.Maximum = max;
                            double val;
                            if (double.TryParse(textInput.Value, out val))
                                slider.Value = val;
                            float step;
                            if (float.TryParse(textInput.Step, out step))
                            {
                                slider.SmallChange = Convert.ToInt32(step);
                                slider.LargeChange = 2 * Convert.ToInt32(step);
                            }
                            rangeGrid.Children.Add(slider);

                            TextBox tb = new TextBox();
                            tb.VerticalAlignment = VerticalAlignment.Center;
                            tb.Style = this.resources["Adaptive.Input.TextInput.Range.TextBox"] as Style;
                            rangePanel.Children.Add(tb);

                            tb.SetBinding(TextBox.TextProperty, new Binding()
                            {
                                Path = new PropertyPath("Value"),
                                Source = slider,
                                Mode = BindingMode.TwoWay
                            });
                            rangeGrid.Children.Add(rangePanel);
                            return rangeGrid;
                        }

                    case ADP.TextInputStyle.Tel:
                        {
                            var telTextBox = new MaskedTextBox();
                            telTextBox.Text = textInput.Value;
                            telTextBox.Mask = "(000) 000 - 0000";
                            telTextBox.Style = this.resources["Adaptive.Input.TextInput.Tel"] as Style;
                            return telTextBox;
                        }

                    case ADP.TextInputStyle.Email:
                    case ADP.TextInputStyle.Month:
                    default:
                        break;
                }
            }

            var textBox = new WatermarkTextBox() { Text = textInput.Value };
            if (textInput.IsMultiline == true)
            {
                textBox.AcceptsReturn = true;
                textBox.TextWrapping = TextWrapping.Wrap;
                textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
            }
            if (textInput.MaxLength.HasValue)
                textBox.MaxLength = textInput.MaxLength.Value;

            textBox.Watermark = textInput.Placeholder;

            textBox.Style = this.resources[$"Adaptive.Input.TextInput.{textInput.Style}"] as Style ?? this.resources[$"Adaptive.Input.TextInput"] as Style;
            return textBox;
        }

        private void NumberBox_PreviewTextInput(object sender, System.Windows.Input.TextCompositionEventArgs e)
        {
            float num;
            e.Handled = !float.TryParse(e.Text, out num);
        }

        /// <summary>
        /// TextInput
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        public UIElement Render(ADP.ChoiceInput choiceInput)
        {
            var uiComboBox = new ComboBox();
            uiComboBox.Style = resources["Adaptive.Input.ChoiceInput.ComboBox"] as Style;
            uiComboBox.Tag = choiceInput;

            var uiStackPanel = new StackPanel();
            uiStackPanel.Tag = choiceInput;
            uiStackPanel.Orientation = Orientation.Vertical;
            uiStackPanel.Style = resources["Adaptive.Input.ChoiceInput"] as Style;

            foreach (var choice in choiceInput.Choices)
            {
                if (choiceInput.MultiSelect == true)
                {
                    var uiCheckbox = new CheckBox();
                    uiCheckbox.Content = choice.Display;
                    uiCheckbox.IsChecked = choice.IsSelected;
                    uiCheckbox.Tag = choice;
                    uiCheckbox.Style = resources["Adaptive.Input.ChoiceInput.CheckBox"] as Style;
                    uiStackPanel.Children.Add(uiCheckbox);
                }
                else
                {
                    if (choiceInput.Style == ADP.ChoiceInputStyle.Compact)
                    {
                        var uiComboItem = new ComboBoxItem();
                        uiComboItem.Style = resources["Adaptive.Input.ChoiceInput.ComboBoxItem"] as Style;
                        uiComboItem.Content = choice.Display;
                        uiComboItem.Tag = choice;
                        uiComboBox.Items.Add(uiComboItem);
                        if (choice.IsSelected)
                            uiComboBox.SelectedItem = uiComboItem;
                    }
                    else
                    {
                        var uiRadio = new RadioButton();
                        uiRadio.Content = choice.Display;
                        uiRadio.IsChecked = choice.IsSelected;
                        uiRadio.GroupName = choiceInput.Id;
                        uiRadio.Tag = choice;
                        uiRadio.Style = resources["Adaptive.Input.ChoiceInput.Radio"] as Style;
                        uiStackPanel.Children.Add(uiRadio);
                    }
                }
            }
            if (choiceInput.Style == ADP.ChoiceInputStyle.Compact)
                return uiComboBox;
            return uiStackPanel;
        }

        /// <summary>
        /// HttpAction
        /// </summary>
        /// <param name="httpAction"></param>
        /// <returns></returns>
        public UIElement Render(ADP.HttpAction httpAction)
        {
            var uiActionGroup = new Grid();
            return uiActionGroup;
        }

        /// <summary>
        /// ShowCard
        /// </summary>
        /// <param name="showCardAction"></param>
        /// <returns></returns>
        public UIElement Render(ADP.ShowCardAction showCardAction)
        {
            var uiActionGroup = new Grid();
            return uiActionGroup;
        }

        /// <summary>
        /// OpenUrl
        /// </summary>
        /// <param name="openUrlAction"></param>
        /// <returns></returns>
        public UIElement Render(ADP.OpenUrlAction openUrlAction)
        {
            var uiActionGroup = new Grid();
            return uiActionGroup;
        }


        /// <summary>
        /// SubmitAction
        /// </summary>
        /// <param name="submitAction"></param>
        /// <returns></returns>
        public UIElement Render(ADP.SubmitAction submitAction)
        {
            var uiActionGroup = new Grid();
            return uiActionGroup;
        }

        /// <summary>
        /// CancelAction
        /// </summary>
        /// <param name="cancelAction"></param>
        /// <returns></returns>
        public UIElement Render(ADP.CancelAction cancelAction)
        {
            var uiActionGroup = new Grid();
            return uiActionGroup;
        }
    }
}