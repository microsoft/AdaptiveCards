// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCardTestApp.ViewModels;
using System;
using System.Collections.Generic;
using UWPTestLibrary;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Media.Animation;
using Windows.UI.Xaml.Navigation;
using Windows.UI.Xaml.Shapes;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=234238

namespace AdaptiveCardTestApp.Pages
{
    /// <summary>
    /// An empty page that can be used on its own or navigated to within a Frame.
    /// </summary>
    public sealed partial class RunningTestsPage : Page
    {
        public RunningTestsPage()
        {
            this.InitializeComponent();
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            StartViewModel startModel = e.Parameter as StartViewModel;
            if (startModel == null)
            {
                throw new NullReferenceException("Must provide start model");
            }

            var model = new RunningTestsViewModel(startModel.SelectedCards, startModel.SelectedHostConfigs, startModel.AddToTimeline, startModel.ExpectedFolder);
            model.OnTestsCompleted += Model_OnTestsCompleted;
            model.OnSingleTestCompleted += Model_OnSingleTestCompleted;
            DataContext = model;

            base.OnNavigatedTo(e);
        }

        private void Model_OnSingleTestCompleted(object sender, TestStatus status)
        {
            ShowSingleTestCompletion(status);
        }

        private void ShowSingleTestCompletion(TestStatus status)
        {
            Grid visual = new Grid()
            {
                Width = 80,
                Height = 80,
                HorizontalAlignment = HorizontalAlignment.Left,
                VerticalAlignment = VerticalAlignment.Bottom,
                Margin = new Thickness(24)
            };

            Color indicatorColor;
            Symbol symbol;

            if (status.IsPassingStatus())
            {
                indicatorColor = Colors.Green;
                symbol = Symbol.Accept;
            }
            else if (status.NewCard)
            {
                indicatorColor = Color.FromArgb(255, 65, 159, 254); // A nice blue color
                symbol = Symbol.Add;
            }
            else
            {
                indicatorColor = Colors.Red;
                symbol = Symbol.Cancel;
            }

            visual.Children.Add(new Ellipse()
            {
                Fill = new SolidColorBrush(indicatorColor)
            });

            visual.Children.Add(new SymbolIcon(symbol)
            {
                Foreground = new SolidColorBrush(Colors.White),
                HorizontalAlignment = HorizontalAlignment.Center,
                VerticalAlignment = VerticalAlignment.Center
            });

            RootGrid.Children.Add(visual);

            visual.RenderTransform = new TranslateTransform();

            const int duration = 1;

            DoubleAnimation move = new DoubleAnimation()
            {
                From = 0,
                To = -200,
                Duration = TimeSpan.FromSeconds(duration)
            };

            DoubleAnimation opacity = new DoubleAnimation()
            {
                From = 1,
                To = 0,
                Duration = TimeSpan.FromSeconds(duration)
            };

            Storyboard s = new Storyboard();
            s.Children.Add(move);
            s.Children.Add(opacity);

            Storyboard.SetTarget(move, visual.RenderTransform);
            Storyboard.SetTargetProperty(move, "Y");

            Storyboard.SetTarget(opacity, visual);
            Storyboard.SetTargetProperty(opacity, "Opacity");

            s.Completed += delegate
            {
                RootGrid.Children.Remove(visual);
            };

            s.Begin();
        }

        private void Model_OnTestsCompleted(object sender, EventArgs e)
        {
            Frame.Navigate(typeof(TestResultsPage), DataContext);
        }
    }
}
