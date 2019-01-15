using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class ResolveContext
    {
        public AdaptiveElementDefinitions Elements { get; set; } = new AdaptiveElementDefinitions();

        private void Populate(AdaptiveTypedElement element)
        {
            if (element.Elements != null)
            {
                foreach (var el in element.Elements)
                {
                    Elements[el.Key] = el.Value;
                }
            }
        }

        public static ResolveContext Create(AdaptiveTypedElement element)
        {
            var answer = new ResolveContext();
            answer.Populate(element);
            return answer;
        }

        public ResolveContext CreateForCurrElement(AdaptiveTypedElement currElement)
        {
            var answer = Clone();
            answer.Populate(currElement);
            return answer;
        }

        private ResolveContext Clone()
        {
            return new ResolveContext()
            {
                Elements = new AdaptiveElementDefinitions(Elements)
            };
        }
    }
}
