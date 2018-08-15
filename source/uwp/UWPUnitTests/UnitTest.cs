
using System;
using System.Threading;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Collections.ObjectModel;
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.ApplicationModel.Core;
using Windows.UI.Core;
using Windows.Storage;
using Windows.ApplicationModel;
using AdaptiveCards.Rendering.Uwp;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;

namespace UWPUnitTests
{
    [TestClass]
    public class UnitTest
    {
        public TestContext TestContext { get; set; }

        private EventWaitHandle _testCompleted = new ManualResetEvent(false);
        private Exception _exceptionThrown = null;
        private StorageFolder _tempResultsFolder;
        private StorageFolder _sourceHostConfigsFolder;
        private StorageFolder _sourceCardsFolder;
        private StorageFolder _expectedFolder;
        private int _count = 0;

        [ClassInitialize]
        static public async Task Init(TestContext context)
        {
            StorageFolder expectedFolder = await Package.Current.InstalledLocation.GetFolderAsync("Expected");

            context.Properties.Add("ExpectedFolder", expectedFolder);
            context.Properties.Add("ResultsFolder", await ApplicationData.Current.TemporaryFolder.CreateFolderAsync("Results", CreationCollisionOption.OpenIfExists));
            context.Properties.Add("SourceHostConfigsFolder", await expectedFolder.CreateFolderAsync("SourceHostConfigs", CreationCollisionOption.OpenIfExists));
            context.Properties.Add("SourceCardsFolder", await expectedFolder.CreateFolderAsync("SourceCards", CreationCollisionOption.OpenIfExists));
        }

        [TestMethod]
        //[DataRow(1, 2, 3, DisplayName = "FooBar")]
        //[DataRow(4, 5, 6, DisplayName = "BarFoo")]
        //[DataSource("Microsoft.VisualStudio.TestTools.DataSource.XML", "D:\\AdaptiveCards\\source\\uwp\\UWPUnitTests\\Cards.xml", "Row", DataAccessMethod.Sequential)]
        public async Task TestMethod()
        {
            _expectedFolder = (TestContext.Properties["ExpectedFolder"] as StorageFolder);
            _tempResultsFolder = (TestContext.Properties["ResultsFolder"] as StorageFolder);
            _sourceCardsFolder = (TestContext.Properties["SourceCardsFolder"] as StorageFolder);
            _sourceHostConfigsFolder = (TestContext.Properties["SourceHostConfigsFolder"] as StorageFolder);

            ObservableCollection<FileViewModel> cards = new ObservableCollection<FileViewModel>();
            ObservableCollection<FileViewModel> hostConfigs = new ObservableCollection<FileViewModel>();

            await FileLoadHelpers.LoadAsync(cards, hostConfigs);

            uint count = 0;
            foreach (var hostConfig in hostConfigs)
            {
                foreach (var card in cards)
                {
                    _count++;
                    await TestCardInDispatcher(hostConfig, card);
                }
            }

            _count++;
        }

        public async Task TestCardInDispatcher(FileViewModel hostConfig, FileViewModel card)
        {
            _exceptionThrown = null;
            var dispatcher = CoreApplication.MainView.CoreWindow.Dispatcher;

            _testCompleted.Reset();

            // Need to move the test to the UI Thread
            await dispatcher.RunAsync(CoreDispatcherPriority.Normal, async () =>
            {
                try
                {
                    await TestCard(hostConfig, card);
                }
                catch (Exception e)
                {
                    _exceptionThrown = e;
                }
                finally
                {
                    _testCompleted.Set();
                }
            });

            _testCompleted.WaitOne();
            if (_exceptionThrown != null)
            {
                throw new Exception("Test Failed", _exceptionThrown);
            }
        }

        async public Task TestCard(FileViewModel hostConfigFile, FileViewModel cardFile)
        {
            var renderResult = await UWPTestLibrary.RenderTestHelpers.RenderCard(cardFile, hostConfigFile);

            UWPTestLibrary.ImageWaiter imageWaiter = new ImageWaiter(renderResult.Item3);

            Border border = new Border();
            border.Width = renderResult.Item4;
            border.Child = renderResult.Item3;
            (Window.Current.Content as Frame).Content = border;

            await imageWaiter.WaitOnAllImagesAsync();

            StorageFile imageResultFile = null;
            StorageFile jsonResultFile = null;
            if (renderResult.Item1 == null)
            {
                imageResultFile = await _tempResultsFolder.CreateFileAsync("Result.png", CreationCollisionOption.GenerateUniqueName);
                jsonResultFile = await _tempResultsFolder.CreateFileAsync("Result.json", CreationCollisionOption.GenerateUniqueName);

                await UWPTestLibrary.RenderTestHelpers.ResultsToFile(imageResultFile, jsonResultFile, renderResult.Item2, renderResult.Item3);
            }

            await Task.Delay(10);

            var result = await TestResultViewModel.CreateAsync(
                cardFile: cardFile,
                hostConfigFile: hostConfigFile,
                actualError: renderResult.Item1,
                actualImageFile: imageResultFile,
                actualJsonFile: jsonResultFile,
                xamlCard: renderResult.Item3,
                expectedFolder: _expectedFolder,
                sourceHostConfigsFolder: _sourceHostConfigsFolder,
                sourceCardsFolder: _sourceCardsFolder);

            if ((result.Status != TestStatus.Passed) && 
                (result.Status != TestStatus.PassedButSourceWasChanged))
            {
                await result.SaveAsNewExpectedAsync();

                throw new Exception();
            }

            return;
        }
    }
}
