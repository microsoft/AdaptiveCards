// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.Collections.Generic;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public HashSet<AdaptiveTypedElement> Elements { get; set; } = new HashSet<AdaptiveTypedElement>();

        public virtual void Visit(AdaptiveTypedElement adaptiveElement)
        {
            if (adaptiveElement is AdaptiveCard card)
                Visit(card);

            else if (adaptiveElement is AdaptiveImage image)
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

        protected virtual void Visit(AdaptiveCard card)
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

        protected virtual void Visit(AdaptiveSelectAction selectAction)
        {
            Visit(selectAction.Action);
        }

        protected virtual void Visit(AdaptiveContainer container)
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

        protected virtual void Visit(AdaptiveColumnSet columnSet)
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

        protected virtual void Visit(AdaptiveFactSet factSet)
        {
            Elements.Add(factSet);

            foreach (var fact in factSet.Facts)
            {
                Visit(fact);
            }
        }

        protected virtual void Visit(AdaptiveImageSet imageSet)
        {
            Elements.Add(imageSet);

            foreach (var image in imageSet.Images)
            {
                Visit(image);
            }
        }

        protected virtual void Visit(AdaptiveTextBlock textBlock)
        {
            Elements.Add(textBlock);
        }

        protected virtual void Visit(AdaptiveImage image)
        {
            Elements.Add(image);

            if (image.SelectAction != null)
            {
                Visit(image.SelectAction);
            }
        }

        protected virtual void Visit(AdaptiveFact fact)
        {
        }

        protected virtual void Visit(AdaptiveTextInput inputText)
        {
            Elements.Add(inputText);

            if (inputText.InlineAction != null)
            {
                Visit(inputText.InlineAction);
            }
        }

        protected virtual void Visit(AdaptiveDateInput inputDate)
        {
            Elements.Add(inputDate);
        }

        protected virtual void Visit(AdaptiveNumberInput inputNumber)
        {
            Elements.Add(inputNumber);
        }

        protected virtual void Visit(AdaptiveTimeInput inputTime)
        {
            Elements.Add(inputTime);
        }

        protected virtual void Visit(AdaptiveToggleInput inputToggle)
        {
            Elements.Add(inputToggle);
        }

        protected virtual void Visit(AdaptiveChoiceSetInput adaptiveChoiceSetInput)
        {
            Elements.Add(adaptiveChoiceSetInput);
        }

        protected virtual void Visit(AdaptiveActionSet actionSet)
        {
            Elements.Add(actionSet);
            foreach (var action in actionSet.Actions)
            {
                Visit(action);
            }
        }

        protected virtual void Visit(AdaptiveAction action)
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

        protected virtual void Visit(AdaptiveSubmitAction action)
        {
            Elements.Add(action);
        }

        protected virtual void Visit(AdaptiveOpenUrlAction action)
        {
            Elements.Add(action);
        }

        protected virtual void Visit(AdaptiveShowCardAction action)
        {
            Elements.Add(action);
            Visit(action.Card);
        }

        protected virtual void Visit(AdaptiveToggleVisibilityAction action)
        {
            Elements.Add(action);
        }

        protected virtual void Visit(AdaptiveExecuteAction action)
        {
            Elements.Add(action);
        }

        protected virtual void Visit(AdaptiveMedia media)
        {
            Elements.Add(media);
        }

        protected virtual void Visit(AdaptiveRichTextBlock rtb)
        {
            Elements.Add(rtb);

            foreach (var inline in rtb.Inlines)
            {
                Visit(inline);
            }
        }

        protected virtual void Visit(AdaptiveInline inline)
        {
            if (inline is AdaptiveTextRun run)
            {
                Visit(run);
            }
        }

        protected virtual void Visit(AdaptiveTextRun run)
        {
            if (run.SelectAction != null)
            {
                Visit(run.SelectAction);
            }
        }

        protected virtual void Visit(AdaptiveRefresh refresh)
        {
            if (refresh.Action != null)
            {
                Visit(refresh.Action);
            }
        }

        protected virtual void Visit(AdaptiveTable table)
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

        protected virtual void Visit(AdaptiveTableRow row)
        {
            foreach (var cell in row.Cells)
            {
                Visit(cell);
            }
        }

        protected virtual void Visit(AdaptiveTableColumn col)
        {
        }

        protected virtual void Visit(AdaptiveTableCell cell)
        {
            foreach (var item in cell.Items)
            {
                Visit(item);
            }
        }
    }
}
