namespace Xamarin.Forms
{
    public class Rectangle : BoxView
    {
        public static readonly BindableProperty VerticalAlignmentProperty = BindableProperty.Create(
            propertyName: nameof(Style),
            returnType: typeof(LayoutOptions),
            declaringType: typeof(Rectangle));

        public LayoutOptions VerticalAlignment
        {
            get { return (LayoutOptions)GetValue(VerticalAlignmentProperty); }
            set { SetValue(VerticalAlignmentProperty, value); }
        }

        public Rectangle()
        {
            Color = Color.Black;
            WidthRequest = 100;
            HeightRequest = 2;
        }
    }
}