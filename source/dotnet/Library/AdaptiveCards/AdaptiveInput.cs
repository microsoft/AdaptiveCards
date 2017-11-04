using System;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards
{
    /// <summary>
    ///     Input is used as part of a Form CardElement to collect information from a user
    /// </summary>
    public abstract class AdaptiveInput : AdaptiveElement
    {
        /// <summary>
        ///     The input must have a value for it to be part of a Submit or Http action
        /// </summary>
        [Obsolete("Ths IsRequired property is not supported in Adaptive Cards yet and will be ignored")]
        public bool IsRequired { get; set; }
    }

}