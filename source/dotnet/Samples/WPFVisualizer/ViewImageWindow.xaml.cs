// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System.IO;
using System.Windows;
using System.Windows.Media.Imaging;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ViewImageWindow.xaml
    /// </summary>
    public partial class ViewImageWindow : Window
    {
        public ViewImageWindow(Stream sourceImageStream)
        {
            InitializeComponent();

            var localStream = new MemoryStream();
            sourceImageStream.CopyTo(localStream);
            localStream.Position = 0;
            var source = new BitmapImage();
            source.BeginInit();
            source.StreamSource = localStream;
            source.EndInit();
            PreviewImage.Source = source;
        }
    }
}
