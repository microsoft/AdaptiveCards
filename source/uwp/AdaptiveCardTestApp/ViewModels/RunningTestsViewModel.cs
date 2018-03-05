using AdaptiveCards.Rendering.Uwp;
using AdaptiveCardTestApp.Helpers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using Windows.Graphics.Imaging;
using Windows.Storage;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Markup;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Imaging;
using Windows.UI.Xaml.Shapes;

namespace AdaptiveCardTestApp.ViewModels
{
    public class RunningTestsViewModel : BaseViewModel
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

        public RunningTestsViewModel(IEnumerable<FileViewModel> cards, IEnumerable<FileViewModel> hostConfigs, StorageFolder expectedFolder)
        {
            _expectedFolder = expectedFolder;
            _originalCards = cards.ToArray();

            RemainingCards = new ObservableCollection<FileViewModel>(_originalCards);
            RemainingHostConfigs = new ObservableCollection<FileViewModel>(hostConfigs);

            if (_originalCards.Length == 0 || RemainingHostConfigs.Count == 0)
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

            // If no cards left
            if (RemainingCards.Count == 0)
            {
                RemainingHostConfigs.RemoveAt(0);

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

            CurrentCard = RemainingCards.First().Name;
            CurrentHostConfig = RemainingHostConfigs.First().Name;
            CurrentCardVisual = null;

            // Delay a bit to allow UI thread to update, otherwise user would never see an update
            await Task.Delay(10);

            var testResult = await TestCard(RemainingCards.First(), RemainingHostConfigs.First());
            Results.Add(testResult);

            RemainingCards.RemoveAt(0);

            // And start the process again
            Start();
        }

        private async Task<TestResultViewModel> TestCard(FileViewModel cardFile, FileViewModel hostConfigFile)
        {
            var renderResult = await RenderCard(cardFile, hostConfigFile);

            var result = await TestResultViewModel.CreateAsync(
                cardFile: cardFile,
                hostConfigFile: hostConfigFile,
                actualError: renderResult.Item1,
                actualImageFile: renderResult.Item2,
                expectedFolder: _expectedFolder,
                sourceHostConfigsFolder: _sourceHostConfigsFolder,
                sourceCardsFolder: _sourceCardsFolder);

            OnSingleTestCompleted?.Invoke(this, result.Status);
            return result;
        }

        private async Task<Tuple<string, StorageFile>> RenderCard(FileViewModel cardFile, FileViewModel hostConfigFile)
        {
            string error = null;
            RenderTargetBitmap rtb = null;

            try
            {
                AdaptiveHostConfig hostConfig = AdaptiveHostConfig.FromJsonString(hostConfigFile.Contents).HostConfig;

                if (hostConfig == null)
                {
                    error = "Parsing hostConfig failed";
                }

                else
                {
                    AdaptiveCard card = AdaptiveCard.FromJsonString(cardFile.Contents).AdaptiveCard;

                    if (card == null)
                    {
                        error = "Parsing card failed";
                    }

                    else
                    {
                        var renderer = new AdaptiveCardRenderer()
                        {
                            HostConfig = hostConfig
                        };

                        if (hostConfigFile.Name.Contains("windows-timeline"))
                        {
                            renderer.SetFixedDimensions(320, 180);
                            CurrentCardVisualWidth = 320;
                        }
                        else if (hostConfigFile.Name.Contains("windows-live-tile"))
                        {
                            renderer.SetFixedDimensions(310, 310);
                            CurrentCardVisualWidth = 310;
                        }
                        else
                        {
                            CurrentCardVisualWidth = 400;
                        }

                        FrameworkElement xaml = renderer.RenderAdaptiveCard(card).FrameworkElement as FrameworkElement;

                        if (xaml == null)
                        {
                            error = "Rendering card failed";
                        }

                        else
                        {
                            xaml = new Border()
                            {
                                Background = new SolidColorBrush(Colors.White),
                                Child = xaml,
                                IsHitTestVisible = false // Disable HitTest so that mouse pointer can't accidently hover over a button
                            };

                            // The theme is important to set since it'll ensure buttons/inputs appear correctly
                            if (hostConfigFile.Name.Contains("windows-notification"))
                            {
                                xaml.RequestedTheme = ElementTheme.Dark;
                            }
                            else
                            {
                                xaml.RequestedTheme = ElementTheme.Light;
                            }

                            CurrentCardVisual = xaml;

                            NormalizeTimePickers(xaml);
                            await WaitOnAllImagesAsync(xaml);

                            rtb = new RenderTargetBitmap();
                            await rtb.RenderAsync(CurrentCardVisual);
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                error = ex.ToString();
            }

            StorageFile file = null;

            if (error == null)
            {
                file = await _tempResultsFolder.CreateFileAsync("Result.png", CreationCollisionOption.GenerateUniqueName);

                // https://basquang.wordpress.com/2013/09/26/windows-store-8-1-save-visual-element-to-bitmap-image-file/
                var buffer = await rtb.GetPixelsAsync();

                using (var stream = await file.OpenAsync(FileAccessMode.ReadWrite))
                {
                    var encoder = await BitmapEncoder.CreateAsync(BitmapEncoder.PngEncoderId, stream);

                    encoder.SetPixelData(BitmapPixelFormat.Bgra8, BitmapAlphaMode.Straight, (uint)rtb.PixelWidth, (uint)rtb.PixelHeight, 96, 96, buffer.ToArray());

                    await encoder.FlushAsync();
                }
            }

            return new Tuple<string, StorageFile>(error, file);
        }

        /// <summary>
        /// This method ensures that any time pickers that didn't have a specific assigned value end up with the same time
        /// as previous tests, to ensure that the fact that the time is different on a machine doesn't make the test fail
        /// </summary>
        /// <param name="el"></param>
        private static void NormalizeTimePickers(UIElement el)
        {
            foreach (var timePicker in GetAllDescendants(el).OfType<TimePicker>())
            {
                // If didn't have a value from the Card payload
                if ((DateTime.Now.TimeOfDay - timePicker.Time).TotalMinutes <= 1)
                {
                    timePicker.Time = new TimeSpan(9, 0, 0);
                }
            }
        }

        private static async Task WaitOnAllImagesAsync(UIElement el)
        {
            int countRemaining = 0;

            ExceptionRoutedEventHandler failedHandler = new ExceptionRoutedEventHandler(delegate
            {
                countRemaining--;
            });
            RoutedEventHandler openedHandler = new RoutedEventHandler(delegate
            {
                countRemaining--;
            });

            foreach (var shape in GetAllDescendants(el).OfType<Shape>())
            {
                if (shape.Fill is ImageBrush)
                {
                    countRemaining++;
                    (shape.Fill as ImageBrush).ImageFailed += failedHandler;
                    (shape.Fill as ImageBrush).ImageOpened += openedHandler;
                }
            }

            foreach (var img in GetAllDescendants(el).OfType<Image>())
            {
                countRemaining++;
                img.ImageFailed += failedHandler;
                img.ImageOpened += openedHandler;
            }

            while (countRemaining > 0)
            {
                await Task.Delay(10);
            }
        }

        private static IEnumerable<UIElement> GetAllDescendants(UIElement element)
        {
            int count = VisualTreeHelper.GetChildrenCount(element);
            for (int i = 0; i < count; i++)
            {
                var child = VisualTreeHelper.GetChild(element, i) as UIElement;
                if (child != null)
                {
                    yield return child;

                    foreach (var descendant in GetAllDescendants(child))
                    {
                        yield return descendant;
                    }
                }
            }

            // Make sure contents of touch targets get walked, the VisualTreeHelper doesn't grab these
            if (element is ContentControl)
            {
                var content = (element as ContentControl).Content as UIElement;
                if (content != null)
                {
                    yield return content;

                    foreach (var descendant in GetAllDescendants(content))
                    {
                        yield return descendant;
                    }
                }
            }
        }

        private void GoToDoneState()
        {
            OnTestsCompleted?.Invoke(this, new EventArgs());
        }
    }
}
