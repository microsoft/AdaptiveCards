using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using Adaptive.Schema.Net;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ShowCardWindow.xaml
    /// </summary>
    public partial class ShowCardWindow : Window
    {
        public ShowCardWindow(AdaptiveCard card, ResourceDictionary resources)
        {
            InitializeComponent();
            var renderer = new AdaptiveXamlRenderer(resources);
            this.DataContext = this;
            this.Body.Children.Add(renderer.Render(card));
        }

        private void CloseWindow_Execute(object sender, ExecutedRoutedEventArgs e)
        {
            this.Close();
        }

        private void CloseWindow_CanExecute(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }
    }
}
