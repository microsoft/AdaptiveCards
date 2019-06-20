// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using DiffPlex;
using DiffPlex.DiffBuilder;
using DiffPlex.DiffBuilder.Model;
using Newtonsoft.Json;
using System.Linq;
using Windows.UI;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Media;

// The User Control item template is documented at https://go.microsoft.com/fwlink/?LinkId=234236

namespace AdaptiveCardTestApp.Views
{
    public sealed partial class DiffView : UserControl
    {
        public DiffView()
        {
            this.InitializeComponent();
        }

        private string FormatJson(string json)
        {
            var parsedJson = JsonConvert.DeserializeObject(json);
            return JsonConvert.SerializeObject(parsedJson, Formatting.Indented);
        }

        public void ShowDiff(string previous, string newContent)
        {
            previous = FormatJson(previous);
            newContent = FormatJson(newContent);
            SideBySideDiffModel model = new SideBySideDiffBuilder(new Differ()).BuildDiffModel(previous, newContent);

            DisplayInto(StackPanelOldLines, model.OldText);
            DisplayInto(StackPanelNewLines, model.NewText);

            NoDifferenceView.Visibility = model.NewText.Lines.All(i => i.Type == ChangeType.Unchanged) ? Visibility.Visible : Visibility.Collapsed;
            if (NoDifferenceView.Visibility == Visibility.Visible)
            {
                TextBlockNoDifference.Text = previous == newContent ? "No difference" : "Only whitespace changed";
            }
        }

        private void DisplayInto(StackPanel sp, DiffPaneModel model)
        {
            sp.Children.Clear();

            foreach (var line in model.Lines)
            {
                sp.Children.Add(new Border()
                {
                    Background = GetBackgroundBrush(line.Type),
                    Child = new TextBlock()
                    {
                        Text = line.Text ?? ""
                    }
                });
            }
        }

        private static Brush GetBackgroundBrush(ChangeType changeType)
        {
            switch (changeType)
            {
                case ChangeType.Deleted:
                    return new SolidColorBrush(Colors.LightPink);

                case ChangeType.Imaginary:
                    return new SolidColorBrush(Colors.LightGray);

                case ChangeType.Inserted:
                    return new SolidColorBrush(Colors.LightGreen);

                case ChangeType.Modified:
                    return new SolidColorBrush(Colors.Yellow);

                case ChangeType.Unchanged:
                default:
                    return null;
            }
        }

        private void ScrollViewerOld_ViewChanged(object sender, ScrollViewerViewChangedEventArgs e)
        {
            ScrollViewerNew.ChangeView(ScrollViewerOld.HorizontalOffset, null, null, true);
        }

        private void ScrollViewerNew_ViewChanged(object sender, ScrollViewerViewChangedEventArgs e)
        {
            ScrollViewerOld.ChangeView(ScrollViewerNew.HorizontalOffset, null, null, true);
        }
    }
}
