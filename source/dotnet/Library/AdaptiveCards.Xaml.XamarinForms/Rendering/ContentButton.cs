using System;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    public class ContentButton : Frame
    {
        public ContentButton()
        {
            this.GestureRecognizers.Add(new TapGestureRecognizer { Command = new Command(() => Click?.Invoke(this, EventArgs.Empty)) } );

            this.CornerRadius = 9;


            base.HasShadow = false;
        }
        public event EventHandler Click;

        // Text is wrapped in a stacklayout, so to get this prop would mean walking
        // the children of that rather than accessing and overwriting
        //public string Text
        //{
        //    get => TextBlock.Text;
        //    set => TextBlock.Text = value;
        //}

        //internal AdaptiveCards.Xaml.XamarinForms.TextBlock TextBlock
        //{
        //    get
        //    {
        //        var textblock = Content as AdaptiveCards.Xaml.XamarinForms.TextBlock;
        //        if (textblock == null)
        //        {
        //            Content = textblock = new AdaptiveCards.Xaml.XamarinForms.TextBlock();
        //        }
        //        return textblock;
        //    }
        //}
    }
}
