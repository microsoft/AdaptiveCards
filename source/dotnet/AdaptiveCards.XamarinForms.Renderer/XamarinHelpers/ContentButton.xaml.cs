using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using Xamarin.Forms;

namespace AdaptiveCards.XamarinForms.Renderer
{
    public partial class ContentButton : ContentView
    {
        public ContentButton()
        {
            InitializeComponent();
        }

        public event EventHandler Tapped;

        public static readonly BindableProperty CommandProperty = BindableProperty.Create(nameof(Command), typeof(ICommand), typeof(ContentButton));

        public ICommand Command
        {
            get { return (ICommand)GetValue(CommandProperty); }
            set { SetValue(CommandProperty, value); }
        }

        public event EventHandler<EventArgs> Click
        {
            add { throw new NotImplementedException(); }
            remove { throw new NotImplementedException(); }
        }

        private void TapGestureRecognizer_OnTapped(object sender, EventArgs e)
        {
            Tapped?.Invoke(this, new EventArgs());
        }
    }
}
