// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Threading;
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Core;
using Windows.Storage;
using Windows.UI.Core;
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
        public async Task TestAllCards()
        {
            _expectedFolder = (TestContext.Properties["ExpectedFolder"] as StorageFolder);
            _tempResultsFolder = (TestContext.Properties["ResultsFolder"] as StorageFolder);
            _sourceCardsFolder = (TestContext.Properties["SourceCardsFolder"] as StorageFolder);
            _sourceHostConfigsFolder = (TestContext.Properties["SourceHostConfigsFolder"] as StorageFolder);

            ObservableCollection<FileViewModel> cards = new ObservableCollection<FileViewModel>();
            ObservableCollection<FileViewModel> hostConfigs = new ObservableCollection<FileViewModel>();

            await FileLoadHelpers.LoadAsync(cards, hostConfigs);

            List<Exception> exceptions = new List<Exception>();
            foreach (var hostConfig in hostConfigs)
            {
                foreach (var card in cards)
                {
                    try
                    {
                        await TestCardInDispatcher(hostConfig, card);
                    }
                    catch (Exception thrown)
                    {
                        exceptions.Add(thrown);
                    }
                }
            }

            if (exceptions.Count != 0)
            {
                string message = string.Empty;
                foreach (var e in exceptions)
                {
                    message += $"{e.Message}{Environment.NewLine}";
                }

                throw new Exception($"Test failed with {exceptions.Count} failures.{Environment.NewLine}{message}");
            }
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
                throw new Exception(_exceptionThrown.Message, _exceptionThrown);
            }
        }

        async public Task TestCard(FileViewModel hostConfigFile, FileViewModel cardFile)
        {
            uint reruns = 0;
            TestResultViewModel result = null;
            bool retryImage = true;
            bool testPass = false;

            while (retryImage)
            {
                var renderResult = await UWPTestLibrary.RenderTestHelpers.RenderCard(cardFile, hostConfigFile);

                if (renderResult.Tree != null)
                {
                    UWPTestLibrary.ImageWaiter imageWaiter = new ImageWaiter(renderResult.Tree);

                    StackPanel stackPanel = new StackPanel();
                    stackPanel.Children.Add(renderResult.Tree);

                    Border border = new Border();
                    border.Width = renderResult.CardWidth;
                    border.Child = stackPanel;

                    ScrollViewer scrollViewer = new ScrollViewer();
                    scrollViewer.Content = border;

                    (Window.Current.Content as Frame).Content = scrollViewer;

                    await imageWaiter.WaitOnAllImagesAsync();

                }

                StorageFile imageResultFile = null;
                StorageFile jsonResultFile = null;
                if (renderResult.Error == null)
                {
                    imageResultFile = await _tempResultsFolder.CreateFileAsync("Result.png", CreationCollisionOption.GenerateUniqueName);
                    jsonResultFile = await _tempResultsFolder.CreateFileAsync("Result.json", CreationCollisionOption.GenerateUniqueName);

                    await UWPTestLibrary.RenderTestHelpers.ResultsToFile(imageResultFile, jsonResultFile, renderResult.RoundTrippedJSON, renderResult.Tree);
                }

                await Task.Delay(10);

                result = await TestResultViewModel.CreateAsync(
                    cardFile: cardFile,
                    hostConfigFile: hostConfigFile,
                    renderedTestResult: renderResult,
                    actualImageFile: imageResultFile,
                    actualJsonFile: jsonResultFile,
                    expectedFolder: _expectedFolder,
                    sourceHostConfigsFolder: _sourceHostConfigsFolder,
                    sourceCardsFolder: _sourceCardsFolder);

                testPass = result.Status.IsPassingStatus() && result.Status.OriginalMatched;

                if(!testPass)
                {
                    // Retry if we failed on image matching for an unchanged card to allow for
                    // occasional differences in image rendering
                    retryImage = result.Status.OriginalMatched && !result.Status.ImageMatched && (reruns < 3);
                    reruns++;
                }
                else
                {
                    retryImage = false;
                }
            }

            if (!testPass)
            {
                throw new Exception(result.Status.ToString() + ": " + result.HostConfigName + "\\" + result.CardName);
            }
        }
    }
}
