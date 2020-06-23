// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Threading.Tasks;
using UWPTestLibrary;
using Windows.ApplicationModel.UserActivities;
using Windows.Storage;
using Windows.UI.Shell;
using Windows.UI.Xaml;

namespace AdaptiveCardTestApp.ViewModels
{
    public class RunningTestsViewModel : BindableBase
    {
        public event EventHandler OnTestsCompleted;
        public event EventHandler<TestStatus> OnSingleTestCompleted;

        private StorageFolder _expectedFolder;
        private StorageFolder _sourceHostConfigsFolder;
        private StorageFolder _sourceCardsFolder;
        private string _currentCard;
        public string CurrentCard
        {
            get { return _currentCard; }
            set { SetProperty(ref _currentCard, value); }
        }

        private string _currentHostConfig;
        public string CurrentHostConfig
        {
            get { return _currentHostConfig; }
            set { SetProperty(ref _currentHostConfig, value); }
        }

        private FileViewModel[] _originalCards;
        public ObservableCollection<FileViewModel> RemainingCards { get; }
        public ObservableCollection<FileViewModel> RemainingHostConfigs { get; }

        private UIElement _currentCardVisual;
        private bool _addToTimeline;
        private UserActivitySession _currentSession;
        public UIElement CurrentCardVisual
        {
            get { return _currentCardVisual; }
            set { SetProperty(ref _currentCardVisual, value); }
        }

        private double _currentCardVisualWidth = 400;
        public double CurrentCardVisualWidth
        {
            get { return _currentCardVisualWidth; }
            set { SetProperty(ref _currentCardVisualWidth, value); }
        }

        private StorageFolder _tempResultsFolder;

        public ObservableCollection<TestResultViewModel> Results { get; } = new ObservableCollection<TestResultViewModel>();
        public RunningTestsViewModel(IEnumerable<FileViewModel> cards, IEnumerable<FileViewModel> hostConfigs, bool addToTimeline, StorageFolder expectedFolder)
        {
            _expectedFolder = expectedFolder;
            _originalCards = cards.ToArray();

            RemainingCards = new ObservableCollection<FileViewModel>(_originalCards);
            RemainingHostConfigs = new ObservableCollection<FileViewModel>(hostConfigs);
            _addToTimeline = addToTimeline;

            if (_originalCards.Length == 0 || (RemainingHostConfigs.Count == 0 && !_addToTimeline))
            {
                throw new InvalidOperationException("There must be some cards and host configs");
            }

            Start();
        }

        private async void Start()
        {
            if (_tempResultsFolder == null)
            {
                _tempResultsFolder = await ApplicationData.Current.TemporaryFolder.CreateFolderAsync("Results", CreationCollisionOption.OpenIfExists);
                _sourceHostConfigsFolder = await _expectedFolder.CreateFolderAsync("SourceHostConfigs", CreationCollisionOption.OpenIfExists);
                _sourceCardsFolder = await _expectedFolder.CreateFolderAsync("SourceCards", CreationCollisionOption.OpenIfExists);
            }

            CurrentCardVisual = null;

            // If no cards left
            if (RemainingCards.Count == 0)
            {
                if (RemainingHostConfigs.Count != 0)
                {
                    RemainingHostConfigs.RemoveAt(0);
                }

                _addToTimeline = false;

                // If also no host configs left, done
                if (RemainingHostConfigs.Count == 0)
                {
                    GoToDoneState();
                    return;
                }

                // Otherwise reset the cards and pop off the current host config
                foreach (var c in _originalCards)
                {
                    RemainingCards.Add(c);
                }
            }

            // Delay a bit to allow UI thread to update, otherwise user would never see an update
            await Task.Delay(10);

            var card = RemainingCards.First();
            CurrentCard = card.Name;

            if (RemainingHostConfigs.Count != 0)
            {
                CurrentHostConfig = RemainingHostConfigs.First().Name;
                var testResult = await TestCard(card, RemainingHostConfigs.First());
                Results.Add(testResult);
            }

            if (_addToTimeline)
            {
                await AddCardToTimeline(card);
            }

            RemainingCards.RemoveAt(0);

            // And start the process again
            Start();
        }

        public async Task AddCardToTimeline(FileViewModel card)
        {
            UserActivityChannel channel = UserActivityChannel.GetDefault();
            UserActivity userActivity = await channel.GetOrCreateUserActivityAsync(Guid.NewGuid().ToString());
            userActivity.VisualElements.DisplayText = "Card error: " + card.Name;
            userActivity.VisualElements.AttributionDisplayText = card.Name;
            userActivity.ActivationUri = new Uri("https://github.com/Microsoft/AdaptiveCards/blob/main/samples/" + card.Name + ".json");

            userActivity.VisualElements.Content = AdaptiveCardBuilder.CreateAdaptiveCardFromJson(card.Contents);

            await userActivity.SaveAsync();

            _currentSession?.Dispose();
            _currentSession = userActivity.CreateSession();
        }

        private async Task<TestResultViewModel> TestCard(FileViewModel cardFile, FileViewModel hostConfigFile)
        {
            uint reruns = 0;
            TestResultViewModel result = null;
            bool retryImage = true;

            while (retryImage)
            {
                var renderResult = await RenderCard(cardFile, hostConfigFile);

                result = await TestResultViewModel.CreateAsync(
                    cardFile: cardFile,
                    hostConfigFile: hostConfigFile,
                    renderedTestResult: renderResult.Item1,
                    actualImageFile: renderResult.Item2,
                    actualJsonFile: renderResult.Item3,
                    expectedFolder: _expectedFolder,
                    sourceHostConfigsFolder: _sourceHostConfigsFolder,
                    sourceCardsFolder: _sourceCardsFolder);

                if (!result.Status.IsPassingStatus())
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

            OnSingleTestCompleted?.Invoke(this, result.Status);
            return result;
        }

        private async Task<Tuple<RenderedTestResult, StorageFile, StorageFile>> RenderCard(FileViewModel cardFile, FileViewModel hostConfigFile)
        {
            var renderResult = await UWPTestLibrary.RenderTestHelpers.RenderCard(cardFile, hostConfigFile);

            UWPTestLibrary.ImageWaiter imageWaiter = new ImageWaiter(renderResult.Tree);

            CurrentCardVisual = renderResult.Tree;
            CurrentCardVisualWidth = renderResult.CardWidth;

            await imageWaiter.WaitOnAllImagesAsync();

            StorageFile imageResultFile = null;
            StorageFile jsonResultFile = null;
            if (renderResult.Error == null)
            {
                imageResultFile = await _tempResultsFolder.CreateFileAsync("Result.png", CreationCollisionOption.GenerateUniqueName);
                jsonResultFile = await _tempResultsFolder.CreateFileAsync("Result.json", CreationCollisionOption.GenerateUniqueName);

                await UWPTestLibrary.RenderTestHelpers.ResultsToFile(imageResultFile, jsonResultFile, renderResult.RoundTrippedJSON, CurrentCardVisual);
            }

            return new Tuple<RenderedTestResult, StorageFile, StorageFile>(renderResult, imageResultFile, jsonResultFile);
        }

        private void GoToDoneState()
        {
            OnTestsCompleted?.Invoke(this, new EventArgs());
        }
    }
}
