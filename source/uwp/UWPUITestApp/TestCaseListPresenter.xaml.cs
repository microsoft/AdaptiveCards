using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Input;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Navigation;

using System.Threading.Tasks;
using System.Collections.ObjectModel;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace UWPUITestApp
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class TestCaseListPresenter : Page
    {

        private static TestCaseListPresenter _Instance = null;
        public static TestCaseListPresenter Instance
        {
            get
            {
                if (_Instance == null)
                {
                    _Instance = new TestCaseListPresenter();
                }

                return _Instance;
            }
        }

        public MainPage MainPage { get; set; }

        public ObservableCollection<string> TestCases { get; set; } = new ObservableCollection<string>();

        public TestCaseListPresenter()
        {
            this.InitializeComponent();

            LoadTestCasesAsync();
        }

        internal void SetContainer(MainPage mainPage)
        {
            MainPage = mainPage;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            string buttonContent = (sender as Button)?.Content.ToString();

            MainPage.UpdateTitle(buttonContent);
            MainPage.ItemClicked(buttonContent);
        }

        private async Task LoadTestCasesAsync()
        {
            var testCasesFolder = await Package.Current.InstalledLocation.GetFolderAsync("LinkedTestCards");

            foreach (var file in await testCasesFolder.GetFilesAsync())
            {
                TestCases.Add(file.Name.Replace(".json", ""));
            }

            UpdateLayout();
        }
    }
}
