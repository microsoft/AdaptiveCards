using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using AdaptiveCards;

namespace AdaptiveCards.Renderers
{
    /// <summary>
    /// Utility class which allows you to visit every node
    /// </summary>
    public class AdaptiveVisitor
    {
        public AdaptiveVisitor()
        {
        }

        public virtual void Visit(CardElement cardElement)
        {
            if (cardElement is Image)
                Visit((Image)cardElement);

            if (cardElement is TextBlock)
                Visit((TextBlock)cardElement);

            if (cardElement is Container)
                Visit((Container)cardElement);

            if (cardElement is ColumnSet)
                Visit((ColumnSet)cardElement);

            if (cardElement is ImageSet)
                Visit((ImageSet)cardElement);

            if (cardElement is FactSet)
                Visit((FactSet)cardElement);

            if (cardElement is InputChoiceSet)
                Visit((InputChoiceSet)cardElement);

            if (cardElement is InputText)
                Visit((InputText)cardElement);

            if (cardElement is InputNumber)
                Visit((InputNumber)cardElement);

            if (cardElement is InputDate)
                Visit((InputDate)cardElement);

            if (cardElement is InputTime)
                Visit((InputTime)cardElement);

            if (cardElement is InputToggle)
                Visit((InputToggle)cardElement);
        }

        public virtual void Visit(AdaptiveCard card)
        {
            foreach (var item in card.Body)
                Visit(item);
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

        public virtual void Visit(Column column)
        {
            foreach (var item in column.Items)
                Visit(item);
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

        public virtual void Visit(InputText inputText)
        {
        }

        public virtual void Visit(InputDate inputDate)
        {
        }

        public virtual void Visit(InputNumber inputNumber)
        {
        }

        public virtual void Visit(InputTime inputTime)
        {
        }

        public virtual void Visit(InputToggle inputToggle)
        {
        }

        public virtual void Visit(InputChoiceSet choiceSet)
        {
        }

        public virtual void Visit(ActionBase action)
        {
            if (action is ActionHttp)
                Visit((ActionHttp)action);
            if (action is ActionOpenUrl)
                Visit((ActionOpenUrl)action);
            if (action is ActionSubmit)
                Visit((ActionSubmit)action);
            if (action is ActionShowCard)
                Visit((ActionShowCard)action);
        }

        public virtual void Visit(ActionHttp action)
        {
        }

        public virtual void Visit(ActionSubmit action)
        {
        }

        public virtual void Visit(ActionOpenUrl action)
        {
        }

        public virtual void Visit(ActionShowCard action)
        {
        }
    }
}
