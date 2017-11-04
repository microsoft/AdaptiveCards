using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Rendering.Wpf
{
    public partial class RenderedAdaptiveCard
    {
        public class RenderedAdaptiveCardInputs : IReadOnlyDictionary<string, string>
        {
            private readonly IReadOnlyDictionary<string, string> _dictionary;

            public RenderedAdaptiveCardInputs(RenderedAdaptiveCard card)
            {
                if (card == null) throw new ArgumentNullException(nameof(card));

                var dic = new Dictionary<string, string>();
                foreach (var id in card.InputBindings.Keys)
                {
                    var value = card.InputBindings[id]();
                    if (value != null)
                    {
                        dic[id] = value.ToString();
                    }
                }

                _dictionary = new ReadOnlyDictionary<string, string>(dic);
            }

            public JObject AsJson()
            {
                return JObject.FromObject(_dictionary);
            }

            public IEnumerator<KeyValuePair<string, string>> GetEnumerator()
            {
                return _dictionary.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return ((IEnumerable)_dictionary).GetEnumerator();
            }

            public int Count
            {
                get { return _dictionary.Count; }
            }

            public bool ContainsKey(string key)
            {
                return _dictionary.ContainsKey(key);
            }

            public bool TryGetValue(string key, out string value)
            {
                return _dictionary.TryGetValue(key, out value);
            }

            public string this[string key]
            {
                get { return _dictionary[key]; }
            }

            public IEnumerable<string> Keys
            {
                get { return _dictionary.Keys; }
            }

            public IEnumerable<string> Values
            {
                get { return _dictionary.Values; }
            }
        }


    }
}
