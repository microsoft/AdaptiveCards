using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using AdaptiveCards.XamlCardRenderer;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace XamlCardVisualizer
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            // Construct a temporary object model tree until the parser is available
            AdaptiveCard card = new AdaptiveCard();
            AdaptiveTextBlock textBlock1 = new AdaptiveTextBlock();
            textBlock1.Text = "Hello";
            card.Items.Add(textBlock1);
            AdaptiveTextBlock textBlock2 = new AdaptiveTextBlock();
            textBlock2.Text = "World";
            card.Items.Add(textBlock2);

            AdaptiveCards.XamlCardRenderer.XamlCardRenderer renderer = new AdaptiveCards.XamlCardRenderer.XamlCardRenderer();
            this.renderedXamlPresenter.Content = renderer.RenderCardAsXaml(card);
        }
    }
}
