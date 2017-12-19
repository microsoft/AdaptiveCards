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
                VisitImage((AdaptiveContainer)parent, (AdaptiveImage) adaptiveElement);

            if (adaptiveElement is AdaptiveTextBlock)
                VisitTextBlock((AdaptiveContainer)parent, (AdaptiveTextBlock) adaptiveElement);

            // includes Column
            if (adaptiveElement is AdaptiveContainer)
                VisitContainer((AdaptiveContainer)parent, (AdaptiveContainer)adaptiveElement);
            
            if (adaptiveElement is AdaptiveColumnSet)
                VisitColumnSet((AdaptiveContainer)parent, (AdaptiveColumnSet) adaptiveElement);

            if (adaptiveElement is AdaptiveImageSet)
                VisitImageSet((AdaptiveContainer)parent, (AdaptiveImageSet) adaptiveElement);

            if (adaptiveElement is AdaptiveFactSet)
                VisitFactSet((AdaptiveContainer)parent, (AdaptiveFactSet) adaptiveElement);

            if (adaptiveElement is AdaptiveChoiceSetInput)
                VisitChoiceSetInput((AdaptiveContainer)parent, (AdaptiveChoiceSetInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTextInput)
                VisitTextInput((AdaptiveContainer)parent, (AdaptiveTextInput) adaptiveElement);

            if (adaptiveElement is AdaptiveNumberInput)
                VisitNumberInput((AdaptiveContainer)parent, (AdaptiveNumberInput) adaptiveElement);

            if (adaptiveElement is AdaptiveDateInput)
                VisitDateInput((AdaptiveContainer)parent, (AdaptiveDateInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTimeInput)
                VisitTimeInput((AdaptiveContainer)parent, (AdaptiveTimeInput) adaptiveElement);

            if (adaptiveElement is AdaptiveToggleInput)
                VisitToggleInput((AdaptiveContainer)parent, (AdaptiveToggleInput) adaptiveElement);
        }

        public virtual void VisitCard(AdaptiveCard card)
        {
            foreach (var item in card.Body)
                Visit(null, item);

            foreach (var action in card.Actions)
                VisitAction(null, action);
        }

        public virtual void VisitContainer(AdaptiveContainer parent, AdaptiveContainer container)
        {
            foreach (var item in container.Items)
                Visit(container, item);
        }

        public virtual void VisitColumnSet(AdaptiveContainer parent, AdaptiveColumnSet columnSet)
        {
            foreach (var column in columnSet.Columns)
                Visit(columnSet, column);
        }

        public virtual void VisitFactSet(AdaptiveContainer parent, AdaptiveFactSet factSet)
        {
            foreach (var fact in factSet.Facts)
                VisitFact(factSet, fact);
        }

        public virtual void VisitImageSet(AdaptiveContainer parent, AdaptiveImageSet imageSet)
        {
            foreach (var image in imageSet.Images)
                Visit(imageSet, image);
        }

        public virtual void VisitTextBlock(AdaptiveContainer parent, AdaptiveTextBlock textBlock)
        {
        }

        public virtual void VisitImage(AdaptiveContainer parent, AdaptiveImage image)
        {
        }

        public virtual void VisitFact(AdaptiveFactSet parent, AdaptiveFact fact)
        {
        }

        public virtual void VisitTextInput(AdaptiveContainer parent, AdaptiveTextInput inputText)
        {
        }

        public virtual void VisitDateInput(AdaptiveContainer parent, AdaptiveDateInput inputDate)
        {
        }

        public virtual void VisitNumberInput(AdaptiveContainer parent, AdaptiveNumberInput inputNumber)
        {
        }

        public virtual void VisitTimeInput(AdaptiveContainer parent, AdaptiveTimeInput inputTime)
        {
        }

        public virtual void VisitToggleInput(AdaptiveContainer parent, AdaptiveToggleInput inputToggle)
        {
        }

        public virtual void VisitChoiceSetInput(AdaptiveContainer parent, AdaptiveChoiceSetInput adaptiveChoiceSetInput)
        {
        }

        public virtual void VisitAction(AdaptiveTypedElement parent, AdaptiveAction action)
        {
            if (action is AdaptiveOpenUrlAction)
                VisitOpenUrlAction(parent, (AdaptiveOpenUrlAction) action);
            if (action is AdaptiveSubmitAction)
                VisitSubmitAction(parent, (AdaptiveSubmitAction) action);
            if (action is AdaptiveShowCardAction)
                VisitShowCardAction(parent, (AdaptiveShowCardAction) action);
        }

        public virtual void VisitSubmitAction(AdaptiveTypedElement parent, AdaptiveSubmitAction action)
        {
        }

        public virtual void VisitOpenUrlAction(AdaptiveTypedElement parent, AdaptiveOpenUrlAction action)
        {
        }

        public virtual void VisitShowCardAction(AdaptiveTypedElement parent, AdaptiveShowCardAction action)
        {
            VisitCard(action.Card);
        }
    }
}