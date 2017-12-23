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
                VisitImage(parent, (AdaptiveImage) adaptiveElement);

            if (adaptiveElement is AdaptiveTextBlock)
                VisitTextBlock(parent, (AdaptiveTextBlock) adaptiveElement);

            // includes Column
            if (adaptiveElement is AdaptiveContainer)
                VisitContainer(parent, (AdaptiveContainer)adaptiveElement);
            
            if (adaptiveElement is AdaptiveColumnSet)
                VisitColumnSet(parent, (AdaptiveColumnSet) adaptiveElement);

            if (adaptiveElement is AdaptiveImageSet)
                VisitImageSet(parent, (AdaptiveImageSet) adaptiveElement);

            if (adaptiveElement is AdaptiveFactSet)
                VisitFactSet(parent, (AdaptiveFactSet) adaptiveElement);

            if (adaptiveElement is AdaptiveChoiceSetInput)
                VisitChoiceSetInput(parent, (AdaptiveChoiceSetInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTextInput)
                VisitTextInput(parent, (AdaptiveTextInput) adaptiveElement);

            if (adaptiveElement is AdaptiveNumberInput)
                VisitNumberInput(parent, (AdaptiveNumberInput) adaptiveElement);

            if (adaptiveElement is AdaptiveDateInput)
                VisitDateInput(parent, (AdaptiveDateInput) adaptiveElement);

            if (adaptiveElement is AdaptiveTimeInput)
                VisitTimeInput(parent, (AdaptiveTimeInput) adaptiveElement);

            if (adaptiveElement is AdaptiveToggleInput)
                VisitToggleInput((AdaptiveContainer)parent, (AdaptiveToggleInput) adaptiveElement);
        }

        public virtual void VisitCard(AdaptiveCard card)
        {
            foreach (var item in card.Body)
                Visit(card, item);

            foreach (var action in card.Actions)
                VisitAction(card, action);
        }

        public virtual void VisitContainer(AdaptiveTypedElement parent, AdaptiveContainer container)
        {
            foreach (var item in container.Items)
                Visit(container, item);
        }

        public virtual void VisitColumnSet(AdaptiveTypedElement parent, AdaptiveColumnSet columnSet)
        {
            foreach (var column in columnSet.Columns)
                Visit(columnSet, column);
        }

        public virtual void VisitFactSet(AdaptiveTypedElement parent, AdaptiveFactSet factSet)
        {
            foreach (var fact in factSet.Facts)
                VisitFact(factSet, fact);
        }

        public virtual void VisitImageSet(AdaptiveTypedElement parent, AdaptiveImageSet imageSet)
        {
            foreach (var image in imageSet.Images)
                Visit(imageSet, image);
        }

        public virtual void VisitTextBlock(AdaptiveTypedElement parent, AdaptiveTextBlock textBlock)
        {
        }

        public virtual void VisitImage(AdaptiveTypedElement parent, AdaptiveImage image)
        {
        }

        public virtual void VisitFact(AdaptiveFactSet parent, AdaptiveFact fact)
        {
        }

        public virtual void VisitTextInput(AdaptiveTypedElement parent, AdaptiveTextInput inputText)
        {
        }

        public virtual void VisitDateInput(AdaptiveTypedElement parent, AdaptiveDateInput inputDate)
        {
        }

        public virtual void VisitNumberInput(AdaptiveTypedElement parent, AdaptiveNumberInput inputNumber)
        {
        }

        public virtual void VisitTimeInput(AdaptiveTypedElement parent, AdaptiveTimeInput inputTime)
        {
        }

        public virtual void VisitToggleInput(AdaptiveTypedElement parent, AdaptiveToggleInput inputToggle)
        {
        }

        public virtual void VisitChoiceSetInput(AdaptiveTypedElement parent, AdaptiveChoiceSetInput adaptiveChoiceSetInput)
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