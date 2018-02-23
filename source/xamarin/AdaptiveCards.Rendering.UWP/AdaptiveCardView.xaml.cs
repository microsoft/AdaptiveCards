using System;
using System.Collections.Generic;
using System.ComponentModel;
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
using AdaptiveCards.Rendering.UWP.Helpers;
using AdaptiveCards.Rendering.UWP.ViewModel;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace AdaptiveCards.Rendering.UWP
{
    public sealed partial class AdaptiveCardView : UserControl
    {
        public AdaptiveCardView ViewModel
        {
            get { return DataContext as AdaptiveCardView; }
        }

        public AdaptiveCardView()
        {
            this.InitializeComponent();
        }
    }
}
