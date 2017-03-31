using Xamarin.Forms;

namespace AdaptiveCards.Rendering
{

    public class FrameworkElement
    {
        private readonly Element _element;

        public FrameworkElement(Element element)
        {
            _element = element;
        }

        public object DataContext
        {
            get { return _element.BindingContext; }
            set { _element.BindingContext = value; }
        }

        public static implicit operator View(FrameworkElement v)
        {
            return (View)v._element;
        }

        public static implicit operator FrameworkElement(Element e)
        {
            return new FrameworkElement(e);
        }
    }
}