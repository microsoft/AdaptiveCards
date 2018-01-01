using AdaptiveCards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public class AdaptiveElementMemory : ProcessedMemory<AdaptiveTypedElement>
    {
        public AdaptiveElementMemory() : base(Identity)
        {

        }

        private static string Identity(AdaptiveTypedElement element)
        {
            if (Guid.TryParse(element.Id, out Guid guid))
                return element.Id;
            return $"{element.Id}-{element.GetHashCode().ToString("x")}";
        }
    }
}
