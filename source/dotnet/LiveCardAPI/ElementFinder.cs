using AdaptiveCards;
using AdaptiveCards.Rendering;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace LiveCardAPI
{
    public class ElementFinder : AdaptiveVisitor
    {

        private string id;

        public ElementFinder(string id)
        {
            this.id = id;
        }

        public object Parent { get; set; }

        public AdaptiveElement Element { get; set; }

        public override void Visit(AdaptiveTypedElement parent, AdaptiveElement adaptiveElement)
        {
            if (adaptiveElement.Id == this.id)
            {
                this.Parent = parent;
                this.Element = adaptiveElement;
                return; // no need to keep traversing
            }
            base.Visit(parent, adaptiveElement);
        }
    }
}