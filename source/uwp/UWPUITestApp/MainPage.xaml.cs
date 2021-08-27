// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

namespace UWPUITestApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();

            TestCaseListPresenter.Instance.SetContainer(this);
            CardPresenter.Instance.SetMainWindow(this);

            PagePresenter.Content = TestCaseListPresenter.Instance;
        }

        internal void ItemClicked(string testCaseName)
        {
            CardPresenter.Instance.TestCase = testCaseName;
            PagePresenter.Content = CardPresenter.Instance;
            HomeButton.Visibility = Visibility.Visible;
        }

        private void HomeButton_Click(object sender, RoutedEventArgs e)
        {
            PagePresenter.Content = TestCaseListPresenter.Instance;
            TitleTextBlock.Text = "Home";
            HomeButton.Visibility = Visibility.Collapsed;
        }

        internal void UpdateTitle(string newTitle)
        {
            TitleTextBlock.Text = newTitle;
        }
    }
}
