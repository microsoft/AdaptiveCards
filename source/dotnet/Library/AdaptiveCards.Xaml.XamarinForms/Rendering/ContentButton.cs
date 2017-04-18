using System;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    public class ContentButton : ContentView
    {
        public ContentButton()
        {
            this.GestureRecognizers.Add(new TapGestureRecognizer { Command = new Command(() => Click?.Invoke(this, EventArgs.Empty)) } );
        }
        public event EventHandler Click;

        public string Text
        {
            get { return (Content as TextBox)?.Text; }
            set
            {
                var textBox = Content as TextBox;
                if(textBox == null)
                {
                    Content = textBox = new TextBox();
                }
                textBox.Text = value;
            }
        }
    }
}
