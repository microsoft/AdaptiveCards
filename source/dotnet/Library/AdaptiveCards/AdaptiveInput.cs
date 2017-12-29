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
        private event EventHandler _OnFocus;
        public event EventHandler OnFocus
        {
            add { _OnFocus += value; this.Events.Add(EventTypes.OnFocus); }
            remove { _OnFocus -= value; this.Events.Remove(EventTypes.OnFocus); }
        }

        private event EventHandler _OnBlur;
        public event EventHandler OnBlur
        {
            add { _OnBlur += value; this.Events.Add(EventTypes.OnBlur); }
            remove { _OnBlur -= value; this.Events.Remove(EventTypes.OnBlur); }
        }

        private event EventHandler<TextChangedEventArgs> _OnTextChanged;
        public event EventHandler<TextChangedEventArgs> OnTextChanged
        {
            add { _OnTextChanged += value; this.Events.Add(EventTypes.OnTextChanged); }
            remove { _OnTextChanged -= value; this.Events.Add(EventTypes.OnTextChanged); }
        }

        private event EventHandler<KeyEventArgs> _OnKey;
        public event EventHandler<KeyEventArgs> OnKey
        {
            add { _OnKey += value; this.Events.Add(EventTypes.OnKey); }
            remove { _OnKey -= value; this.Events.Add(EventTypes.OnKey); }
        }

        private event EventHandler<SelectionChangedEventArgs> _OnSelectionChanged;
        public event EventHandler<SelectionChangedEventArgs> OnSelectionChanged
        {
            add { _OnSelectionChanged += value; this.Events.Add(EventTypes.OnSelectionChanged); }
            remove { _OnSelectionChanged -= value; this.Events.Add(EventTypes.OnSelectionChanged); }
        }

        public void FireFocus()
        {
            _OnFocus?.Invoke(this, new EventArgs());
        }

        public void FireBlur()
        {
            _OnBlur?.Invoke(this, new EventArgs());
        }

        public void FireTextChanged(string text)
        {
            _OnTextChanged?.Invoke(this, new TextChangedEventArgs() { Text = text });
        }

        public void FireKey(string key)
        {
            _OnKey?.Invoke(this, new KeyEventArgs() { Key = key });
        }

        public void FireSelectionChanged(int[] selections)
        {
            _OnSelectionChanged?.Invoke(this, new SelectionChangedEventArgs() { Selection = selections });
        }


        /// <summary>
        ///     The input must have a value for it to be part of a Submit or Http action
        /// </summary>
        [Obsolete("Ths IsRequired property is not supported in Adaptive Cards yet and will be ignored")]
        public bool IsRequired { get { return _IsRequired; } set { SetPropertyValue(ref _IsRequired, value); } }
        private bool _IsRequired;

    }

}