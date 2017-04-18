namespace AdaptiveCards.Rendering
{
    /// <summary>
    ///     Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public virtual void Visit(CardElement cardElement)
        {
            if (cardElement is Image)
                Visit((Image) cardElement);

            if (cardElement is TextBlock)
                Visit((TextBlock) cardElement);

            // includes Column
            if (cardElement is Container)
                Visit((Container)cardElement);
            
            if (cardElement is ColumnSet)
                Visit((ColumnSet) cardElement);

            if (cardElement is ImageSet)
                Visit((ImageSet) cardElement);

            if (cardElement is FactSet)
                Visit((FactSet) cardElement);

            if (cardElement is ActionSet)
                Visit((ActionSet)cardElement);

            if (cardElement is ChoiceSet)
                Visit((ChoiceSet) cardElement);

            if (cardElement is TextInput)
                Visit((TextInput) cardElement);

            if (cardElement is NumberInput)
                Visit((NumberInput) cardElement);

            if (cardElement is DateInput)
                Visit((DateInput) cardElement);

            if (cardElement is TimeInput)
                Visit((TimeInput) cardElement);

            if (cardElement is ToggleInput)
                Visit((ToggleInput) cardElement);
        }

        public virtual void Visit(AdaptiveCard card)
        {
            foreach (var item in card.Body)
                Visit(item);

            foreach (var action in card.Actions)
                Visit(action);
        }

        public virtual void Visit(Container container)
        {
            foreach (var item in container.Items)
                Visit(item);
        }

        public virtual void Visit(ColumnSet columnSet)
        {
            foreach (var column in columnSet.Columns)
                Visit(column);
        }

        public virtual void Visit(ActionSet actionSet)
        {
            foreach (var action in actionSet.Actions)
                Visit(action);
        }

        public virtual void Visit(FactSet factSet)
        {
            foreach (var fact in factSet.Facts)
                Visit(fact);
        }

        public virtual void Visit(ImageSet imageSet)
        {
            foreach (var image in imageSet.Images)
                Visit(image);
        }

        public virtual void Visit(TextBlock textBlock)
        {
        }

        public virtual void Visit(Image image)
        {
        }

        public virtual void Visit(Fact fact)
        {
        }

        public virtual void Visit(TextInput inputText)
        {
        }

        public virtual void Visit(DateInput inputDate)
        {
        }

        public virtual void Visit(NumberInput inputNumber)
        {
        }

        public virtual void Visit(TimeInput inputTime)
        {
        }

        public virtual void Visit(ToggleInput inputToggle)
        {
        }

        public virtual void Visit(ChoiceSet choiceSet)
        {
        }

        public virtual void Visit(ActionBase action)
        {
            if (action is HttpAction)
                Visit((HttpAction) action);
            if (action is OpenUrlAction)
                Visit((OpenUrlAction) action);
            if (action is SubmitAction)
                Visit((SubmitAction) action);
            if (action is ShowCardAction)
                Visit((ShowCardAction) action);
        }

        public virtual void Visit(HttpAction action)
        {
        }

        public virtual void Visit(SubmitAction action)
        {
        }

        public virtual void Visit(OpenUrlAction action)
        {
        }

        public virtual void Visit(ShowCardAction action)
        {
            Visit(action.Card);
        }
    }
}