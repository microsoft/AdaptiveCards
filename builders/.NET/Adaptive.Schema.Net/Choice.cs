using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Adaptive.Schema.Net
{
    /// <summary>
    /// Choice as part of a MultichoiceInput element
    /// </summary>
    public class Choice 
    {
        public Choice()
        { }

        /// <summary>
        /// Display text for the choice
        /// </summary>
        public string Display { get; set; }

        /// <summary>
        /// Internal value which will be collected as input if the choice is selected
        /// </summary>
        public string Value { get; set; }

        /// <summary>
        /// (OPTIONAL) Speech description of the choice
        /// </summary>
        // ISSUE: I think we need speak here...
        public string Speak { get; set; }
    }
}
