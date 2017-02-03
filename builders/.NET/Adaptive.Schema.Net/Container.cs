using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Container for a collection of elements
    /// </summary>
    public class Container : TypedElement
    {
        public Container()
        { }

        // Issue:  Should this be Elements?  
        public List<CardElement> Items { get; set; } = new List<CardElement>();

        /// <summary>
        /// Image to use for the background of a card
        /// </summary>
        public string BackgroundImageUrl { get; set; }

        /// <summary>
        /// Background color to use for the card
        /// </summary>
        // ISSUE: Why is this a string?  
        public string BackgroundColor { get; set; }
    }
}
