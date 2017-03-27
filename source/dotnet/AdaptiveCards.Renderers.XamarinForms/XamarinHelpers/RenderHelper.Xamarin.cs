using System;
using Xamarin.Forms;
using UI = Xamarin.Forms;

namespace Adaptive
{
    public static class RenderHelper
    {
        public static void SetBackgroundImage(this Grid grid,  Uri uri)
        {
            grid.Children.Add(new UI.Image() { Source = ImageSource.FromUri(uri)});
        }

        public static void SetSource(this UI.Image image, Uri uri)
        {
            image.Source = ImageSource.FromUri(uri);
        }

        public static void SetHorizontalAlignment(this UI.Image image, HorizontalAlignment alignment)
        {
            switch (alignment)
            {
                case HorizontalAlignment.Left:
                    image.HorizontalOptions = LayoutOptions.Start;
                    break;

                case HorizontalAlignment.Center:
                    image.HorizontalOptions = LayoutOptions.Center;
                    break;

                case HorizontalAlignment.Right:
                    image.HorizontalOptions = LayoutOptions.End;
                    break;

                default:
                    image.HorizontalOptions = LayoutOptions.FillAndExpand; //images fill available width
                    break;
            }
        }
       
}
}