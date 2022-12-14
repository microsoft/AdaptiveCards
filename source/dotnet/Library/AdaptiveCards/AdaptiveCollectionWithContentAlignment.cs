// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

using System.Xml.Serialization;
using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.ComponentModel;
using System.Collections.Generic;
using System.Collections;

namespace AdaptiveCards
{
    /// <summary>
    /// AdaptiveCard element with content alignment properties
    /// </summary>
    public abstract class AdaptiveCollectionWithContentAlignment : AdaptiveElement, IEnumerable<AdaptiveElement>
    {
        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty("verticalCellContentAlignment", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveVerticalContentAlignment), "top")]
        public AdaptiveVerticalContentAlignment VerticalContentAlignment { get; set; }

        /// <summary>
        /// The content alignment for the TableCells inside the TableRow.
        /// </summary>
        [JsonProperty("horizontalCellContentAlignment", DefaultValueHandling = DefaultValueHandling.IgnoreAndPopulate)]
#if !NETSTANDARD1_3
        [XmlAttribute]
#endif
        [DefaultValue(typeof(AdaptiveHorizontalContentAlignment), "left")]
        public AdaptiveHorizontalContentAlignment HorizontalContentAlignment { get; set; }

        /// <summary>
        /// Returns enumerator
        /// </summary>
        /// <returns></returns>
        public abstract IEnumerator<AdaptiveElement> GetEnumerator();

        IEnumerator IEnumerable.GetEnumerator()
        {
            throw new System.NotImplementedException();
        }

        public void Add(AdaptiveElement element)
        {
            throw new System.NotImplementedException();
        }
    }
}
