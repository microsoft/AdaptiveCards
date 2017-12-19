using AdaptiveCards;
using AdaptiveCards.Rendering;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace LiveCardAPI
{
    public class SetEventsVisitor : AdaptiveVisitor
    {
        public override void Visit(AdaptiveTypedElement parent, AdaptiveElement adaptiveElement)
        {
            adaptiveElement.SetEvents();
            base.Visit(parent, adaptiveElement);
        }
    }
}