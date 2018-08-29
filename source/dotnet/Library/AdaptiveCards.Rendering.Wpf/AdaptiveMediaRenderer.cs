using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class AdaptiveMediaRenderer
    {
        private enum MediaState
        {
            NotStarted = 0,
            IsPlaying,
            IsPaused,
        }

        public static FrameworkElement Render(AdaptiveMedia media, AdaptiveRenderContext context)
        {
            // If host doesn't support interactivity or no media source is provided
            // just return the poster image if present
            if (!context.Config.SupportsInteractivity || media.Sources.Count == 0)
            {
                var uiImage = new Image();
                uiImage.SetSource(ResolveUri(media.Poster), context);

                return uiImage;
            }

            Uri mediaSource = GetMediaSource(media);
            if (mediaSource == null)
            {
                return null;
            }

            var uiMedia = new Grid();

            // Thumbnail
            Button uiThumbnailButton = RenderThumbnailButton(media, context);
            uiThumbnailButton.Visibility = Visibility.Visible;
            uiMedia.Children.Add(uiThumbnailButton);

            // Media player
            StackPanel uiMediaPlayer = RenderMediaPlayer(mediaSource);
            uiMediaPlayer.Visibility = Visibility.Collapsed;
            uiMedia.Children.Add(uiMediaPlayer);

            // Add on click handler to play the media
            // TODO: consider adding a loading gif when video is being loaded
            uiThumbnailButton.Click += (sender, e) =>
            {
                uiThumbnailButton.Visibility = Visibility.Collapsed;
                uiMediaPlayer.Visibility = Visibility.Visible;
            };

            return uiMedia;
        }

        /** Display a thumbnail containing the poster image and a play button */
        private static Button RenderThumbnailButton(AdaptiveMedia media, AdaptiveRenderContext context)
        {
            var mediaConfig = context.Config.Media;

            var uiThumbnailGrid = new Grid();

            /* Poster (if present) */

            if (!string.IsNullOrEmpty(media.Poster))
            {
                // Use the provided poster
                var uiPosterImage = new Image();
                uiPosterImage.SetSource(ResolveUri(media.Poster), context);

                uiThumbnailGrid.Children.Add(uiPosterImage);
            }
            else if (!string.IsNullOrEmpty(mediaConfig.DefaultPoster))
            {
                // Use the default poster from host
                var uiPosterImage = new Image();
                uiPosterImage.SetSource(ResolveUri(mediaConfig.DefaultPoster), context);

                uiThumbnailGrid.Children.Add(uiPosterImage);
            }

            /* Play button */
            
            // TODO: Move default play button offline
            var playButtonSize = 100;
            var uiPlayButton = new Image()
            {
                Height = playButtonSize,
            };
            if (!string.IsNullOrEmpty(mediaConfig.PlayButton))
            {
                uiPlayButton.SetSource(ResolveUri(mediaConfig.PlayButton), context);
            }
            else
            {
                uiPlayButton.Source = CreateBitmapImage(ResolveUri("http://icons.iconarchive.com/icons/iconsmind/outline/256/Play-Music-icon.png"), playButtonSize);
            }

            uiThumbnailGrid.Children.Add(uiPlayButton);

            // Wrap everything in a Button then return
            return new Button
            {
                Content = uiThumbnailGrid
            };
        }

        private static StackPanel RenderMediaPlayer(Uri mediaSource)
        {
            var masterPanel = new StackPanel()
            {
                Background = new SolidColorBrush(Colors.Gray),
            };

            // Media element
            var mediaElement = new MediaElement()
            {
                Stretch = Stretch.Fill,
            };
            masterPanel.Children.Add(mediaElement);

            // Button margin * 2 + button height = panel height (50)
            int panelHeight = 50;
            int childMargin = 5;
            Thickness marginThickness = new Thickness(childMargin, childMargin, childMargin, childMargin);
            int childHeight = 40;

            #region Timeline Panel

            // Using Grid to stretch the timeline slider
            var uiTimelinePanel = new Grid()
            {
                HorizontalAlignment = HorizontalAlignment.Stretch,
                Height = panelHeight,
                Margin = marginThickness,
            };

            TextBlock uiCurrentTime = new TextBlock()
            {
                Text = "00:00:00",
                Foreground = new SolidColorBrush(Colors.White), // TODO: Use host config
                VerticalAlignment = VerticalAlignment.Center,
                Margin = marginThickness,
            };
            uiTimelinePanel.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Auto),
            });
            Grid.SetColumn(uiCurrentTime, 0);
            uiTimelinePanel.Children.Add(uiCurrentTime);

            Slider uiTimelineSlider = new Slider()
            {
                Margin = marginThickness,
                IsEnabled = false,
                HorizontalAlignment = HorizontalAlignment.Stretch,
                VerticalAlignment = VerticalAlignment.Center,
            };
            uiTimelinePanel.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Star),
            });
            Grid.SetColumn(uiTimelineSlider, 1);
            uiTimelinePanel.Children.Add(uiTimelineSlider);

            TextBlock uiMaxTime = new TextBlock()
            {
                Text = "00:00:00",
                Foreground = new SolidColorBrush(Colors.White), // TODO: Use host config
                VerticalAlignment = VerticalAlignment.Center,
                Margin = marginThickness,
            };
            uiTimelinePanel.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Auto),
            });
            Grid.SetColumn(uiMaxTime, 2);
            uiTimelinePanel.Children.Add(uiMaxTime);

            #endregion

            masterPanel.Children.Add(uiTimelinePanel);

            #region Control Panel
            // TODO: replace button URIs with local ones

            var uiControlPanel = new Grid()
            {
                Height = panelHeight,
                Margin = marginThickness,
            };

            #region Create Playback Control Container

            var uiPlaybackControlContainer = new StackPanel()
            {
                VerticalAlignment = VerticalAlignment.Center,
                HorizontalAlignment = HorizontalAlignment.Center,
                Orientation = Orientation.Horizontal,
                Height = panelHeight,
            };

            // Play button
            var uiPlayButton = new Image()
            {
                Name = "playButton",
                Margin = marginThickness,
                Source = CreateBitmapImage(ResolveUri("https://docs.microsoft.com/en-us/windows/uwp/design/style/images/segoe-mdl/e768.png"), childHeight),
            };
            uiPlaybackControlContainer.Children.Add(uiPlayButton);

            // Play trigger
            var playTrigger = new EventTrigger(UIElement.MouseUpEvent)
            {
                SourceName = "playButton",
            };

            var mediaTimeline = new MediaTimeline()
            {
                Source = mediaSource,
            };
            Storyboard.SetTarget(mediaTimeline, mediaElement);

            var storyboard = new Storyboard()
            {
                SlipBehavior = SlipBehavior.Slip,
            };
            storyboard.Children.Add(mediaTimeline);
            var beginStoryboard = new BeginStoryboard()
            {
                Name = "beginStoryboard",
                Storyboard = storyboard,
            };
            playTrigger.Actions.Add(beginStoryboard);

            // Pause button
            var uiPauseButton = new Image()
            {
                Margin = marginThickness,
                Source = CreateBitmapImage(ResolveUri("https://docs.microsoft.com/en-us/windows/uwp/design/style/images/segoe-mdl/e769.png"), childHeight),
                Visibility = Visibility.Collapsed,
            };
            uiPlaybackControlContainer.Children.Add(uiPauseButton);

            // Resume button
            var uiResumeButton = new Image()
            {
                Margin = marginThickness,
                Source = CreateBitmapImage(ResolveUri("https://docs.microsoft.com/en-us/windows/uwp/design/style/images/segoe-mdl/e768.png"), childHeight),
                Visibility = Visibility.Collapsed,
            };
            uiPlaybackControlContainer.Children.Add(uiResumeButton);

            // Stop button
            var uiStopButton = new Image()
            {
                Margin = marginThickness,
                Source = CreateBitmapImage(ResolveUri("https://docs.microsoft.com/en-us/windows/uwp/design/style/images/segoe-mdl/e71a.png"), childHeight),
            };
            uiPlaybackControlContainer.Children.Add(uiStopButton);

            // Click events
            uiPauseButton.MouseUp += (sender, e) =>
            {
                storyboard.Pause(masterPanel);
                HandleButtonAppearance(MediaState.IsPaused, uiPlayButton, uiPauseButton, uiResumeButton, uiStopButton);
            };
            uiResumeButton.MouseUp += (sender, e) =>
            {
                storyboard.Resume(masterPanel);
                HandleButtonAppearance(MediaState.IsPlaying, uiPlayButton, uiPauseButton, uiResumeButton, uiStopButton);
            };
            uiStopButton.MouseUp += (sender, e) =>
            {
                storyboard.Stop(masterPanel);
                HandleButtonAppearance(MediaState.NotStarted, uiPlayButton, uiPauseButton, uiResumeButton, uiStopButton);
            };

            // The media is considered playing only after it's opened
            mediaElement.MediaOpened += (sender, e) =>
            {
                HandleButtonAppearance(MediaState.IsPlaying, uiPlayButton, uiPauseButton, uiResumeButton, uiStopButton);
            };

            #endregion

            // Add to control bar
            uiControlPanel.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Star),
            });
            Grid.SetColumn(uiPlaybackControlContainer, 0);
            uiControlPanel.Children.Add(uiPlaybackControlContainer);

            #region Create Volume Control Container

            // TODO: Restyle volume popup and slider
            var uiVolumeControlContainer = new Grid()
            {
                Height = panelHeight,
                VerticalAlignment = VerticalAlignment.Center,
            };

            Image uiVolumeButton = new Image()
            {
                Margin = marginThickness,
                Source = CreateBitmapImage(ResolveUri("https://docs.microsoft.com/en-us/windows/uwp/design/style/images/segoe-mdl/E767.png"), childHeight),
            };
            uiVolumeControlContainer.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Auto),
            });
            Grid.SetColumn(uiVolumeButton, 0);
            uiVolumeControlContainer.Children.Add(uiVolumeButton);

            // Button to alternate between mute/unmute state
            Image uiVolumeMuteButton = new Image()
            {
                Margin = marginThickness,
                Source = CreateBitmapImage(ResolveUri("https://docs.microsoft.com/en-us/windows/uwp/design/style/images/segoe-mdl/E74F.png"), childHeight),
                Visibility = Visibility.Collapsed,
            };
            uiVolumeControlContainer.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Auto),
            });
            Grid.SetColumn(uiVolumeMuteButton, 0);
            uiVolumeControlContainer.Children.Add(uiVolumeMuteButton);

            Slider uiVolumeSlider = new Slider()
            {
                Orientation = Orientation.Horizontal,
                VerticalAlignment = VerticalAlignment.Center,
                Width = 100,

                Minimum = 0,
                Maximum = 1,
                Value = 0.5,
            };
            mediaElement.Volume = uiVolumeSlider.Value; // Initialize
            uiVolumeSlider.ValueChanged += (sender, e) =>
            {
                mediaElement.Volume = uiVolumeSlider.Value;
            };
            uiVolumeControlContainer.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Auto),
            });
            Grid.SetColumn(uiVolumeSlider, 1);
            uiVolumeControlContainer.Children.Add(uiVolumeSlider);

            // Handle volume button click
            uiVolumeButton.MouseUp += (sender, e) =>
            {
                uiVolumeButton.Visibility = Visibility.Collapsed;
                uiVolumeMuteButton.Visibility = Visibility.Visible;
                mediaElement.Volume = 0;
            };
            uiVolumeMuteButton.MouseUp += (sender, e) =>
            {
                uiVolumeMuteButton.Visibility = Visibility.Collapsed;
                uiVolumeButton.Visibility = Visibility.Visible;
                mediaElement.Volume = uiVolumeSlider.Value;
            };
            uiVolumeSlider.ValueChanged += (sender, e) =>
            {
                // When volume slider moves, unmute
                uiVolumeMuteButton.Visibility = Visibility.Collapsed;
                uiVolumeButton.Visibility = Visibility.Visible;
                mediaElement.Volume = uiVolumeSlider.Value;
            };

            #endregion

            // Add to control bar
            uiControlPanel.ColumnDefinitions.Add(new ColumnDefinition()
            {
                Width = new GridLength(20, GridUnitType.Auto),
            });
            Grid.SetColumn(uiVolumeControlContainer, 1);
            uiControlPanel.Children.Add(uiVolumeControlContainer);

            #endregion

            masterPanel.Children.Add(uiControlPanel);

            masterPanel.Triggers.Add(playTrigger);

            #region Timeline events
            
            // Timeline slider events
            mediaElement.MediaOpened += (sender, e) =>
            {
                uiTimelineSlider.Maximum = mediaElement.NaturalDuration.TimeSpan.TotalMilliseconds;
                uiTimelineSlider.IsEnabled = true;

                uiMaxTime.Text = mediaElement.NaturalDuration.TimeSpan.ToString(@"hh\:mm\:ss");
            };
            storyboard.CurrentTimeInvalidated += (sender, e) => {
                uiTimelineSlider.Value = mediaElement.Position.TotalMilliseconds;

                uiCurrentTime.Text = mediaElement.Position.ToString(@"hh\:mm\:ss");
            };

            // Thumb events
            uiTimelineSlider.AddHandler(Thumb.DragStartedEvent, new DragStartedEventHandler((sender, e) =>
            {
                storyboard.Pause(masterPanel);
            }));
            uiTimelineSlider.AddHandler(Thumb.DragDeltaEvent, new DragDeltaEventHandler((sender, e) =>
            {
                int sliderValue = (int)uiTimelineSlider.Value;

                TimeSpan selectedTimeSpan = new TimeSpan(0, 0, 0, 0, sliderValue);

                uiCurrentTime.Text = selectedTimeSpan.ToString(@"hh\:mm\:ss");
            }));
            uiTimelineSlider.AddHandler(Thumb.DragCompletedEvent, new DragCompletedEventHandler((sender, e) =>
            {
                int sliderValue = (int)uiTimelineSlider.Value;
                storyboard.Seek(masterPanel, new TimeSpan(0, 0, 0, 0, sliderValue), TimeSeekOrigin.BeginTime);
                storyboard.Resume(masterPanel);
            }));

            #endregion

            return masterPanel;
        }

        private static void HandleButtonAppearance(MediaState currentMediaState,
            FrameworkElement playButton, FrameworkElement pauseButton, FrameworkElement resumeButton, FrameworkElement stopButton)
        {
            playButton.Visibility = Visibility.Collapsed;
            pauseButton.Visibility = Visibility.Collapsed;
            resumeButton.Visibility = Visibility.Collapsed;
            stopButton.Visibility = Visibility.Visible; // Stop button is always enabled

            if (currentMediaState == MediaState.NotStarted)
            {
                playButton.Visibility = Visibility.Visible;
            }
            else if (currentMediaState == MediaState.IsPlaying)
            {
                pauseButton.Visibility = Visibility.Visible;
            }
            else // IsPaused
            {
                resumeButton.Visibility = Visibility.Visible;
            }
        }

        /** Get the bitmap source of a given height (aspect ratio is kept) to optimize memory use */
        private static BitmapImage CreateBitmapImage(Uri uri, int height)
        {
            BitmapImage bitmapImage = new BitmapImage();
            bitmapImage.BeginInit();
            bitmapImage.UriSource = uri;
            bitmapImage.DecodePixelHeight = height;
            bitmapImage.EndInit();

            return bitmapImage;
        }
        
        /** Try to resolve a URI from a string */
        // TODO: add support for relative URI
        private static Uri ResolveUri(string uri)
        {
            if (string.IsNullOrEmpty(uri))
            {
                return null;
            }

            Uri posterUri;
            try
            {
                posterUri = new Uri(uri, UriKind.RelativeOrAbsolute);
            }
            catch
            {
                return null;
            }

            return posterUri;
        }

        /** Get media URI of a given media object */
        private static Uri GetMediaSource(AdaptiveMedia media)
        {
            List<string> supportedMimeTypes = new List<string>
            {
                "video/mp4",
                "audio/mp4",
                "audio/mpeg"
            };

            // Return the first supported source with not-null URI
            foreach (var source in media.Sources)
            {
                if (supportedMimeTypes.Contains(source.MimeType))
                {
                    Uri uri = ResolveUri(source.Url);
                    if (uri != null)
                    {
                        return uri;
                    }
                }
            }

            // No good source is found
            return null;
        }
    }
}
