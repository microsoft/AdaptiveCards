using System;
using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{
    public class ContentButton : Button
    {
        public ContentButton()
        {

        }

        public object Content
        {
            get { return Text; }
            set { Text = value?.ToString(); }
        }

        public event EventHandler Click
        {
            add { Clicked += value; }
            remove { Clicked -= value; }
        }
    }
}
