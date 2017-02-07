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
using System.Windows.Navigation;
using System.Windows.Shapes;
using ADP = Adaptive.Schema.Net;
using Newtonsoft.Json;
using Microsoft.Win32;
using System.IO;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void textBox_TextChanged(object sender, TextChangedEventArgs e)
        {
            var renderer = new AdaptiveXamlRenderer(this.Resources);
            try
            {
                this.card.Children.Clear();
                var aCard = JsonConvert.DeserializeObject<ADP.AdaptiveCard>(this.textBox.Text);
                var element = renderer.Render(aCard);
                this.card.Children.Add(element);
            }
            catch (Exception err)
            {
                this.card.Children.Clear();
                this.card.Children.Add(new TextBlock() { Text = err.Message });
            }
        }

        private void loadButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                this.textBox.Text = File.ReadAllText(dlg.FileName);
            }
        }
    }
}
