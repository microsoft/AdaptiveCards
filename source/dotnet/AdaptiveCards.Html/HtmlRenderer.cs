using HtmlTags;
using MarkedNet;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Renderers
{
    /// <summary>
    /// Render as texthtml suitable for server side generation
    /// </summary>
    public class HtmlRenderer : AdaptiveRenderer<HtmlTag, object>
    {

        public HtmlRenderer(RenderOptions options) : base(options)
        {
        }

        public HtmlTag RenderAdaptiveCard(AdaptiveCard card)
        {
            return Render(card, null);
        }

        public HtmlTag RenderShowCard(ActionShowCard showCard)
        {
            return Render(showCard.Card, null);
        }

        protected override HtmlTag Render(ActionHttp action, object context)
        {
            // not supported
            return null;
        }

        protected override HtmlTag Render(ActionOpenUrl action, object context)
        {
            if (this.Options.SupportInteraction)
            {
                var uiButton = new LinkTag(action.Title, action.Url, action.Type.Replace(".", ""), "pushButton");
                return uiButton;
            }
            return null;
        }

        protected override HtmlTag Render(ActionShowCard action, object context)
        {
            // not supported
            return null;
        }

        protected override HtmlTag Render(ActionSubmit action, object context)
        {
            // not supported
            return null;
        }

        protected override HtmlTag Render(AdaptiveCard card, object context)
        {
            var uiCard = new DivTag()
                .AddClass(card.Type)
                .Style("border-width", "1px 1px 1px 3px")
                .Style("border-style", "solid")
                .Style("border-color", "rgb(241, 241, 241)");

            if (card.BackgroundImage != null)
            {
                uiCard = uiCard.Style("background-image", $"url('{card.BackgroundImage}')")
                    .Style("background-repeat", "no-repeat")
                    .Style("background-size", "cover");
            }

            AddContainerElements(uiCard, card.Body, card.Actions, context);

            return uiCard;
        }

        protected void AddContainerElements(HtmlTag uiContainer, List<CardElement> elements, List<ActionBase> actions, object context)
        {
            foreach (var cardElement in elements)
            {
                // each element has a row
                HtmlTag uiElement = this.Render(cardElement, context);
                if (uiElement != null)
                {
                    if (uiContainer.Children.Any())
                    {
                        switch (cardElement.Separation)
                        {
                            case SeparationStyle.None:
                                uiElement = uiElement.AddClass("NoSeparation");
                                break;
                            case SeparationStyle.Default:
                                break;
                            case SeparationStyle.Strong:
                                {
                                    uiElement = uiElement.AddClass("NoSeparation");
                                    var uiSep = new DivTag()
                                        .AddClass("Separator");
                                    uiContainer.Children.Add(uiSep);
                                }
                                break;
                        }

                    }
                    else
                    {
                        uiElement = uiElement.AddClass("NoSeparation");
                    }
                    uiContainer.Children.Add(uiElement);
                }
            }

            if (this.Options.SupportInteraction && actions?.Any() == true)
            {
                var uiActions = new DivTag()
                    .AddClass("Container");

                int iCol = 0;
                foreach (var action in actions)
                {
                    // add actions
                    var uiAction = this.RenderAction(action, context);
                    if (uiAction != null)
                    {
                        uiActions.Children.Add(uiAction);
                    }
                }

                if (uiActions.Children.Any())
                    uiContainer.Children.Add(uiActions);
            }
        }


        protected override HtmlTag Render(Column column, object context)
        {
            var uiColumn = new DivTag()
                .AddClass(column.Type);

            AddContainerElements(uiColumn, column.Items, column.Actions, context);

            if (this.Options.SupportInteraction && column.SelectAction != null)
            {
                //var uiButton = (Button)RenderAction(container.SelectAction, new RenderContext(this.actionCallback, this.missingDataCallback));
                //if (uiButton != null)
                //{
                //    uiButton.Content = uiContainer;
                //    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                //    return uiButton;
                //}
            }

            return uiColumn;
        }

        protected override HtmlTag Render(ColumnSet columnSet, object context)
        {
            var uiColumnSet = new DivTag()
                .AddClass(columnSet.Type)
                .Style("overflow", "hidden")
                .Style("display", "flex");

            double max = Math.Max(1.0, columnSet.Columns.Select(col =>
            {
                if (double.TryParse(col.Size ?? "0", out double val))
                    return val;
                return 0;
            }).Sum());

            foreach (var column in columnSet.Columns)
            {
                var uiColumn = this.Render(column, context);

                // Add vertical Seperator
                if (uiColumnSet.Children.Any())
                {
                    switch (column.Separation)
                    {
                        case SeparationStyle.None:
                            break;

                        case SeparationStyle.Default:
                            {
                                uiColumnSet.Children.Add(new DivTag()
                                    .AddClass("ColumnSeparator")
                                    .AddClass("Default")
                                    .Style("flex", "0 0 auto"));
                            }
                            break;

                        case SeparationStyle.Strong:
                            {
                                uiColumnSet.Children.Add(new DivTag()
                                    .AddClass("ColumnSeparator")
                                    .AddClass("Strong")
                                    .Style("flex", "0 0 auto"));
                            }
                            break;
                    }
                }

                // do some sizing magic 
                var size = column.Size?.ToLower();
                if (size == null || size == ColumnSize.Stretch.ToLower())
                    uiColumn = uiColumn.Style("flex", "1 1 auto");
                else if (size == ColumnSize.Auto.ToLower())
                    uiColumn = uiColumn.Style("flex", "0 0 auto");
                else
                {
                    double val;
                    if (double.TryParse(size, out val))
                    {
                        var percent = Convert.ToInt32(100 * (val / max));
                        uiColumn = uiColumn.Style("flex", $"1 1 {percent}%");
                    }
                    else
                        uiColumn = uiColumn.Style("flex", "0 0 auto");
                }

                uiColumnSet.Children.Add(uiColumn);
            }

            return uiColumnSet;
        }

        protected override HtmlTag Render(Container container, object context)
        {
            var uiContainer = new DivTag()
                .AddClass(container.Type);

            AddContainerElements(uiContainer, container.Items, container.Actions, context);

            if (this.Options.SupportInteraction && container.SelectAction != null)
            {
                //var uiButton = (Button)RenderAction(container.SelectAction, new RenderContext(this.actionCallback, this.missingDataCallback));
                //if (uiButton != null)
                //{
                //    uiButton.Content = uiContainer;
                //    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                //    return uiButton;
                //}
            }

            return uiContainer;
        }

        protected override Tuple<HtmlTag, HtmlTag> Render(Fact fact, object context)
        {
            return new Tuple<HtmlTag, HtmlTag>(new DivTag().Text(fact.Title).AddClass("FactName").AddClass("NoSeparation"),
                                               new DivTag().Text(fact.Value).AddClass("FactTitle").AddClass("NoSeparation"));
        }

        protected override HtmlTag Render(FactSet factSet, object context)
        {
            var uiFactSet = (TableTag)new TableTag()
                .AddClass(factSet.Type)
                .Style("overflow", "hidden");

            foreach (var fact in factSet.Facts)
            {
                var uiElements = Render(fact, context);
                var uiRow = uiFactSet.AddBodyRow();
                uiRow.Cell().AddClass("FactName").Append(uiElements.Item1);
                uiRow.Cell().AddClass("FactValue").Append(uiElements.Item2);
            }
            return uiFactSet;
        }

        protected override HtmlTag Render(TextBlock textBlock, object context)
        {
            var uiTextBlock = new DivTag()
                .AddClass(textBlock.Type)
                .Style("text-align", textBlock.HorizontalAlignment.ToString().ToLower())
                .Style("overflow", "hidden");

            if (textBlock.Color != TextColor.Default)
            {
                uiTextBlock = uiTextBlock.AddClass($"{textBlock.Color}");
            }
            if (textBlock.Weight != TextWeight.Normal)
            {
                uiTextBlock = uiTextBlock.AddClass($"{textBlock.Weight}");
            }
            if (textBlock.Size != TextSize.Normal)
            {
                uiTextBlock = uiTextBlock.AddClass($"{textBlock.Size}");
            }

            if (textBlock.Wrap == false)
            {
                uiTextBlock = uiTextBlock
                    .Style("white-space", "nowrap")
                    .Style("text-overflow", "ellipsis");
            }

            if (textBlock.IsSubtle)
            {
                uiTextBlock = uiTextBlock.AddClass("Subtle");
            }

            Marked marked = new Marked();
            marked.Options.Mangle = false;
            marked.Options.Sanitize = true;

            string html = marked.Parse(RendererUtilities.ApplyTextFunctions(textBlock.Text)).Replace("<p>", "<p style='margin-top: 0px;margin-bottom: 0px'>");
            var uiPara = new LiteralTag(html)
                .Style("margin-top", "0px")
                .Style("margin-bottom", "0px");
            uiTextBlock.Children.Add(uiPara);
            return uiTextBlock;
        }

        protected override HtmlTag Render(Image image, object context)
        {
            var uiImage = new HtmlTag("img")
                .AddClass(image.Type)
                .AddClass($"{image.Size}")
                .AddClass($"{image.Style}")
                .Attr("src", image.Url);

            switch (image.HorizontalAlignment)
            {
                case HorizontalAlignment.Left:
                    uiImage = uiImage.Style("overflow", "hidden")
                        .Style("display", "block");
                    break;
                case HorizontalAlignment.Center:
                    uiImage = uiImage.Style("overflow", "hidden")
                        .Style("margin-right", "auto")
                        .Style("margin-left", "auto")
                        .Style("display", "block");
                    break;
                case HorizontalAlignment.Right:
                    uiImage = uiImage.Style("overflow", "hidden")
                        .Style("margin-left", "auto")
                        .Style("display", "block");
                    break;
            }

            if (this.Options.SupportInteraction && image.SelectAction != null)
            {
                //var uiButton = (Button)RenderAction(image.SelectAction, context);
                //if (uiButton != null)
                //{
                //    uiButton.Content = uiImage;
                //    uiButton.Style = this.GetStyle("Adaptive.Action.Tap");
                //    return uiButton;
                //}
            }
            return uiImage;
        }

        protected override HtmlTag Render(ImageSet imageSet, object context)
        {
            var uiImageSet = new DivTag()
                .AddClass(imageSet.Type);

            foreach (var image in imageSet.Images)
            {
                var uiImage = this.Render(image, context);
                if (imageSet.ImageSize != ImageSize.Auto)
                {
                    uiImage = uiImage.RemoveClass(ImageSize.Auto.ToString())
                        .RemoveClass($"{ImageSize.Stretch}")
                        .RemoveClass($"{ImageSize.Small}")
                        .RemoveClass($"{ImageSize.Medium}")
                        .RemoveClass($"{ImageSize.Large}")
                        .AddClass($"{imageSet.ImageSize}");
                }
                uiImageSet.Children.Add(uiImage);
            }
            return uiImageSet;
        }

        protected override HtmlTag Render(InputChoiceSet choiceSet, object context)
        {
            string choiceText = this.GetFallbackText(choiceSet);
            if (choiceText == null)
            {
                List<string> choices = choiceSet.Choices.Select(choice => choice.Title).ToList();
                if (choiceSet.Style == ChoiceInputStyle.Compact)
                {
                    if (choiceSet.IsMultiSelect)
                    {
                        choiceText = $"Choices: {JoinString(choices, ", ", " and ")}";
                    }
                    else
                    {
                        choiceText = $"Choices: {JoinString(choices, ", ", " or ")}";
                    }
                }
                else // if (this.Style == ChoiceInputStyle.Expanded)
                {
                    choiceText = $"* {JoinString(choices, "\n* ", "\n* ")}";
                }
            }
            Container container = new Container() { Separation = choiceSet.Separation };
            container.Items.Add(new TextBlock()
            {
                Text = choiceText,
                Wrap = true
            });
            container.Items.Add(new TextBlock()
            {
                Text = JoinString(choiceSet.Choices.Where(c => c.IsSelected).Select(c => c.Title).ToList(), ", ", " and "),
                Color = TextColor.Accent,
                Wrap = true
            });
            return Render(container, context);
        }

        protected override HtmlTag Render(InputDate input, object context)
        {
            Container container = new Container() { Separation = input.Separation };
            container.Items.Add(new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder });
            if (input.Value != null)
            {

                container.Items.Add(new TextBlock()
                {
                    Text = input.Value,
                    Color = TextColor.Accent,
                    Wrap = true
                });
            }
            return Render(container, context);
        }

        protected override HtmlTag Render(InputNumber input, object context)
        {
            Container container = new Container() { Separation = input.Separation };
            container.Items.Add(new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder });
            if (input.Value != null)
            {
                container.Items.Add(new TextBlock()
                {
                    Text = input.Value,
                    Color = TextColor.Accent,
                    Wrap = true
                });
            }
            return Render(container, context);
        }

        protected override HtmlTag Render(InputText input, object context)
        {
            Container container = new Container() { Separation = input.Separation };
            container.Items.Add(new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder });
            if (input.Value != null)
            {

                container.Items.Add(new TextBlock()
                {
                    Text = input.Value,
                    Color = TextColor.Accent,
                    Wrap = true
                });
            }
            return Render(container, context);
        }

        protected override HtmlTag Render(InputTime input, object context)
        {
            Container container = new Container() { Separation = input.Separation };
            container.Items.Add(new TextBlock() { Text = GetFallbackText(input) ?? input.Placeholder });
            if (input.Value != null)
            {
                container.Items.Add(new TextBlock()
                {
                    Text = input.Value,
                    Color = TextColor.Accent,
                    Wrap = true
                });
            }
            return Render(container, context);
        }

        protected override HtmlTag Render(InputToggle input, object context)
        {
            Container container = new Container() { Separation = input.Separation };
            container.Items.Add(new TextBlock() { Text = GetFallbackText(input) });
            if (input.Value != null)
            {
                container.Items.Add(new TextBlock()
                {
                    Text = (input.Value == (input.ValueOn ?? "true")) ? input.ValueOn ?? "selected" : input.ValueOff ?? "not selected",
                    Color = TextColor.Accent,
                    Wrap = true
                });
            }
            return Render(container, context);
        }

        protected string GetFallbackText(CardElement cardElement)
        {
            if (!string.IsNullOrEmpty(cardElement.Speak))
            {

                // TODO: Fix xamarin fallback
                var doc = new System.Xml.XmlDocument();
                var xml = cardElement.Speak;
                if (!xml.Trim().StartsWith("<"))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<Speak>{xml}</Speak>";
                else if (!xml.StartsWith("<?xml "))
                    xml = $"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n{xml}";
                doc.LoadXml(xml);
                return doc.InnerText;
            }
            return null;
        }

    }
}
