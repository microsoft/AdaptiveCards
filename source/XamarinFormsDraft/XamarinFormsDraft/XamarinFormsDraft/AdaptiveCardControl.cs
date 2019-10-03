using System;
using System.Collections.Generic;
using System.Text;
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

        /*
        public EventHandler OnAction(object sender, EventArgs eventArgs)
        {
        }
        */

    }
}
