using System.Linq;
using System.Text;
using System.Collections.Generic;
using System.Windows;
using AdaptiveCards.Rendering;
#if WPF
using System.Windows.Controls;
#elif XAMARIN
using Xamarin.Forms;
#endif

namespace AdaptiveCards.Rendering
{
    public partial class XamlRenderer
    {
        /// <summary>
        /// Input.ChoiceSet
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        protected static FrameworkElement RenderInputChoiceSet(TypedElement element, RenderContext context)
        {
            InputChoiceSet choiceSet = (InputChoiceSet)element;
#if WPF
            if (context.Options.AdaptiveCard.SupportsInteractivity)
            {
                var uiGrid = new Grid();
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
                uiGrid.RowDefinitions.Add(new RowDefinition() { Height = new GridLength(1, GridUnitType.Star) });

                var uiComboBox = new ComboBox();
                uiComboBox.Style = context.GetStyle("Adaptive.Input.ChoiceSet.ComboBox");
                uiComboBox.DataContext = choiceSet;

                var uiChoices = new ListBox();
                ScrollViewer.SetHorizontalScrollBarVisibility(uiChoices, ScrollBarVisibility.Disabled);
                var itemsPanelTemplate = new ItemsPanelTemplate();
                var factory = new FrameworkElementFactory(typeof(WrapPanel));
                itemsPanelTemplate.VisualTree = factory;
                uiChoices.ItemsPanel = itemsPanelTemplate;
                uiChoices.DataContext = choiceSet;
                uiChoices.Style = context.GetStyle("Adaptive.Input.ChoiceSet");

                foreach (var choice in choiceSet.Choices)
                {
                    if (choiceSet.IsMultiSelect == true)
                    {
                        var uiCheckbox = new CheckBox();
                        uiCheckbox.Content = choice.Title;
                        uiCheckbox.IsChecked = choice.IsSelected;
                        uiCheckbox.DataContext = choice;
                        uiCheckbox.Style = context.GetStyle("Adaptive.Input.ChoiceSet.CheckBox");
                        uiChoices.Items.Add(uiCheckbox);
                    }
                    else
                    {
                        if (choiceSet.Style == ChoiceInputStyle.Compact)
                        {
                            var uiComboItem = new ComboBoxItem();
                            uiComboItem.Style = context.GetStyle("Adaptive.Input.ChoiceSet.ComboBoxItem");
                            uiComboItem.Content = choice.Title;
                            uiComboItem.DataContext = choice;
                            uiComboBox.Items.Add(uiComboItem);
                            if (choice.IsSelected)
                                uiComboBox.SelectedItem = uiComboItem;
                        }
                        else
                        {
                            var uiRadio = new RadioButton();
                            uiRadio.Content = choice.Title;
                            uiRadio.IsChecked = choice.IsSelected;
                            uiRadio.GroupName = choiceSet.Id;
                            uiRadio.DataContext = choice;
                            uiRadio.Style = context.GetStyle("Adaptive.Input.ChoiceSet.Radio");
                            uiChoices.Items.Add(uiRadio);
                        }
                    }
                }
                if (choiceSet.Style == ChoiceInputStyle.Compact)
                {
                    context.InputControls.Add(uiComboBox);
                    Grid.SetRow(uiComboBox, 1);
                    uiGrid.Children.Add(uiComboBox);
                    return uiGrid;
                }
                else
                {
                    context.InputControls.Add(uiChoices);
                    Grid.SetRow(uiChoices, 1);
                    uiGrid.Children.Add(uiChoices);
                    return uiGrid;
                }
            }
            
#endif

            string choiceText = GetFallbackText(choiceSet);
            if (choiceText == null)
            {
                List<string> choices = choiceSet.Choices.Select(choice => choice.Title).ToList();
                if (choiceSet.Style == ChoiceInputStyle.Compact)
                {
                    if (choiceSet.IsMultiSelect)
                    {
                        choiceText = $"Choices: {RendererUtilities.JoinString(choices, ", ", " and ")}";
                    }
                    else
                    {
                        choiceText = $"Choices: {RendererUtilities.JoinString(choices, ", ", " or ")}";
                    }
                }
                else // if (this.Style == ChoiceInputStyle.Expanded)
                {
                    choiceText = $"* {RendererUtilities.JoinString(choices, "\n* ", "\n* ")}";
                }
            }
            Container container = new Container() { Separation = choiceSet.Separation };
            container.Items.Add(new TextBlock()
            {
                Text = choiceText,
                Wrap = true
            });
            container.Items.Add(new TextBlock()
            {
                Text = RendererUtilities.JoinString(choiceSet.Choices.Where(c => c.IsSelected).Select(c => c.Title).ToList(), ", ", " and "),
                Color = TextColor.Accent,
                Wrap = true
            });
            return context.Render(container);
        }
    }
}