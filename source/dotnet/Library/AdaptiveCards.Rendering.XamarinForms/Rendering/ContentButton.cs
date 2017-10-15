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
            get => TextBlock.Text;
            set => TextBlock.Text = value;
        }

        internal Xamarin.Forms.TextBlock TextBlock
        {
            get
            {
                var textblock = Content as Xamarin.Forms.TextBlock;
                if (textblock == null)
                {
                    Content = textblock = new Xamarin.Forms.TextBlock();
                }
                return textblock;
            }
        }
    }
}
