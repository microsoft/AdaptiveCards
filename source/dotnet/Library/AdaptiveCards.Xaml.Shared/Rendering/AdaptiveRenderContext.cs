// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Threading.Tasks;
using System.Windows;
#if WPF
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
#elif XAMARIN
using Xamarin.Forms;
using FrameworkElement = Xamarin.Forms.View;
using Button = AdaptiveCards.Rendering.ContentButton;
#endif

namespace AdaptiveCards.Rendering.Wpf
{
    /// <summary>
    /// Context state for a render pass
    /// </summary>
    public class AdaptiveRenderContext
    {
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

#if WPF
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
#endif

#if WPF
        private readonly Dictionary<string, SolidColorBrush> _colors = new Dictionary<string, SolidColorBrush>();

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
#elif XAMARIN
        // TODO
        public object GetColorBrush(string color)
        {
            return null;
        }
#endif

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

#if WPF
                        if (!String.IsNullOrEmpty(element.Id))
                        {
                            rendered.Name = element.Id;
                        }
#endif

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
#if WPF
            if ((element != null) && (element.Tag != null) && (element.Tag is TagContent tagContent))
            {
                return tagContent;
            }
#endif
            return null;
        }

        /// <summary>
        /// Changes the visibility for the rendered element
        /// </summary>
        /// <param name="element">Rendered element to apply visibility</param>
        /// <param name="desiredVisibility">Visibility to be applied to the element</param>
        /// <param name="tagContent">Rendered element tag</param>
        public void SetVisibility(FrameworkElement element, bool desiredVisibility, TagContent tagContent)
        {
            // TagContents are only assigned to card elements so actions mustn't have a TagContent object tied to it
            // TagContents are used to save information on the rendered object as the element separator
            if (tagContent == null)
            {
                return;
            }

#if WPF
            bool elementIsCurrentlyVisible = (element.Visibility == Visibility.Visible);

            element.Visibility = desiredVisibility ? Visibility.Visible : Visibility.Collapsed;
#elif XAMARIN
            bool elementIsCurrentlyVisible = element.IsVisible;
            element.IsVisible = desiredVisibility;
#endif

            // Hides the separator if any was rendered
            Grid separator = tagContent.Separator;
            if (separator != null)
            {
#if WPF
                separator.Visibility = desiredVisibility ? Visibility.Visible : Visibility.Collapsed;
#elif XAMARIN
                separator.IsVisible = desiredVisibility;
#endif
            }

            // Elements (Rows) with RowDefinition having stars won't hide so we have to set the width to auto
            // Also, trying to set the same rowDefinition twice to the same element is not valid,
            // so we have to make a check first
            if ((tagContent.RowDefinition != null) && !(elementIsCurrentlyVisible && desiredVisibility))
            {
                RowDefinition rowDefinition = null;
                if (desiredVisibility)
                {
                    rowDefinition = tagContent.RowDefinition;
                }
                else
                {
                    // When the visibility is set to false, then set the row definition to auto
                    rowDefinition = new RowDefinition() { Height = GridLength.Auto };
                }

                tagContent.ParentContainerElement.RowDefinitions[tagContent.ViewIndex] = rowDefinition;
            }

            // Columns with ColumnDefinition having stars won't hide so we have to set the width to auto
            // Also, trying to set the same columnDefinition twice to the same element is not valid,
            // so we have to make a check first
            if ((tagContent.ColumnDefinition != null) && !(elementIsCurrentlyVisible && desiredVisibility))
            {
                ColumnDefinition columnDefinition = null;
                if (desiredVisibility)
                {
                    columnDefinition = tagContent.ColumnDefinition;
                }
                else
                {
                    columnDefinition = new ColumnDefinition() { Width = GridLength.Auto };
                }

                tagContent.ParentContainerElement.ColumnDefinitions[tagContent.ViewIndex] = columnDefinition;
            }
        }

        /// <summary>
        /// Changes the visibility of the specified elements as defined
        /// </summary>
        /// <param name="targetElements">Taget elements to change visibility</param>
        public void ToggleVisibility(IEnumerable<AdaptiveTargetElement> targetElements)
        {
#if WPF
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

                    SetVisibility(elementFrameworkElement, newVisibility, tagContent);

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
#endif
        }

#if WPF
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
#endif

        private void HandleSeparatorAndSpacing(bool isFirstVisible, FrameworkElement element, TagContent tagContent)
        {
            // Hide the spacing / separator for the first element
            // Separators and spacings are added as a grid
            Grid separator = tagContent.Separator;

            if (separator != null)
            {
#if WPF
                separator.Visibility = isFirstVisible ? Visibility.Collapsed : Visibility.Visible;
#elif XAMARIN
                separator.IsVisible = !isFirstVisible;
#endif
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
#if WPF
                if (element.Visibility == Visibility.Visible)
                {
                    TagContent tagContent = GetTagContent(element);

                    if (tagContent != null)
                    {
                        HandleSeparatorAndSpacing(isFirstVisible, element, tagContent);
                        isFirstVisible = false;
                    }
                }
#endif
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
#if WPF
                var targetVisibility = card.Visibility == Visibility.Visible ? Visibility.Collapsed : Visibility.Visible;
#elif XAMARIN
                var targetVisibility = !card.IsVisible;
#endif
                // need to make sure we collapse all showcards before showing this one
                foreach (var showCard in peers)
                {
#if WPF
                    showCard.Visibility = Visibility.Collapsed;
#elif XAMARIN
                    showCard.IsVisible = false;
#endif
                }

#if WPF
                card.Visibility = targetVisibility;
#elif XAMARIN
                card.IsVisible = targetVisibility;
#endif
            }
        }
    }
}
