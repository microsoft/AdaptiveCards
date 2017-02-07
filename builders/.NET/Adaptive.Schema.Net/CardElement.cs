using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Newtonsoft.Json.Converters;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Base class for all elements in a container
    /// </summary>
    public class CardElement : TypedElement
    {
        public CardElement() : base()
        {
        }

        /// <summary>
        /// SSML fragment for spoken interaction
        /// </summary>
        public string Speak { get; set; }

        /// <summary>
        /// Size hint for the element
        /// </summary>
        public Size Size { get; set; } = Size.Auto;

        /// <summary>
        /// Horizontal alignment for element
        /// </summary>
        public HorizontalAlignment HorizontalAlignment { get; set; } = HorizontalAlignment.Left;
    }
}


