namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public virtual void Visit(AdaptiveTypedElement parent, AdaptiveElement adaptiveElement)
        {
            if (adaptiveElement is AdaptiveImage)
                Visit(parent, (AdaptiveImage) adaptiveElement);

            if (adaptiveElement is AdaptiveTextBlock)
                Visit(parent, (AdaptiveTextBlock) adaptiveElement);

            // includes Column
            if (adaptiveElement is AdaptiveContainer)
                Visit(parent, (AdaptiveContainer)adaptiveElement);
            
            if (adaptiveElement is AdaptiveColumnSet)
                Visit(parent, (AdaptiveColumnSet) adaptiveElement);

            if (adaptiveElement is AdaptiveImageSet)
                Visit(parent, (AdaptiveImageSet) adaptiveElement);

            if (adaptiveElement is AdaptiveFactSet)
                Visit(parent, (AdaptiveFactSet) adaptiveElement);

            if (adaptiveElement is AdaptiveChoiceSetInput)
                Visit(parent, (AdaptiveChoiceSetInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTextInput)
                Visit(parent, (AdaptiveTextInput) adaptiveElement);

            if (adaptiveElement is AdaptiveNumberInput)
                Visit(parent, (AdaptiveNumberInput) adaptiveElement);

            if (adaptiveElement is AdaptiveDateInput)
                Visit(parent, (AdaptiveDateInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTimeInput)
                Visit(parent, (AdaptiveTimeInput) adaptiveElement);

            if (adaptiveElement is AdaptiveToggleInput)
                Visit(parent, (AdaptiveToggleInput) adaptiveElement);
        }

        public virtual void Visit(AdaptiveCard card)
        {
            foreach (var item in card.Body)
                Visit(card, item);

            foreach (var action in card.Actions)
                Visit(card, action);
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveContainer container)
        {
            foreach (var item in container.Items)
                Visit(container, item);
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveColumnSet columnSet)
        {
            foreach (var column in columnSet.Columns)
                Visit(columnSet, column);
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveFactSet factSet)
        {
            foreach (var fact in factSet.Facts)
                Visit(factSet, fact);
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveImageSet imageSet)
        {
            foreach (var image in imageSet.Images)
                Visit(imageSet, image);
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveTextBlock textBlock)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveImage image)
        {
        }

        public virtual void Visit(AdaptiveFactSet parent, AdaptiveFact fact)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveTextInput inputText)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveDateInput inputDate)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveNumberInput inputNumber)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveTimeInput inputTime)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveToggleInput inputToggle)
        {
        }

        public virtual void Visit(AdaptiveContainer parent, AdaptiveChoiceSetInput adaptiveChoiceSetInput)
        {
        }

        public virtual void Visit(AdaptiveTypedElement parent, AdaptiveAction action)
        {
            if (action is AdaptiveOpenUrlAction)
                Visit(parent, (AdaptiveOpenUrlAction) action);
            if (action is AdaptiveSubmitAction)
                Visit(parent, (AdaptiveSubmitAction) action);
            if (action is AdaptiveShowCardAction)
                Visit(parent, (AdaptiveShowCardAction) action);
        }

        public virtual void Visit(AdaptiveTypedElement parent, AdaptiveSubmitAction action)
        {
        }

        public virtual void Visit(AdaptiveTypedElement parent, AdaptiveOpenUrlAction action)
        {
        }

        public virtual void Visit(AdaptiveTypedElement parent, AdaptiveShowCardAction action)
        {
            Visit(action.Card);
        }
    }
}