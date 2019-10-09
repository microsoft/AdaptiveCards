using System;
using System.Collections.Generic;
using System.Text;
using Windows.Foundation;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering.XamarinForms
{
    public class AdaptiveCardControl : View
    {

        public static readonly BindableProperty CardProperty = BindableProperty.Create(
            propertyName: "Card",
            returnType: typeof(string),
            declaringType: typeof(AdaptiveCardControl),
            defaultValue: "");

        public string CardContent 
        {
            get { return (string)GetValue(CardProperty); }
            set { SetValue(CardProperty, value); }
        }

        public static readonly BindableProperty HostConfigProperty = BindableProperty.Create(
            propertyName: "HostConfig",
            returnType: typeof(string),
            declaringType: typeof(AdaptiveCardControl),
            defaultValue: "");

        public string HostConfig {
            get { return (string)GetValue(HostConfigProperty); }
            set { SetValue(HostConfigProperty, value); }
        }

        private EventHandler onAction;

        // This will be our default name in the meantime
        public event EventHandler OnAction
        {
            add
            {
                onAction -= value;
                onAction += value;
            }

            remove
            {
                onAction -= value;
            }
        }

        protected virtual void OnOnAction(EventArgs eventArgs)
        {
            EventHandler handler = onAction;

            handler?.Invoke(this, eventArgs);
        }
        public void SendActionEvent()
        {
            OnOnAction(EventArgs.Empty);
        }

    }
}
