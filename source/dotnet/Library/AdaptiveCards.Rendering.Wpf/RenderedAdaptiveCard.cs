using System;
using System.Collections;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Windows;
using Newtonsoft.Json.Linq;

namespace AdaptiveCards.Rendering.Wpf
{
    public class RenderedAdaptiveCard : RenderedAdaptiveCardBase
    {
        public RenderedAdaptiveCard(FrameworkElement frameworkElement, AdaptiveCard originatingCard)
            : base(originatingCard)
        {
            FrameworkElement = frameworkElement;
        }

        /// <summary>
        /// The rendered result. If there were errors present, this will be null.
        /// </summary>
        public FrameworkElement FrameworkElement { get; }

        internal Dictionary<string, Func<object>> InputBindings { get; set; } = new Dictionary<string, Func<object>>();


        /// <summary>
        /// Event handler for when user invokes an action.
        /// </summary>
        public event TypedEventHandler<RenderedAdaptiveCard, AdaptiveActionEventArgs> OnAction;

        internal void InvokeOnAction(AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(this, args);
        }

        /// <summary>
        /// Gather the current values from any inputs on the card
        /// </summary>
        public AdaptiveInputs GetUserInputs(InputValueMode mode)
        {
            return new AdaptiveInputs(this, mode);
        }

        public class AdaptiveInputs : IReadOnlyDictionary<string, string>
        {
            private readonly RenderedAdaptiveCard _card;
            private readonly InputValueMode _valueMode;
            private IReadOnlyDictionary<string, string> _readOnlyDictionaryImplementation;

            public AdaptiveInputs(RenderedAdaptiveCard card, InputValueMode valueMode)
            {
                _card = card;
                _valueMode = valueMode;
                //_readOnlyDictionaryImplementation = new ReadOnlyDictionary<string, string>(card.InputBindings);
            }


            public JObject AsJson()
            {
                var jObj = new JObject();
                foreach (var id in _card.InputBindings.Keys)
                {
                    var value = _card.InputBindings[id]();
                    if (value != null)
                    {
                        jObj[id] = JToken.FromObject(value);
                    }
                }
                return jObj;

            }

            public IEnumerator<KeyValuePair<string, string>> GetEnumerator()
            {
                return _readOnlyDictionaryImplementation.GetEnumerator();
            }

            IEnumerator IEnumerable.GetEnumerator()
            {
                return ((IEnumerable)_readOnlyDictionaryImplementation).GetEnumerator();
            }

            public int Count
            {
                get { return _readOnlyDictionaryImplementation.Count; }
            }

            public bool ContainsKey(string key)
            {
                return _readOnlyDictionaryImplementation.ContainsKey(key);
            }

            public bool TryGetValue(string key, out string value)
            {
                return _readOnlyDictionaryImplementation.TryGetValue(key, out value);
            }

            public string this[string key]
            {
                get { return _readOnlyDictionaryImplementation[key]; }
            }

            public IEnumerable<string> Keys
            {
                get { return _readOnlyDictionaryImplementation.Keys; }
            }

            public IEnumerable<string> Values
            {
                get { return _readOnlyDictionaryImplementation.Values; }
            }
        }


    }

    public enum InputValueMode
    {
        /// <summary>
        /// All inputs will have their values returned as a string
        /// </summary>
        RawString
    }
}
