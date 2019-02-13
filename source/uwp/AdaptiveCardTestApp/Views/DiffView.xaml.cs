using DiffPlex;
using DiffPlex.DiffBuilder;
using DiffPlex.DiffBuilder.Model;
using System.Linq;
using System.Text;
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

        // a simplistic JSON formatter for use in displaying for diffview
        private string FormatJson(string json)
        {
            StringBuilder sbOut = new StringBuilder(json.Length);
            uint indent = 0; // current indent level

            // tracks which character represents the string literal we're visiting.
            // ', ", or 0 if we're not in a literal
            char inStringLiteral = (char)0;

            bool ignoreNextChar = false; // ignore next character (\ escaping)
            foreach (char c in json)
            {
                bool newlineBefore = false;
                bool newlineAfter = false;
                if (ignoreNextChar)
                {
                    ignoreNextChar = false;
                }
                else
                {
                    switch (c)
                    {
                        case '"':
                        case '\'':
                            {
                                if (inStringLiteral == (char)0)
                                {
                                    inStringLiteral = c;
                                }
                                else if (inStringLiteral == c)
                                {
                                    inStringLiteral = (char)0;
                                }
                                break;
                            }

                        case '\\':
                            {
                                ignoreNextChar = (inStringLiteral != (char)0);
                                break;
                            }

                        case '{':
                        case '[':
                            {
                                if (inStringLiteral == (char)0)
                                {
                                    indent++;
                                    newlineAfter = true;
                                }
                                break;
                            }
                        case '}':
                        case ']':
                            {
                                if (inStringLiteral == (char)0)
                                {
                                    indent--;
                                    newlineBefore = true;
                                }
                                break;
                            }
                        case ',':
                            {
                                if (inStringLiteral == (char)0)
                                {
                                    newlineAfter = true;
                                }
                                break;
                            }
                    }
                }

                if (newlineBefore)
                {
                    sbOut.Append('\n');
                    for (uint i = 0; i < indent; i++)
                    {
                        sbOut.Append(' ');
                    }
                }

                sbOut.Append(c);

                if (newlineAfter)
                {
                    sbOut.Append('\n');
                    for (uint i = 0; i < indent; i++)
                    {
                        sbOut.Append(' ');
                    }
                }
            }
            return sbOut.ToString();
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
