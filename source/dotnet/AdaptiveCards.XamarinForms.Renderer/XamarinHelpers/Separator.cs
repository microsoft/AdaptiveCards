using Xamarin.Forms;

namespace Adaptive
{
    public class Separator : BoxView
    {
        public static readonly BindableProperty VerticalAlignmentProperty = BindableProperty.Create(
            propertyName: nameof(Style),
            returnType: typeof(LayoutOptions),
            declaringType: typeof(Separator));

        public LayoutOptions VerticalAlignment
        {
            get { return (LayoutOptions)GetValue(VerticalAlignmentProperty); }
            set { SetValue(VerticalAlignmentProperty, value); }
        }

        public Separator()
        {
            Color = Color.Black;
            WidthRequest = 100;
            HeightRequest = 2;
        }
    }
}