namespace Xamarin.Forms
{
    public class TextBox : Entry
    {
        public bool AcceptsReturn
        {
            get; set;
        }

        public object DataContext
        {
            get { return BindingContext; }
            set { BindingContext = value; }
        }
    }
}