using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveElementDefinition
    {
        public AdaptiveElement Element { get; set; }

        private ElementRepeater _elementRepeater;
        public AdaptiveElement GetNewElement()
        {
            if (Element == null)
            {
                return null;
            }

            if (_elementRepeater == null)
            {
                _elementRepeater = new ElementRepeater(Element);
            }

            return _elementRepeater.GetNewElement() as AdaptiveElement;
        }
    }
}
