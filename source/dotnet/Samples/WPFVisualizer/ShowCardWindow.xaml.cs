// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Diagnostics;
using System.Windows;
using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;

namespace WpfVisualizer
{
    /// <summary>
    /// Interaction logic for ShowCardWindow.xaml
    /// </summary>
    public partial class ShowCardWindow : Window
    {
        private readonly AdaptiveShowCardAction _card;
        private readonly ResourceDictionary _resources;

        public ShowCardWindow(string title, AdaptiveShowCardAction action, ResourceDictionary resources)
        {
            InitializeComponent();

            _resources = resources;
            _card = action;
            Title = title;
        }

        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var renderer = new AdaptiveCardRenderer(new AdaptiveHostConfig())
            {
                Resources = _resources
            };
            var result = renderer.RenderCard(_card.Card);

            if (result.FrameworkElement != null)
            {
                // Wire up click handler
                result.OnAction += OnAction;

                Body.Children.Add(result.FrameworkElement);
            }
        }

        private void OnAction(object sender, AdaptiveActionEventArgs e)
        {
            if (e.Action is AdaptiveOpenUrlAction openUrlAction)
            {
                Process.Start(openUrlAction.Url.AbsoluteUri);
            }
            else if (e.Action is AdaptiveShowCardAction)
            {
                MessageBox.Show("Action.ShowCard is not alloed from within a sub-card");
            }
            else if (e.Action is AdaptiveSubmitAction submitAction)
            {
                MessageBox.Show(this, submitAction.DataJson, "SubmitAction");
                Close();
            }
        }
    }
}
