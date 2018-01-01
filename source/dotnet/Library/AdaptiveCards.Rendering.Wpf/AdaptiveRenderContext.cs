using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Newtonsoft.Json.Linq;
using System.Linq;
using System.Reflection;
using System.Windows.Controls;
using System.Windows.Markup;

namespace AdaptiveCards.Rendering.Wpf
{
    public class AdaptiveRenderContext
    {
        private readonly Func<string, MemoryStream> _imageResolver;
        private readonly Dictionary<string, SolidColorBrush> _colors = new Dictionary<string, SolidColorBrush>();

        public AdaptiveRenderContext(Action<object, AdaptiveActionEventArgs> actionCallback,
            Action<object, MissingInputEventArgs> missingDataCallback,
            Func<string, MemoryStream> imageResolver = null)
        {
            if (actionCallback != null)
                OnAction += (obj, args) => actionCallback(obj, args);

            if (missingDataCallback != null)
                OnMissingInput += (obj, args) => missingDataCallback(obj, args);

            _imageResolver = imageResolver;
        }

        public AdaptiveHostConfig Config { get; set; } = new AdaptiveHostConfig();

        public IList<AdaptiveWarning> Warnings { get; } = new List<AdaptiveWarning>();

        public AdaptiveElementRenderers<FrameworkElement, AdaptiveRenderContext> ElementRenderers { get; set; }

        public INameScope Namescope { get; set; }

        public BitmapImage ResolveImageSource(string url)
        {
            BitmapImage source = null;
            // off screen rendering can pass already loaded image to us so we can render immediately
            var stream = _imageResolver?.Invoke(url);
            if (stream != null)
            {
                source = new BitmapImage();
                source.BeginInit();
                source.StreamSource = stream;
                source.EndInit();
            }
            return source ?? new BitmapImage(new Uri(url));
        }


        public event EventHandler<AdaptiveActionEventArgs> OnAction;

        /// <summary>
        /// Event fires when missing input for submit/http actions
        /// </summary>
        public event EventHandler<MissingInputEventArgs> OnMissingInput;

        public void InvokeAction(FrameworkElement ui, AdaptiveActionEventArgs args)
        {
            OnAction?.Invoke(ui, args);
        }

        public void MissingInput(AdaptiveAction sender, MissingInputEventArgs args)
        {
            OnMissingInput?.Invoke(sender, args);
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

        public ResourceDictionary Resources { get; set; }

        public AdaptiveActionHandlers ActionHandlers { get; set; }

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
            var renderer = ElementRenderers.Get(element.GetType());
            if (renderer != null)
            {
                var frameworkElement = renderer.Invoke(element, this);
                // set dataContext to source object
                frameworkElement.DataContext = element;
                frameworkElement.Name = element.Id;

                if (element is AdaptiveElement)
                {
                    AdaptiveElement el = element as AdaptiveElement;
                    foreach (var evt in el.Events)
                    {
                        switch (evt)
                        {
                            case EventTypes.OnClick:
                                {
                                    UIElement uiElement = frameworkElement as UIElement;
                                    uiElement.MouseLeftButtonDown += MouseLeftButtonDown;
                                    uiElement.MouseLeftButtonUp += MouseLeftButtonUp;
                                }
                                break;
                            case EventTypes.OnMouseEnter:
                                BindEvent(frameworkElement, evt, "MouseEnter");
                                break;
                            case EventTypes.OnMouseLeave:
                                BindEvent(frameworkElement, evt, "MouseLeave");
                                break;
                            case EventTypes.OnFocus:
                                BindEvent(frameworkElement, evt, "GotFocus");
                                break;
                            case EventTypes.OnBlur:
                                BindEvent(frameworkElement, evt, "LostFocus");
                                break;
                            case EventTypes.OnKey:
                                BindEvent(frameworkElement, evt, "KeyDown");
                                break;
                            case EventTypes.OnTextChanged:
                                BindEvent(frameworkElement, evt, "TextChanged");
                                break;
                            case EventTypes.OnSelectionChanged:
                                //                                BindEvent(frameworkElement, evt, "TextChanged");
                                break;
                        }
                    }
                }
                return frameworkElement;
            }
            else
            {
                Warnings.Add(new AdaptiveWarning(-1, $"No renderer for element type '{element.Type}'"));
                return null;
            }
        }

        private void MouseLeftButtonUp(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            UIElement uie = sender as UIElement;
            if (uie != null)
            {
                uie.CaptureMouse();
            }
        }

        private void MouseLeftButtonDown(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            UIElement uie = sender as UIElement;
            if (uie != null && uie.IsMouseCaptured)
            {
                uie.ReleaseMouseCapture();
                UIElement uiElement = e.OriginalSource as UIElement;
                if (uiElement != null && uiElement.InputHitTest(e.GetPosition(uiElement)) != null)
                {
                    AdaptiveElement element = ((FrameworkElement)sender).DataContext as AdaptiveElement;
                    element.FireClick();
                }
            }
        }

        private void KeyDownbinding(object sender, System.Windows.Input.KeyEventArgs e)
        {
            AdaptiveInput element = ((FrameworkElement)sender).DataContext as AdaptiveInput;
            if (element != null)
                element.FireKey(e.Key.ToString());
        }

        private void TextChangedBinding(object sender, System.Windows.Controls.TextChangedEventArgs e)
        {
            AdaptiveInput element = ((FrameworkElement)sender).DataContext as AdaptiveInput;
            if (element != null)
            {
                var tb = sender as TextBlock;
                if (tb != null)
                    element.FireTextChanged(tb.Text);
            }
        }

        private void LostFocusBinding(object sender, RoutedEventArgs e)
        {
            AdaptiveInput element = ((FrameworkElement)sender).DataContext as AdaptiveInput;
            if (element != null)
                element.FireBlur();
        }

        private void GotFocusBinding(object sender, RoutedEventArgs e)
        {
            AdaptiveInput element = ((FrameworkElement)sender).DataContext as AdaptiveInput;
            if (element != null)
                element.FireFocus();
        }
        private void MouseDownBinding(object sender, System.Windows.Input.MouseButtonEventArgs e)
        {
            AdaptiveElement element = ((FrameworkElement)sender).DataContext as AdaptiveElement;
            if (element != null)
                element.FireClick();
        }

        private void MouseLeaveBinding(object sender, System.Windows.Input.MouseEventArgs e)
        {
            AdaptiveElement element = ((FrameworkElement)sender).DataContext as AdaptiveElement;
            if (element != null)
                element.FireMouseLeave();
        }

        private void MouseEnterBinding(object sender, System.Windows.Input.MouseEventArgs e)
        {
            AdaptiveElement element = ((FrameworkElement)sender).DataContext as AdaptiveElement;
            if (element != null)
                element.FireMouseEnter();
        }

        private void BindEvent(FrameworkElement frameworkElement, string evt, string nativeEventName)
        {
            var eventInfo = frameworkElement.GetType().GetEvent(nativeEventName, BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
            if (eventInfo != null)
            {
                var methodInfo = this.GetType().GetMethod($"{nativeEventName}Binding", BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
                if (methodInfo != null)
                    eventInfo.AddEventHandler(frameworkElement, Delegate.CreateDelegate(eventInfo.EventHandlerType, this, methodInfo));
                else
                    throw new Exception($"binding {nativeEventName} => {evt} failed");
            }
        }


        public Dictionary<string, Func<string>> InputBindings = new Dictionary<string, Func<string>>();
    }
}
