// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards;
using AdaptiveCards.Rendering;
using AdaptiveCards.Rendering.Wpf;
using Microsoft.Win32;
using Newtonsoft.Json;
using System;
using System.ComponentModel;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Speech.Synthesis;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Threading;
using Newtonsoft.Json.Linq;
using Xceed.Wpf.Toolkit.PropertyGrid;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using System.Windows.Media;
using ICSharpCode.AvalonEdit.Highlighting.Xshd;
using ICSharpCode.AvalonEdit.Highlighting;
using ICSharpCode.AvalonEdit.Document;
using System.Collections.ObjectModel;
using System.Threading;

using System.Windows.Documents;
using System.Collections.Generic;

namespace WpfVisualizer
{
    public partial class MainWindow : Window
    {
        /*
        // This variable exists so the sample styles are not added twice
        private bool _stylesAdded = false;
        */

        public AdaptiveCardRenderer Renderer { get; set; }

        private AdaptiveHostConfig HostConfig;

        private List<AdaptiveCard> AdaptiveCards = new List<AdaptiveCard>();
        private List<string> AdaptiveCardsNames = new List<string>();

        private StackPanel panel;

        public MainWindow()
        {
            InitializeComponent();

            panel = (StackPanel)this.FindName("layout");

            var timer = new DispatcherTimer { Interval = TimeSpan.FromSeconds(1) };
            timer.Start();
            
            Renderer = new AdaptiveCardRenderer()
            {
                Resources = Resources
            };
            
            // Use the Xceed rich input controls
            Renderer.UseXceedElementRenderers();

            // Register custom elements and actions

            // This seems unecessary?
            Renderer.ActionHandlers.AddSupportedAction<MyCustomAction>();

            ReadAllFiles();
            RenderAllCards();
        }

        private void ReadAllFiles()
        {
            HostConfig = new AdaptiveHostConfig();

            string[] files = Directory.GetFiles("Samples//");

            foreach (var file in files)
            {
                string cardPayload = File.ReadAllText(file);
                AdaptiveCardParseResult parseResult = AdaptiveCard.FromJson(cardPayload);

                AdaptiveCards.Add(parseResult.Card);
                AdaptiveCardsNames.Add(file);
            }           
        }

        private void RenderAllCards()
        {
            for(int i = 0; i < 14; ++i)
            {
                RenderCard(i % AdaptiveCards.Count);
            }
        }

        private void RenderCard(int index)
        {
            try
            {
                Stopwatch stopwatch = new Stopwatch();

                stopwatch.Start();
                RenderedAdaptiveCard renderedCard = Renderer.RenderCard(AdaptiveCards[index]);
                stopwatch.Stop();

                Debug.WriteLine("Card: " + AdaptiveCardsNames[index] + " - Time elapsed: " + stopwatch.ElapsedMilliseconds);

                layout.Children.Add(renderedCard.FrameworkElement);

                // Wire up click handler
                renderedCard.OnAction += OnAction;

                renderedCard.OnMediaClicked += OnMediaClick;
            }
            catch (AdaptiveRenderException)
            {
            }
            catch (Exception)
            {
            }
        }

        private void OnAction(RenderedAdaptiveCard sender, AdaptiveActionEventArgs e)
        {
            if (e.Action is AdaptiveOpenUrlAction openUrlAction)
            {
                Process.Start(openUrlAction.Url.AbsoluteUri);
            }
            else if (e.Action is AdaptiveShowCardAction showCardAction)
            {
                // Action.ShowCard can be rendered inline automatically, or in "popup" mode
                // If the Host Config is set to Popup mode, then the app needs to show it
                if (Renderer.HostConfig.Actions.ShowCard.ActionMode == ShowCardActionMode.Popup)
                {
                    var dialog = new ShowCardWindow(showCardAction.Title, showCardAction, Resources);
                    dialog.Owner = this;
                    dialog.ShowDialog();
                }
            }
            else if (e.Action is AdaptiveSubmitAction submitAction)
            {
                var inputs = sender.UserInputs.AsJson();

                // Merge the Action.Submit Data property with the inputs
                inputs.Merge(submitAction.Data);

                MessageBox.Show(this, JsonConvert.SerializeObject(inputs, Formatting.Indented), "SubmitAction");
            }
        }

        private void OnMediaClick(RenderedAdaptiveCard sender, AdaptiveMediaEventArgs e)
        {
            MessageBox.Show(this, JsonConvert.SerializeObject(e.Media), "Host received a Media");
        }

        private void _OnMissingInput(object sender, MissingInputEventArgs args)
        {
            MessageBox.Show("Required input is missing.");
            args.FrameworkElement.Focus();
        }
        
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            var binding = new CommandBinding(NavigationCommands.GoToPage, GoToPage, CanGoToPage);
            // Register CommandBinding for all windows.
            CommandManager.RegisterClassCommandBinding(typeof(Window), binding);
        }


        private void GoToPage(object sender, ExecutedRoutedEventArgs e)
        {
            if (e.Parameter is string)
            {
                var name = e.Parameter as string;
                if (!string.IsNullOrWhiteSpace(name))
                    Process.Start(name);
            }
        }

        private void CanGoToPage(object sender, CanExecuteRoutedEventArgs e)
        {
            e.CanExecute = true;
        }
        
        private string FixSSML(string speak)
        {
            var sb = new StringBuilder();
            sb.AppendLine("<speak version=\"1.0\"");
            sb.AppendLine(" xmlns =\"http://www.w3.org/2001/10/synthesis\"");
            sb.AppendLine(" xml:lang=\"en-US\">");
            sb.AppendLine(speak);
            sb.AppendLine("</speak>");
            return sb.ToString();
        }
        
        private void loadConfig_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new OpenFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                HostConfig = AdaptiveHostConfig.FromJson(File.ReadAllText(dlg.FileName));
            }
        }

        private void saveConfig_Click(object sender, RoutedEventArgs e)
        {
            var dlg = new SaveFileDialog();
            dlg.DefaultExt = ".json";
            dlg.Filter = "Json documents (*.json)|*.json";
            var result = dlg.ShowDialog();
            if (result == true)
            {
                var json = JsonConvert.SerializeObject(Renderer.HostConfig, Formatting.Indented);
                File.WriteAllText(dlg.FileName, json);
            }
        }
        
        private void XceedCheckBox_Unchecked(object sender, RoutedEventArgs e)
        {
            Renderer.UseDefaultElementRenderers();
        }

        private void XceedCheckBox_Checked(object sender, RoutedEventArgs e)
        {
            Renderer.UseXceedElementRenderers();
        }
    }
}
