// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Rendering
{
    /// <summary>
    /// Provides access to the input fields on a card
    /// </summary>
    public class RenderedAdaptiveCardInputs
    {
        private readonly IDictionary<string, Func<string>> _inputBindings;

        public RenderedAdaptiveCardInputs(IDictionary<string, Func<string>> inputBindings = null)
        {
            _inputBindings = inputBindings;
        }

        /// <summary>
        /// Read the input fields as a JSON object. All input values will serialize to strings
        /// </summary>
        /// <returns></returns>
        public JObject AsJson()
        {
            return JObject.FromObject(AsDictionary());
        }

        /// <summary>
        /// Read the input fields as a Dictionary. All input values will serialize the strings
        /// </summary>
        /// <returns></returns>
        public IReadOnlyDictionary<string, string> AsDictionary()
        {
            var dic = new Dictionary<string, string>();
            foreach (var id in _inputBindings.Keys)
            {
                var value = _inputBindings[id]();
                if (value != null)
                {
                    dic[id] = value;
                }
            }

            return dic;
        }
    }
}
