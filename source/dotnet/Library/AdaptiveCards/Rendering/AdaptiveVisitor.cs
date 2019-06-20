// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public virtual void Visit(AdaptiveElement adaptiveElement)
        {
            if (adaptiveElement is AdaptiveImage image)
                Visit(image);

            if (adaptiveElement is AdaptiveTextBlock textBlock)
                Visit(textBlock);

            // includes Column
            if (adaptiveElement is AdaptiveContainer container)
                Visit(container);

            if (adaptiveElement is AdaptiveColumnSet set)
                Visit(set);

            if (adaptiveElement is AdaptiveImageSet imageSet)
                Visit(imageSet);

            if (adaptiveElement is AdaptiveFactSet factSet)
                Visit(factSet);

            if (adaptiveElement is AdaptiveChoiceSetInput input)
                Visit(input);

            if (adaptiveElement is AdaptiveTextInput textInput)
                Visit(textInput);

            if (adaptiveElement is AdaptiveNumberInput numberInput)
                Visit(numberInput);

            if (adaptiveElement is AdaptiveDateInput dateInput)
                Visit(dateInput);

            if (adaptiveElement is AdaptiveTimeInput timeInput)
                Visit(timeInput);

            if (adaptiveElement is AdaptiveToggleInput toggleInput)
                Visit(toggleInput);

            if (adaptiveElement is AdaptiveMedia media)
                Visit(media);

            if (adaptiveElement is AdaptiveActionSet actionSet)
                Visit(actionSet);
        }

        public virtual void Visit(AdaptiveCard card)
        {
            foreach (var item in card.Body)
                Visit(item);

            foreach (var action in card.Actions)
                Visit(action);
        }

        public virtual void Visit(AdaptiveContainer container)
        {
            foreach (var item in container.Items)
                Visit(item);
        }

        public virtual void Visit(AdaptiveColumnSet columnSet)
        {
            foreach (var column in columnSet.Columns)
                Visit(column);
        }

        public virtual void Visit(AdaptiveFactSet factSet)
        {
            foreach (var fact in factSet.Facts)
                Visit(fact);
        }

        public virtual void Visit(AdaptiveImageSet imageSet)
        {
            foreach (var image in imageSet.Images)
                Visit(image);
        }

        public virtual void Visit(AdaptiveTextBlock textBlock)
        {
        }

        public virtual void Visit(AdaptiveImage image)
        {
        }

        public virtual void Visit(AdaptiveFact fact)
        {
        }

        public virtual void Visit(AdaptiveTextInput inputText)
        {
        }

        public virtual void Visit(AdaptiveDateInput inputDate)
        {
        }

        public virtual void Visit(AdaptiveNumberInput inputNumber)
        {
        }

        public virtual void Visit(AdaptiveTimeInput inputTime)
        {
        }

        public virtual void Visit(AdaptiveToggleInput inputToggle)
        {
        }

        public virtual void Visit(AdaptiveChoiceSetInput adaptiveChoiceSetInput)
        {
        }

        public virtual void Visit(AdaptiveActionSet actionSet)
        {
            foreach (var action in actionSet.Actions)
                Visit(action);
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
        }

        public virtual void Visit(AdaptiveSubmitAction action)
        {
        }

        public virtual void Visit(AdaptiveOpenUrlAction action)
        {
        }

        public virtual void Visit(AdaptiveShowCardAction action)
        {
            Visit(action.Card);
        }

        public virtual void Visit(AdaptiveMedia media)
        {
        }
    }
}
