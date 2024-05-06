// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards;
using System.Collections.Generic;
using System.ComponentModel;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {

        /// <summary>
        /// A hashset of each object found while visiting. This is useful for finding an element using Linq
        /// </summary>
        public HashSet<AdaptiveTypedElement> Elements { get; set; } = new HashSet<AdaptiveTypedElement>();

        /// <summary>
        /// Visit an element
        /// </summary>
        /// <param name="adaptiveElement"></param>
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

        /// <summary>
        /// Visit a card
        /// </summary>
        /// <param name="card"></param>
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

        /// <summary>
        /// Visit a container
        /// </summary>
        /// <param name="container"></param>
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

        /// <summary>
        /// Visit a columnSet
        /// </summary>
        /// <param name="columnSet"></param>
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

        /// <summary>
        /// Visit a factset
        /// </summary>
        /// <param name="factSet"></param>
        public virtual void Visit(AdaptiveFactSet factSet)
        {
            Elements.Add(factSet);

            foreach (var fact in factSet.Facts)
            {
                Visit(fact);
            }
        }

        /// <summary>
        /// Visit an imagesset.
        /// </summary>
        /// <param name="imageSet"></param>
        public virtual void Visit(AdaptiveImageSet imageSet)
        {
            Elements.Add(imageSet);

            foreach (var image in imageSet.Images)
            {
                Visit(image);
            }
        }

        /// <summary>
        /// Visit a textblock
        /// </summary>
        /// <param name="textBlock"></param>
        public virtual void Visit(AdaptiveTextBlock textBlock)
        {
            Elements.Add(textBlock);
        }

        /// <summary>
        /// Visit a image
        /// </summary>
        /// <param name="image"></param>
        public virtual void Visit(AdaptiveImage image)
        {
            Elements.Add(image);

            if (image.SelectAction != null)
            {
                Visit(image.SelectAction);
            }
        }

        /// <summary>
        /// Visit a Fact.
        /// </summary>
        /// <param name="fact"></param>
        public virtual void Visit(AdaptiveFact fact)
        {
        }

        /// <summary>
        /// Visit a textInput
        /// </summary>
        /// <param name="inputText"></param>
        public virtual void Visit(AdaptiveTextInput inputText)
        {
            Elements.Add(inputText);

            if (inputText.InlineAction != null)
            {
                Visit(inputText.InlineAction);
            }
        }

        /// <summary>
        /// Visit a Date Input
        /// </summary>
        /// <param name="inputDate"></param>
        public virtual void Visit(AdaptiveDateInput inputDate)
        {
            Elements.Add(inputDate);
        }

        /// <summary>
        /// Visit a Number Input
        /// </summary>
        /// <param name="inputNumber"></param>
        public virtual void Visit(AdaptiveNumberInput inputNumber)
        {
            Elements.Add(inputNumber);
        }

        /// <summary>
        /// Visit a time input
        /// </summary>
        /// <param name="inputTime"></param>
        public virtual void Visit(AdaptiveTimeInput inputTime)
        {
            Elements.Add(inputTime);
        }

        /// <summary>
        /// Visit a toggle input
        /// </summary>
        /// <param name="inputToggle"></param>
        public virtual void Visit(AdaptiveToggleInput inputToggle)
        {
            Elements.Add(inputToggle);
        }

        /// <summary>
        /// Visit a choiceSet Input
        /// </summary>
        /// <param name="adaptiveChoiceSetInput"></param>
        public virtual void Visit(AdaptiveChoiceSetInput adaptiveChoiceSetInput)
        {
            Elements.Add(adaptiveChoiceSetInput);
        }

        /// <summary>
        /// Visit a actionSet
        /// </summary>
        /// <param name="actionSet"></param>
        public virtual void Visit(AdaptiveActionSet actionSet)
        {
            Elements.Add(actionSet);
            foreach (var action in actionSet.Actions)
            {
                Visit(action);
            }
        }

        /// <summary>
        /// Visit an action
        /// </summary>
        /// <param name="action"></param>
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

        /// <summary>
        /// Visit a submit action
        /// </summary>
        /// <param name="action"></param>
        public virtual void Visit(AdaptiveSubmitAction action)
        {
            Elements.Add(action);
        }

        /// <summary>
        /// Visit a OpenUrlAction
        /// </summary>
        /// <param name="action"></param>
        public virtual void Visit(AdaptiveOpenUrlAction action)
        {
            Elements.Add(action);
        }

        /// <summary>
        /// Visit a showCard action
        /// </summary>
        /// <param name="action"></param>
        public virtual void Visit(AdaptiveShowCardAction action)
        {
            Elements.Add(action);
            Visit(action.Card);
        }

        /// <summary>
        /// Visit a toggle visibility action.
        /// </summary>
        /// <param name="action"></param>
        public virtual void Visit(AdaptiveToggleVisibilityAction action)
        {
            Elements.Add(action);

            foreach (var targetElement in action.TargetElements)
            {
                Visit(targetElement);
            }
        }

        /// <summary>
        /// Visit a targetElement.
        /// </summary>
        /// <param name="targetElement"></param>
        public virtual void Visit(AdaptiveTargetElement targetElement)
        {

        }

        /// <summary>
        /// Visit a execute Action.
        /// </summary>
        /// <param name="action"></param>
        public virtual void Visit(AdaptiveExecuteAction action)
        {
            Elements.Add(action);
        }

        /// <summary>
        /// Visit a Media element
        /// </summary>
        /// <param name="media"></param>
        public virtual void Visit(AdaptiveMedia media)
        {
            Elements.Add(media);
        }

        /// <summary>
        /// Visit a RichTextBlock 
        /// </summary>
        /// <param name="rtb"></param>
        public virtual void Visit(AdaptiveRichTextBlock rtb)
        {
            Elements.Add(rtb);

            foreach (var inline in rtb.Inlines)
            {
                Visit(inline);
            }
        }

        /// <summary>
        /// Visit an Inline element
        /// </summary>
        /// <param name="inline"></param>
        public virtual void Visit(AdaptiveInline inline)
        {
            if (inline is AdaptiveTextRun run)
            {
                Visit(run);
            }
        }

        /// <summary>
        /// Visit a textRun
        /// </summary>
        /// <param name="run"></param>
        public virtual void Visit(AdaptiveTextRun run)
        {
            if (run.SelectAction != null)
            {
                Visit(run.SelectAction);
            }
        }

        /// <summary>
        /// Visit refresh
        /// </summary>
        /// <param name="refresh"></param>
        public virtual void Visit(AdaptiveRefresh refresh)
        {
            if (refresh.Action != null)
            {
                Visit(refresh.Action);
            }
        }

        /// <summary>
        /// Visit table
        /// </summary>
        /// <param name="table"></param>
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

        /// <summary>
        /// Visit TableRow
        /// </summary>
        /// <param name="row"></param>
        public virtual void Visit(AdaptiveTableRow row)
        {
            foreach (var cell in row.Cells)
            {
                Visit(cell);
            }
        }

        /// <summary>
        /// Visit TableColumnDefinition
        /// </summary>
        /// <param name="col"></param>
        public virtual void Visit(AdaptiveTableColumnDefinition col)
        {
        }

        /// <summary>
        /// Visit table cell
        /// </summary>
        /// <param name="cell"></param>
        public virtual void Visit(AdaptiveTableCell cell)
        {
            foreach (var item in cell.Items)
            {
                Visit(item);
            }

            if (cell.SelectAction != null)
            {
                Visit(cell.SelectAction);
            }
        }
    }
}

