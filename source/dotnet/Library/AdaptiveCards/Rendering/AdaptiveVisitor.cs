namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public virtual void Visit(AdaptiveElement adaptiveElement)
        {
            if (adaptiveElement is AdaptiveImage)
                Visit((AdaptiveImage) adaptiveElement);

            if (adaptiveElement is AdaptiveTextBlock)
                Visit((AdaptiveTextBlock) adaptiveElement);

            // includes Column
            if (adaptiveElement is AdaptiveContainer)
                Visit((AdaptiveContainer)adaptiveElement);
            
            if (adaptiveElement is AdaptiveColumnSet)
                Visit((AdaptiveColumnSet) adaptiveElement);

            if (adaptiveElement is AdaptiveImageSet)
                Visit((AdaptiveImageSet) adaptiveElement);

            if (adaptiveElement is AdaptiveFactSet)
                Visit((AdaptiveFactSet) adaptiveElement);

            if (adaptiveElement is AdaptiveChoiceSetInput)
                Visit((AdaptiveChoiceSetInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTextInput)
                Visit((AdaptiveTextInput) adaptiveElement);

            if (adaptiveElement is AdaptiveNumberInput)
                Visit((AdaptiveNumberInput) adaptiveElement);

            if (adaptiveElement is AdaptiveDateInput)
                Visit((AdaptiveDateInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTimeInput)
                Visit((AdaptiveTimeInput) adaptiveElement);

            if (adaptiveElement is AdaptiveToggleInput)
                Visit((AdaptiveToggleInput) adaptiveElement);
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

        public virtual void Visit(AdaptiveActionBase action)
        {
            if (action is AdaptiveOpenUrlAction)
                Visit((AdaptiveOpenUrlAction) action);
            if (action is AdaptiveSubmitAction)
                Visit((AdaptiveSubmitAction) action);
            if (action is AdaptiveShowCardAction)
                Visit((AdaptiveShowCardAction) action);
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
    }
}