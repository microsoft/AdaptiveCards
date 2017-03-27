using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards.Renderers
{
    public abstract class AdaptiveRenderer<TUIElement, TContext>
        where TUIElement : class 
        where TContext : class
    {
        public AdaptiveRenderer(RenderOptions options)
        {
            this.Options = options;
        }

        public RenderOptions Options { get; set; }

        // containers
        protected virtual TUIElement Render(CardElement cardElement, TContext context)
        {
            if (cardElement is Image)
                return Render((Image)cardElement, context);

            if (cardElement is TextBlock)
                return Render((TextBlock)cardElement, context);

            if (cardElement is Container)
                return Render((Container)cardElement, context);

            if (cardElement is ColumnSet)
                return Render((ColumnSet)cardElement, context);

            if (cardElement is ImageSet)
                return Render((ImageSet)cardElement, context);

            if (cardElement is FactSet)
                return Render((FactSet)cardElement, context);

            if (cardElement is InputChoiceSet)
                return Render((InputChoiceSet)cardElement, context);

            if (cardElement is InputText)
                return Render((InputText)cardElement, context);

            if (cardElement is InputNumber)
                return Render((InputNumber)cardElement, context);

            if (cardElement is InputDate)
                return Render((InputDate)cardElement, context);

            if (cardElement is InputTime)
                return Render((InputTime)cardElement, context);

            if (cardElement is InputToggle)
                return Render((InputToggle)cardElement, context);

            return null;
        }

        protected abstract TUIElement Render(AdaptiveCard card, TContext context);
        protected abstract TUIElement Render(Container container, TContext context);
        protected abstract TUIElement Render(ColumnSet columnSet, TContext context);
        protected abstract TUIElement Render(Column column, TContext context);
        protected abstract TUIElement Render(FactSet factSet, TContext context);
        protected abstract TUIElement Render(ImageSet imageSet, TContext context);

        // elements
        protected abstract TUIElement Render(TextBlock textBlock, TContext context);
        protected abstract TUIElement Render(Image image, TContext context);
        protected abstract Tuple<TUIElement, TUIElement> Render(Fact fact, TContext context);

        // input
        protected abstract TUIElement Render(InputText inputText, TContext context);
        protected abstract TUIElement Render(InputDate inputDate, TContext context);
        protected abstract TUIElement Render(InputNumber inputNumber, TContext context);
        protected abstract TUIElement Render(InputTime inputTime, TContext context);
        protected abstract TUIElement Render(InputToggle inputToggle, TContext context);
        protected abstract TUIElement Render(InputChoiceSet choiceSet, TContext context);

        // actions
        protected virtual TUIElement RenderAction(ActionBase action, TContext context)
        {
            if (action is ActionSubmit)
                return this.Render((ActionSubmit)action, context);
            if (action is ActionHttp)
                return this.Render((ActionHttp)action, context);
            if (action is ActionOpenUrl)
                return this.Render((ActionOpenUrl)action, context);
            if (action is ActionShowCard)
                return this.Render((ActionShowCard)action, context);
            return null;
        }

        protected abstract TUIElement Render(ActionHttp action, TContext context);
        protected abstract TUIElement Render(ActionSubmit action, TContext context);
        protected abstract TUIElement Render(ActionOpenUrl action, TContext context);
        protected abstract TUIElement Render(ActionShowCard action, TContext context);

        protected string JoinString(IList<string> choices, string sep, string last)
        {
            StringBuilder sb = new StringBuilder();
            string s = string.Empty;
            for (int i = 0; i < choices.Count - 1; i++)
            {
                sb.Append(s);
                sb.Append(choices[i]);
                s = sep;
            }
            if (choices.Count > 1)
                sb.Append(last);
            sb.Append(choices.Last());
            return sb.ToString();
        }

    }
}
