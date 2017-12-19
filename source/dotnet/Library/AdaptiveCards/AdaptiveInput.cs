using System;
using System.Collections.Generic;
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
        public event EventHandler OnFocus;
        public event EventHandler OnBlur;
        public event EventHandler<TextChangedEventArgs> OnTextChanged;
        public event EventHandler<KeyEventArgs> OnKey;
        public event EventHandler<SelectionChangedEventArgs> OnSelectionChanged;

        public void Focus()
        {
            OnFocus?.Invoke(this, new EventArgs());
        }

        public void Blur()
        {
            OnBlur?.Invoke(this, new EventArgs());
        }

        public void TextChanged(string text)
        {
            OnTextChanged?.Invoke(this, new TextChangedEventArgs() { Text = text });
        }

        public void Key(string key)
        {
            OnKey?.Invoke(this, new KeyEventArgs() { Key = key });
        }
        public void SelectionChanged(int[] selections)
        {
            OnSelectionChanged?.Invoke(this, new SelectionChangedEventArgs() { Selection = selections });
        }

        public override void SetEvents(List<string> events = null)
        {
            if (events == null)
                events = new List<string>();
            if (this.OnFocus != null)
                events.Add(EventTypes.OnFocus);
            if (this.OnBlur != null)
                events.Add(EventTypes.OnBlur);
            if (this.OnTextChanged != null)
                events.Add(EventTypes.OnTextChanged);
            if (this.OnKey != null)
                events.Add(EventTypes.OnKey);
            if (this.OnSelectionChanged != null)
                events.Add(EventTypes.OnSelectionChanged);
            base.SetEvents(events);
        }

        /// <summary>
        ///     The input must have a value for it to be part of a Submit or Http action
        /// </summary>
        [Obsolete("Ths IsRequired property is not supported in Adaptive Cards yet and will be ignored")]
        public bool IsRequired { get; set; }
    }

}