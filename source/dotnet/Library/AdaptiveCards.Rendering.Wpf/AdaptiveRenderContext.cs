// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace AdaptiveCards.Rendering.Wpf
{
    /// <summary>
    /// Context state for a render pass
    /// </summary>
    public class AdaptiveRenderContext
    {
        private readonly Dictionary<string, SolidColorBrush> _colors = new Dictionary<string, SolidColorBrush>();

        public List<Task> AssetTasks { get; } = new List<Task>();

        public AdaptiveRenderContext(Action<object, AdaptiveActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback,
            Action<object, AdaptiveMediaEventArgs> mediaClickCallback)
        {
            if (actionCallback != null)
                OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                OnMissingInput += (obj, args) => missingDataCallback(obj, args);

            if (mediaClickCallback != null)
                OnMediaClick += (obj, args) => mediaClickCallback(obj, args);
        }

        public AdaptiveHostConfig Config { get; set; } = new AdaptiveHostConfig();

        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();

        public AdaptiveElementRenderers<FrameworkElement, AdaptiveRenderContext> ElementRenderers { get; set; }

        public ResourceDictionary Resources { get; set; }

        public AdaptiveActionHandlers ActionHandlers { get; set; }

        public AdaptiveFeatureRegistration FeatureRegistration { get; set; }

        public ResourceResolver ResourceResolvers { get; set; }

        public bool IsRenderingSelectAction { get; set; }

        public IDictionary<Uri, MemoryStream> CardAssets { get; set; } = new Dictionary<Uri, MemoryStream>();

        public IDictionary<string, Func<string>> InputBindings = new Dictionary<string, Func<string>>();

        public event EventHandler<AdaptiveActionEventArgs> OnAction;

        public event EventHandler<AdaptiveMediaEventArgs> OnMediaClick;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public event EventHandler<MissingInputEventArgs> OnMissingInput;

        public void InvokeAction(FrameworkElement ui, AdaptiveActionEventArgs args)
        {
            // ToggleVisibility is a renderer-handled action
            if (args.Action is AdaptiveToggleVisibilityAction toggleVisibilityAction)
            {
                ToggleVisibility(toggleVisibilityAction.TargetElements);
                return;
            }
            else if (args.Action is AdaptiveShowCardAction
                && Config.Actions.ShowCard.ActionMode == ShowCardActionMode.Inline)
            {
                ToggleShowCardVisibility((Button)ui);
                return;
            }
            else if (args.Action is AdaptiveSubmitAction)
            {
                if (!ValidateInputs(args.Action as AdaptiveSubmitAction))
                {
                    return;
                }
            }

            OnAction?.Invoke(ui, args);
        }

        public void MissingInput(AdaptiveAction sender, MissingInputEventArgs args)
        {
            OnMissingInput?.Invoke(sender, args);
        }

        public void ClickMedia(FrameworkElement ui, AdaptiveMediaEventArgs args)
        {
            OnMediaClick?.Invoke(ui, args);
        }

        /// <summary>
        /// All remote assets should be resolved through this method for tracking
        /// </summary>
        public async Task<BitmapImage> ResolveImageSource(Uri url)
        {
            var completeTask = new TaskCompletionSource<object>();
            AssetTasks.Add(completeTask.Task);

            try
            {
                // Load the stream from the pre-populated CardAssets or try to load from the ResourceResolver
                var streamTask = CardAssets.TryGetValue(url, out var s) ? Task.FromResult(s) : ResourceResolvers.LoadAssetAsync(url);

                Debug.WriteLine($"ASSETS: Starting asset down task for {url}");

                var source = new BitmapImage();

                var stream = await streamTask;
                if (stream != null)
                {
                    stream.Position = 0;
                    source.BeginInit();
                    source.CacheOption = BitmapCacheOption.OnLoad;
                    source.StreamSource = stream;
                    source.EndInit();
                    Debug.WriteLine($"ASSETS: Finished loading asset for {url} ({stream.Length} bytes)");
                }
                completeTask.SetResult(new object());
                return source;
            }
            catch (Exception e)
            {
                Debug.WriteLine($"ASSETS: Failed to load asset for {url}. {e.Message}");
                completeTask.SetException(e);
                return null;
            }
        }

        public SolidColorBrush GetColorBrush(string color)
        {
            lock (_colors)
            {
                if (_colors.TryGetValue(color, out var brush))
                    return brush;
                brush = new SolidColorBrush((Color)ColorConverter.ConvertFromString(color));
                _colors[color] = brush;
                return brush;
            }
        }

        public IDictionary<Button, FrameworkElement> ActionShowCards = new Dictionary<Button, FrameworkElement>();

        // contains showcard peers in actions set, and the AdaptiveInternalID is internal id of the actions set
        public IDictionary<AdaptiveInternalID, List<FrameworkElement>> PeerShowCardsInActionSet = new Dictionary<AdaptiveInternalID, List<FrameworkElement>>();

        public virtual Style GetStyle(string styleName)
        {
            while (!String.IsNullOrEmpty(styleName))
            {
                Style style = this.Resources.TryGetValue<Style>(styleName);
                if (style != null)
                    return style;
                var iPos = styleName.LastIndexOf('.');
                if (iPos <= 0)
                    break;
                styleName = styleName.Substring(0, iPos);
            }

            // Debug.WriteLine($"Unable to find Style {styleName} from the supplied ResourceDictionary");
            return null;
        }

        public AdaptiveTypedElement GetRendereableElement(AdaptiveTypedElement element)
        {
            AdaptiveTypedElement rendereableElement = null;
            var oldAncestorHasFallback = AncestorHasFallback;
            var elementHasFallback = element != null && element.Fallback != null && (element.Fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None);
            AncestorHasFallback = AncestorHasFallback || elementHasFallback;

            try
            {
                if (AncestorHasFallback && !element.MeetsRequirements(FeatureRegistration))
                {
                    throw new AdaptiveFallbackException("Element requirements aren't met");
                }

                var renderer = ElementRenderers.Get(element.GetType());
                if (renderer != null)
                {
                    rendereableElement = element;
                }
            }
            catch (AdaptiveFallbackException)
            {
                if (!elementHasFallback)
                {
                    throw;
                }
            }

            if (rendereableElement == null)
            {
                // Since no renderer exists for this element, add warning and render fallback (if available)
                if (element.Fallback != null && element.Fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None)
                {
                    if (element.Fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Drop)
                    {
                        Warnings.Add(new AdaptiveWarning(-1, $"Dropping element '{element.Type}' for fallback"));
                    }
                    else if (element.Fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Content && element.Fallback.Content != null)
                    {
                        // Render fallback content
                        Warnings.Add(new AdaptiveWarning(-1, $"Performing fallback for '{element.Type}' (fallback element type '{element.Fallback.Content.Type}')"));
                        RenderingFallback = true;

                        rendereableElement = GetRendereableElement(element.Fallback.Content);

                        RenderingFallback = false;
                    }
                }
                else if (AncestorHasFallback && !RenderingFallback)
                {
                    throw new AdaptiveFallbackException();
                }
                else
                {
                    Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element '{element.Type}'"));
                }
            }

            AncestorHasFallback = oldAncestorHasFallback;

            return rendereableElement;
        }

        /// <summary>
        /// Helper to deal with casting
        /// </summary>
        public FrameworkElement Render(AdaptiveTypedElement element)
        {
            FrameworkElement frameworkElementOut = null;
            var oldAncestorHasFallback = AncestorHasFallback;
            var elementHasFallback = element != null && element.Fallback != null && (element.Fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None);
            AncestorHasFallback = AncestorHasFallback || elementHasFallback;

            try
            {
                if (AncestorHasFallback && !element.MeetsRequirements(FeatureRegistration))
                {
                    throw new AdaptiveFallbackException("Element requirements aren't met");
                }

                // Inputs should render read-only if interactivity is false
                if (!Config.SupportsInteractivity && element is AdaptiveInput input)
                {
                    var tb = AdaptiveTypedElementConverter.CreateElement<AdaptiveTextBlock>();
                    tb.Text = input.GetNonInteractiveValue() ?? "*[Input]*";
                    tb.Color = AdaptiveTextColor.Accent;
                    tb.Wrap = true;
                    Warnings.Add(new AdaptiveWarning(-1, $"Rendering non-interactive input element '{element.Type}'"));
                    frameworkElementOut = Render(tb);
                }

                if (frameworkElementOut == null)
                {
                    var renderer = ElementRenderers.Get(element.GetType());
                    if (renderer != null)
                    {
                        var rendered = renderer.Invoke(element, this);

                        if (!String.IsNullOrEmpty(element.Id))
                        {
                            rendered.Name = element.Id;
                        }

                        frameworkElementOut = rendered;
                    }
                }
            }
            catch (AdaptiveFallbackException)
            {
                if (!elementHasFallback)
                {
                    throw;
                }
            }

            if (frameworkElementOut == null)
            {
                // Since no renderer exists for this element, add warning and render fallback (if available)
                if (element.Fallback != null && element.Fallback.Type != AdaptiveFallbackElement.AdaptiveFallbackType.None)
                {
                    if (element.Fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Drop)
                    {
                        Warnings.Add(new AdaptiveWarning(-1, $"Dropping element '{element.Type}' for fallback"));
                    }
                    else if (element.Fallback.Type == AdaptiveFallbackElement.AdaptiveFallbackType.Content && element.Fallback.Content != null)
                    {
                        // Render fallback content
                        Warnings.Add(new AdaptiveWarning(-1, $"Performing fallback for '{element.Type}' (fallback element type '{element.Fallback.Content.Type}')"));
                        RenderingFallback = true;
                        frameworkElementOut = Render(element.Fallback.Content);
                        RenderingFallback = false;
                    }
                }
                else if (AncestorHasFallback && !RenderingFallback)
                {
                    throw new AdaptiveFallbackException();
                }
                else
                {
                    Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element '{element.Type}'"));
                }
            }

            AncestorHasFallback = oldAncestorHasFallback;
            return frameworkElementOut;
        }

        private bool AncestorHasFallback = false;
        private bool RenderingFallback = false;

        public string Lang { get; set; }

        public FrameworkElement CardRoot { get; set; }

        public AdaptiveRenderArgs RenderArgs { get; set; }
        public FontColorConfig GetForegroundColors(AdaptiveTextColor textColor)
        {
            switch (textColor)
            {
                case AdaptiveTextColor.Accent:
                    return RenderArgs.ForegroundColors.Accent;
                case AdaptiveTextColor.Attention:
                    return RenderArgs.ForegroundColors.Attention;
                case AdaptiveTextColor.Dark:
                    return RenderArgs.ForegroundColors.Dark;
                case AdaptiveTextColor.Good:
                    return RenderArgs.ForegroundColors.Good;
                case AdaptiveTextColor.Light:
                    return RenderArgs.ForegroundColors.Light;
                case AdaptiveTextColor.Warning:
                    return RenderArgs.ForegroundColors.Warning;
                case AdaptiveTextColor.Default:
                default:
                    return RenderArgs.ForegroundColors.Default;
            }
        }

        /// <summary>
        /// Casts framework element to a TagContent element
        /// </summary>
        /// <param name="element">Rendered element that contains tag</param>
        /// <returns>Casted tag content</returns>
        private TagContent GetTagContent(FrameworkElement element)
        {
            if ((element != null) && (element.Tag != null) && (element.Tag is TagContent tagContent))
            {
                return tagContent;
            }
            return null;
        }       

        /// <summary>
        /// Changes the visibility of the specified elements as defined
        /// </summary>
        /// <param name="targetElements">Taget elements to change visibility</param>
        public void ToggleVisibility(IEnumerable<AdaptiveTargetElement> targetElements)
        {
            HashSet<Grid> elementContainers = new HashSet<Grid>();

            foreach (AdaptiveTargetElement targetElement in targetElements)
            {
                var element = LogicalTreeHelper.FindLogicalNode(CardRoot, targetElement.ElementId);

                if (element != null && element is FrameworkElement elementFrameworkElement)
                {
                    bool isCurrentlyVisible = (elementFrameworkElement.Visibility == Visibility.Visible);

                    // if we read something with the format {"elementId": <id>", "isVisible": true} or
                    // we just read the id and the element is not visible;
                    // otherwise if we read something with the format {"elementId": <id>", "isVisible": false} or
                    // we just read the id and the element is visible
                    bool newVisibility = (targetElement.IsVisible.HasValue && targetElement.IsVisible.Value) ||
                                         (!targetElement.IsVisible.HasValue && !isCurrentlyVisible);

                    TagContent tagContent = GetTagContent(elementFrameworkElement);

                    RendererUtil.SetVisibility(elementFrameworkElement, newVisibility, tagContent);

                    if (tagContent != null)
                    {
                        elementContainers.Add(tagContent.ParentContainerElement);
                    }
                }
            }

            foreach (Grid elementContainer in elementContainers)
            {
                ResetSeparatorVisibilityInsideContainer(elementContainer);
            }

        }

        /// <summary>
        /// Gets the actual rendered element as elements with 'stretch' height are contained inside a StackPanel
        /// </summary>
        /// <param name="element">Element or StackPanel that contains rendered element</param>
        /// <returns>Actual rendered element</returns>
        private FrameworkElement GetRenderedElement(FrameworkElement element)
        {
            if (element is StackPanel containerPanel)
            {
                UIElement uiElement = containerPanel.Children[0];

                if (uiElement is FrameworkElement frameworkElement)
                {
                    return frameworkElement;
                }
            }

            return element;
        }

        private void HandleSeparatorAndSpacing(bool isFirstVisible, FrameworkElement element, TagContent tagContent)
        {
            // Hide the spacing / separator for the first element
            // Separators and spacings are added as a grid
            Grid separator = tagContent.Separator;

            if (separator != null)
            {
                separator.Visibility = isFirstVisible ? Visibility.Collapsed : Visibility.Visible;
            }
        }

        /// <summary>
        /// Hides the first separator and fixes the visibility for the other visible separators
        /// </summary>
        /// <param name="uiContainer">Renderered element container</param>
        public void ResetSeparatorVisibilityInsideContainer(Grid uiContainer)
        {
            bool isFirstVisible = true;
            foreach (FrameworkElement element in uiContainer.Children)
            {
                if (element.Visibility == Visibility.Visible)
                {
                    TagContent tagContent = GetTagContent(element);

                    if (tagContent != null)
                    {
                        HandleSeparatorAndSpacing(isFirstVisible, element, tagContent);
                        isFirstVisible = false;
                    }
                }
            }
        }

        public void ToggleShowCardVisibility(Button uiAction)
        {
            FrameworkElement card = ActionShowCards[uiAction];
            var id = uiAction.GetContext() as AdaptiveInternalID;
            if (id == null)
            {
                Warnings.Add(new AdaptiveWarning(-1, $"Toggling visibility event handling is dropped " +
                    $"since the action set the button belongs to has null internal id"));
                return;
            }
            var peers = PeerShowCardsInActionSet[id];
            if (card != null && peers != null)
            {
                var targetVisibility = card.Visibility == Visibility.Visible ? Visibility.Collapsed : Visibility.Visible;
                // need to make sure we collapse all showcards before showing this one
                foreach (var showCard in peers)
                {
                    showCard.Visibility = Visibility.Collapsed;
                }

                card.Visibility = targetVisibility;
            }
        }

        private bool ValidateInputs(AdaptiveSubmitAction submitAction)
        {
            bool allInputsValid = true, firstInvalidInputFound = false;
            Dictionary<string, Func<string>> newInputBindings = new Dictionary<string, Func<string>>();

            // We clear the InputBindings collection to clear all the results
            InputBindings.Clear();

            List<string> inputsToValidate = RetrieveInputList(submitAction);

            // Iterate through all the elements and validate them
            foreach (string inputId in inputsToValidate)
            {
                AdaptiveInputValue inputValue = InputValues[inputId];
                bool inputIsValid = inputValue.Validate();
                allInputsValid = allInputsValid && inputIsValid;

                // If the validation failed, set focus to the first element that failed
                if (!allInputsValid && !firstInvalidInputFound)
                {
                    inputValue.SetFocus();
                    firstInvalidInputFound = true;
                }

                inputValue.ChangeVisualCueVisibility(inputIsValid);

                // Add the input value to the inputs bindings
                newInputBindings.Add(inputId, () => inputValue.GetValue());
            }

            // If the validation succeeded, then copy the result to the InputBindings
            if (allInputsValid)
            {
                foreach (string key in newInputBindings.Keys)
                {
                    InputBindings.Add(key, newInputBindings[key]);
                }
            }

            return allInputsValid;
        }

        private List<string> RetrieveInputList(AdaptiveSubmitAction submitAction)
        {
            List<string> inputList = new List<string>();
            AdaptiveInternalID submitActionCardId = SubmitActionCardId[submitAction];

            // While the card is not the main card, iterate through them
            // It's important to note that as we go from deep most upwards then we have to add the
            // inputs at the begining of the list to focus on the first one on validation
            while (!submitActionCardId.Equals(new AdaptiveInternalID()))
            {
                // Copy the inputs into the result
                if (InputsInCard.ContainsKey(submitActionCardId))
                {
                    inputList.InsertRange(0, InputsInCard[submitActionCardId]);
                }

                // Move to the parent card
                submitActionCardId = ParentCards[submitActionCardId];
            }

            return inputList;
        }

        public void AddInputToCard(AdaptiveInternalID cardId, string inputId)
        {
            if (!InputsInCard.ContainsKey(cardId))
            {
                InputsInCard.Add(cardId, new List<string>());
            }

            InputsInCard[cardId].Add(inputId);
        }

        // Dictionary where all the parent cards point to their parent cards, the parent for the main card must have ID = Invalid
        public Dictionary<AdaptiveInternalID, AdaptiveInternalID> ParentCards { get; set; }  = new Dictionary<AdaptiveInternalID, AdaptiveInternalID>();

        // Dictionary where we tie every Action.Submit to the card where it is contained, this help us knowing where should we start validating from
        public Dictionary<AdaptiveSubmitAction, AdaptiveInternalID> SubmitActionCardId { get; set; } = new Dictionary<AdaptiveSubmitAction, AdaptiveInternalID>();

        // Dictionary where we tie every input.Id (string) with the card internal Id 
        private Dictionary<AdaptiveInternalID, List<string>> InputsInCard = new Dictionary<AdaptiveInternalID, List<string>>();

        public Dictionary<string, AdaptiveInputValue> InputValues = new Dictionary<string, AdaptiveInputValue>();
    }
}
