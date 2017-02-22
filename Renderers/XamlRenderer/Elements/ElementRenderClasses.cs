//using System;
//using System.IO;
//using System.Windows;
//using System.Windows.Controls;
//using System.Windows.Data;
//using System.Windows.Markup;
//using System.Windows.Media;
//using System.Windows.Media.Imaging;
//using System.Xml;
//using MarkedNet;
//using Xceed.Wpf.Toolkit;

//namespace Adaptive
//{
//    public partial class TextBlock
//    {

//        /// <summary>
//        /// TextBlock
//        /// </summary>
//        /// <param name="textBlock"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            Marked marked = new Marked();
//            marked.Options.Renderer = new MarkedXamlRenderer();
//            marked.Options.Mangle = false;
//            marked.Options.Sanitize = true;

//            string text = Utilities.ApplyTextFunctions(this.Text);

//            // uiTextBlock.Text = this.Text;
//            string xaml = $"<TextBlock  xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\">{marked.Parse(text)}</TextBlock>";
//            StringReader stringReader = new StringReader(xaml);
//            XmlReader xmlReader = XmlReader.Create(stringReader);
//            var uiTextBlock = (System.Windows.Controls.TextBlock)XamlReader.Load(xmlReader);
//            uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock");
//            uiTextBlock.TextTrimming = TextTrimming.CharacterEllipsis;

//            if (this.HorizontalAlignment.HasValue)
//            {
//                System.Windows.HorizontalAlignment alignment;
//                if (Enum.TryParse<System.Windows.HorizontalAlignment>(this.HorizontalAlignment.ToString(), out alignment))
//                    uiTextBlock.HorizontalAlignment = alignment;
//            }

//            switch (this.Size)
//            {
//                case TextSize.Small:
//                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Small"); ;
//                    break;
//                case TextSize.Medium:
//                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Medium"); ;
//                    break;
//                case TextSize.Large:
//                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Large"); ;
//                    break;
//                case TextSize.ExtraLarge:
//                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.ExtraLarge"); ;
//                    break;
//                case TextSize.Normal:
//                default:
//                    uiTextBlock.Style = context.GetStyle("Adaptive.TextBlock.Normal"); ;
//                    break;
//            }

//            switch (this.Color)
//            {
//                case TextColor.Accent:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.AccentBrush"] as Brush;
//                    break;
//                case TextColor.Attention:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.AttentionBrush"] as Brush;
//                    break;
//                case TextColor.Dark:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.DarkBrush"] as Brush;
//                    break;
//                case TextColor.Good:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.GoodBrush"] as Brush;
//                    break;
//                case TextColor.Light:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.LightBrush"] as Brush;
//                    break;
//                case TextColor.Warning:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.WarningBrush"] as Brush;
//                    break;
//                case TextColor.Default:
//                default:
//                    uiTextBlock.Foreground = context.Resources["Adaptive.DefaultBrush"] as Brush;
//                    break;
//            }

//            switch (this.Weight)
//            {
//                case TextWeight.Bolder:
//                    uiTextBlock.FontWeight = (FontWeight)context.Resources["Adaptive.BolderFontWeight"];
//                    break;
//                case TextWeight.Lighter:
//                    uiTextBlock.FontWeight = (FontWeight)context.Resources["Adaptive.LighterFontWeight"];
//                    break;
//                case TextWeight.Normal:
//                default:
//                    uiTextBlock.FontWeight = (FontWeight)context.Resources["Adaptive.NormalFontWeight"];
//                    break;
//            }

//            if (this.IsSubtle.HasValue && this.IsSubtle == true)
//                uiTextBlock.Opacity = (double)context.Resources["Adaptive.IsSubtleOpacity"];

//            if (this.Wrap.HasValue && this.Wrap == true)
//            {
//                uiTextBlock.TextWrapping = TextWrapping.Wrap;
//                if (this.MaxLines.HasValue)
//                {
//                    var uiGrid = new Grid();
//                    // create hidden textBlock with appropriate linebreaks that we can use to measure the ActualHeight
//                    // using same style, fontWeight settings as original textblock
//                    var measureBlock = new System.Windows.Controls.TextBlock()
//                    {
//                        Style = uiTextBlock.Style,
//                        FontWeight = uiTextBlock.FontWeight,
//                        Visibility = Visibility.Hidden,
//                        TextWrapping = TextWrapping.Wrap
//                    };

//                    for (int i = 1; i < this.MaxLines; i++)
//                        measureBlock.Inlines.Add(new System.Windows.Documents.LineBreak());

//                    // bind the real textBlock's Height => MeasureBlock.ActualHeight
//                    uiTextBlock.SetBinding(Control.HeightProperty, new Binding()
//                    {
//                        Path = new PropertyPath("ActualHeight"),
//                        Source = measureBlock,
//                        Mode = BindingMode.OneWay
//                    });

//                    // Add both to a grid so they go as a unit
//                    uiGrid.Children.Add(measureBlock);
//                    uiGrid.Children.Add(uiTextBlock);
//                    return uiGrid;
//                }
//            }
//            else
//                uiTextBlock.TextWrapping = TextWrapping.NoWrap;
//            return uiTextBlock;
//        }
//    }

//    public partial class Image
//    {
//        /// <summary>
//        /// Image
//        /// </summary>
//        /// <param name="image"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiImage = new System.Windows.Controls.Image();
//            // uiImage.Margin = this.Theme.ImageMargins;

//            uiImage.Source = new BitmapImage(new Uri(this.Url));
//            System.Windows.HorizontalAlignment alignment;
//            if (Enum.TryParse<System.Windows.HorizontalAlignment>(this.HorizontalAlignment.ToString(), out alignment))
//                uiImage.HorizontalAlignment = alignment;
//            string style = $"Adaptive.Image";
//            if (this.Size != null)
//                style += $".{this.Size.ToString()}";

//            if (this.Style == ImageStyle.Person)
//                style += $".{this.Style.ToString()}";
//            uiImage.Style = context.GetStyle(style);
//            if (this.SelectAction != null)
//            {
//                var uiButton = (Button)this.SelectAction.Render(context.NewActionContext());
//                uiButton.Content = uiImage;
//                uiButton.Style = context.GetStyle("Adaptive.Action.Tap");
//                return uiButton;
//            }
//            return uiImage;
//        }
//    }

//    public partial class InputText
//    {
//        /// <summary>
//        /// Input.Text
//        /// </summary>
//        /// <param name="input"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var textBox = new WatermarkTextBox() { Text = this.Value };
//            if (this.IsMultiline == true)
//            {
//                textBox.AcceptsReturn = true;
//                textBox.TextWrapping = TextWrapping.Wrap;
//                textBox.HorizontalScrollBarVisibility = ScrollBarVisibility.Disabled;
//            }
//            if (this.MaxLength.HasValue)
//                textBox.MaxLength = this.MaxLength.Value;

//            textBox.Watermark = this.Placeholder;
//            textBox.Style = context.GetStyle($"Adaptive.Input.Text.{this.Style}");
//            textBox.DataContext = this;
//            context.InputControls.Add(textBox);
//            return textBox;
//        }
//    }

//    public partial class InputDate
//    {
//        /// <summary>
//        /// Input.Date
//        /// </summary>
//        /// <param name="input"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var datePicker = new DatePicker();
//            datePicker.ToolTip = this.Placeholder;
//            DateTime value;
//            if (DateTime.TryParse(this.Value, out value))
//                datePicker.SelectedDate = value;
//            DateTime minValue;
//            if (DateTime.TryParse(this.Min, out minValue))
//                datePicker.DisplayDateStart = minValue;
//            DateTime maxValue;
//            if (DateTime.TryParse(this.Max, out maxValue))
//                datePicker.DisplayDateEnd = maxValue;
//            datePicker.Style = context.GetStyle("Adaptive.Input.Date");
//            datePicker.DataContext = this;
//            context.InputControls.Add(datePicker);
//            return datePicker;
//        }
//    }


//    public partial class InputTime
//    {
//        /// <summary>
//        /// Input.Time
//        /// </summary>
//        /// <param name="input"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var timePicker = new TimePicker();
//            DateTime value;
//            if (DateTime.TryParse(this.Value, out value))
//                timePicker.Value = value;
//            TimeSpan minValue;
//            if (TimeSpan.TryParse(this.Min, out minValue))
//                timePicker.EndTime = minValue;
//            TimeSpan maxValue;
//            if (TimeSpan.TryParse(this.Max, out maxValue))
//                timePicker.EndTime = maxValue;
//            timePicker.Watermark = this.Placeholder;
//            timePicker.Style = context.GetStyle("Adaptive.Input.Time");
//            timePicker.DataContext = this;
//            context.InputControls.Add(timePicker);
//            return timePicker;
//        }
//    }

//    public partial class InputNumber
//    {
//        /// <summary>
//        /// Input.Number
//        /// </summary>
//        /// <param name="input"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            IntegerUpDown numberPicker = new IntegerUpDown();
//            // numberPicker.ShowButtonSpinner = true;

//            float value;
//            if (float.TryParse(this.Value, out value))
//                numberPicker.Value = Convert.ToInt32(value);

//            float minValue;
//            if (float.TryParse(this.Min, out minValue))
//                numberPicker.Minimum = Convert.ToInt32(minValue);

//            float maxValue;
//            if (float.TryParse(this.Max, out maxValue))
//                numberPicker.Maximum = Convert.ToInt32(maxValue);

//            numberPicker.Watermark = this.Placeholder;
//            numberPicker.Style = context.GetStyle("Adaptive.Input.Number");
//            numberPicker.DataContext = this;
//            context.InputControls.Add(numberPicker);
//            return numberPicker;
//        }
//    }


//    public partial class InputToggle
//    {
//        /// <summary>
//        /// TextInput
//        /// </summary>
//        /// <param name="input"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiToggle = new CheckBox();
//            uiToggle.Content = this.Title;
//            uiToggle.IsChecked = this.Value == (this.ValueOn ?? "true");
//            uiToggle.Style = context.GetStyle($"Adaptive.Input.Toggle");
//            uiToggle.DataContext = this;
//            context.InputControls.Add(uiToggle);
//            return uiToggle;
//        }
//    }


//    public partial class InputChoiceSet
//    {

//        /// <summary>
//        /// Input.ChoiceSet
//        /// </summary>
//        /// <param name="input"></param>
//        /// <returns></returns>
//        public override FrameworkElement Render(RenderContext context)
//        {
//            var uiGrid = new Grid();
//            uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
//            uiGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

//            var uiComboBox = new ComboBox();
//            uiComboBox.Style = context.GetStyle("Adaptive.Input.ChoiceSet.ComboBox");
//            uiComboBox.DataContext = this;

//            var uiChoices = new ListBox();
//            ScrollViewer.SetHorizontalScrollBarVisibility(uiChoices, ScrollBarVisibility.Disabled);
//            var itemsPanelTemplate = new ItemsPanelTemplate();
//            var factory = new FrameworkElementFactory(typeof(WrapPanel));
//            itemsPanelTemplate.VisualTree = factory;
//            uiChoices.ItemsPanel = itemsPanelTemplate;
//            uiChoices.DataContext = this;
//            uiChoices.Style = context.GetStyle("Adaptive.Input.ChoiceSet");

//            foreach (var choice in this.Choices)
//            {
//                if (this.IsMultiSelect == true)
//                {
//                    var uiCheckbox = new CheckBox();
//                    uiCheckbox.Content = choice.Display;
//                    uiCheckbox.IsChecked = choice.IsSelected;
//                    uiCheckbox.DataContext = choice;
//                    uiCheckbox.Style = context.GetStyle("Adaptive.Input.ChoiceSet.CheckBox");
//                    uiChoices.Items.Add(uiCheckbox);
//                }
//                else
//                {
//                    if (this.Style == ChoiceInputStyle.Compact)
//                    {
//                        var uiComboItem = new ComboBoxItem();
//                        uiComboItem.Style = context.GetStyle("Adaptive.Input.ChoiceSet.ComboBoxItem");
//                        uiComboItem.Content = choice.Display;
//                        uiComboItem.DataContext = choice;
//                        uiComboBox.Items.Add(uiComboItem);
//                        if (choice.IsSelected)
//                            uiComboBox.SelectedItem = uiComboItem;
//                    }
//                    else
//                    {
//                        var uiRadio = new RadioButton();
//                        uiRadio.Content = choice.Display;
//                        uiRadio.IsChecked = choice.IsSelected;
//                        uiRadio.GroupName = this.Id;
//                        uiRadio.DataContext = choice;
//                        uiRadio.Style = context.GetStyle("Adaptive.Input.ChoiceSet.Radio");
//                        uiChoices.Items.Add(uiRadio);
//                    }
//                }
//            }
//            if (this.Style == ChoiceInputStyle.Compact)
//            {
//                context.InputControls.Add(uiComboBox);
//                Grid.SetRow(uiComboBox, 1);
//                uiGrid.Children.Add(uiComboBox);
//                return uiGrid;
//            }
//            else
//            {
//                context.InputControls.Add(uiChoices);
//                Grid.SetRow(uiChoices, 1);
//                uiGrid.Children.Add(uiChoices);
//                return uiGrid;
//            }
//        }
//    }

//}