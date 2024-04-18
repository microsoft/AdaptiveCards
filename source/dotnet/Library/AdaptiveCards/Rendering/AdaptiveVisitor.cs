// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards;
using System.Collections.Generic;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public HashSet<AdaptiveTypedElement> Elements { get; set; } = new HashSet<AdaptiveTypedElement>();

        public virtual void Visit(AdaptiveElement adaptiveElement)
        {
            if (adaptiveElement is AdaptiveImage image)
                Visit(image);

            else if (adaptiveElement is AdaptiveTextBlock textBlock)
                Visit(textBlock);

            // includes Column
            else if (adaptiveElement is AdaptiveContainer container)
                Visit(container);

            else if (adaptiveElement is AdaptiveColumnSet set)
                Visit(set);

            else if (adaptiveElement is AdaptiveImageSet imageSet)
                Visit(imageSet);

            else if (adaptiveElement is AdaptiveFactSet factSet)
                Visit(factSet);

            else if (adaptiveElement is AdaptiveChoiceSetInput input)
                Visit(input);

            else if (adaptiveElement is AdaptiveTextInput textInput)
                Visit(textInput);

            else if (adaptiveElement is AdaptiveNumberInput numberInput)
                Visit(numberInput);

            else if (adaptiveElement is AdaptiveDateInput dateInput)
                Visit(dateInput);

            else if (adaptiveElement is AdaptiveTimeInput timeInput)
                Visit(timeInput);

            else if (adaptiveElement is AdaptiveToggleInput toggleInput)
                Visit(toggleInput);

            else if (adaptiveElement is AdaptiveMedia media)
                Visit(media);

            else if (adaptiveElement is AdaptiveActionSet actionSet)
                Visit(actionSet);

            else if (adaptiveElement is AdaptiveRichTextBlock rtb)
                Visit(rtb);

            else if (adaptiveElement is AdaptiveTable table)
                Visit(table);
        }

        public virtual void Visit(AdaptiveCard card)
        {
            if (card == null)
            {
                return;
            }

            Elements.Add(card);

            foreach (var item in card.Body)
            {
                Visit(item);
            }

            foreach (var action in card.Actions)
            {
                Visit(action);
            }

            if (card.SelectAction != null)
            {
                Visit(card.SelectAction);
            }

            if (card.Refresh != null)
            {
                Visit(card.Refresh);
            }
        }

        public virtual void Visit(AdaptiveContainer container)
        {
            Elements.Add(container);

            foreach (var item in container.Items)
            {
                Visit(item);
            }

            if (container.SelectAction != null)
            {
                Visit(container.SelectAction);
            }
        }

        public virtual void Visit(AdaptiveColumnSet columnSet)
        {
            Elements.Add(columnSet);

            foreach (var column in columnSet.Columns)
            {
                Visit(column);
            }

            if (columnSet.SelectAction != null)
            {
                Visit(columnSet.SelectAction);
            }
        }

        public virtual void Visit(AdaptiveFactSet factSet)
        {
            Elements.Add(factSet);

            foreach (var fact in factSet.Facts)
            {
                Visit(fact);
            }
        }

        public virtual void Visit(AdaptiveImageSet imageSet)
        {
            Elements.Add(imageSet);

            foreach (var image in imageSet.Images)
            {
                Visit(image);
            }
        }

        public virtual void Visit(AdaptiveTextBlock textBlock)
        {
            Elements.Add(textBlock);
        }

        public virtual void Visit(AdaptiveImage image)
        {
            Elements.Add(image);

            if (image.SelectAction != null)
            {
                Visit(image.SelectAction);
            }
        }

        public virtual void Visit(AdaptiveFact fact)
        {
        }

        public virtual void Visit(AdaptiveTextInput inputText)
        {
            Elements.Add(inputText);

            if (inputText.InlineAction != null)
            {
                Visit(inputText.InlineAction);
            }
        }

        public virtual void Visit(AdaptiveDateInput inputDate)
        {
            Elements.Add(inputDate);
        }

        public virtual void Visit(AdaptiveNumberInput inputNumber)
        {
            Elements.Add(inputNumber);
        }

        public virtual void Visit(AdaptiveTimeInput inputTime)
        {
            Elements.Add(inputTime);
        }

        public virtual void Visit(AdaptiveToggleInput inputToggle)
        {
            Elements.Add(inputToggle);
        }

        public virtual void Visit(AdaptiveChoiceSetInput adaptiveChoiceSetInput)
        {
            Elements.Add(adaptiveChoiceSetInput);
        }

        public virtual void Visit(AdaptiveActionSet actionSet)
        {
            Elements.Add(actionSet);
            foreach (var action in actionSet.Actions)
            {
                Visit(action);
            }
        }

        public virtual void Visit(AdaptiveAction action)
        {
            if (action is AdaptiveOpenUrlAction urlAction)
                Visit(urlAction);

            if (action is AdaptiveSubmitAction submitAction)
                Visit(submitAction);

            if (action is AdaptiveShowCardAction cardAction)
                Visit(cardAction);

            if (action is AdaptiveToggleVisibilityAction toggleVisibilityAction)
                Visit(toggleVisibilityAction);

            if (action is AdaptiveExecuteAction executeAction)
                Visit(executeAction);
        }

        public virtual void Visit(AdaptiveSubmitAction action)
        {
            Elements.Add(action);
        }

        public virtual void Visit(AdaptiveOpenUrlAction action)
        {
            Elements.Add(action);
        }

        public virtual void Visit(AdaptiveShowCardAction action)
        {
            Elements.Add(action);
            Visit(action.Card);
        }

        public virtual void Visit(AdaptiveToggleVisibilityAction action)
        {
            Elements.Add(action);

            foreach (var targetElement in action.TargetElements)
            {
                Visit(targetElement);
            }
        }

        public virtual void Visit(AdaptiveTargetElement targetElement)
        {

        }

        public virtual void Visit(AdaptiveExecuteAction action)
        {
            Elements.Add(action);
        }

        public virtual void Visit(AdaptiveMedia media)
        {
            Elements.Add(media);
        }

        public virtual void Visit(AdaptiveRichTextBlock rtb)
        {
            Elements.Add(rtb);

            foreach (var inline in rtb.Inlines)
            {
                Visit(inline);
            }
        }

        public virtual void Visit(AdaptiveInline inline)
        {
            if (inline is AdaptiveTextRun run)
            {
                Visit(run);
            }
        }

        public virtual void Visit(AdaptiveTextRun run)
        {
            if (run.SelectAction != null)
            {
                Visit(run.SelectAction);
            }
        }

        public virtual void Visit(AdaptiveRefresh refresh)
        {
            if (refresh.Action != null)
            {
                Visit(refresh.Action);
            }
        }

        public virtual void Visit(AdaptiveTable table)
        {
            Elements.Add(table);

            foreach (var col in table.Columns)
            {
                Visit(col);
            }

            foreach (var row in table.Rows)
            {
                Visit(row);
            }
        }

        public virtual void Visit(AdaptiveTableRow row)
        {
            foreach (var cell in row.Cells)
            {
                Visit(cell);
            }
        }

        public virtual void Visit(AdaptiveTableColumnDefinition col)
        {
        }

        public virtual void Visit(AdaptiveTableCell cell)
        {
            foreach (var item in cell.Items)
            {
                Visit(item);
            }
        }
    }
}

