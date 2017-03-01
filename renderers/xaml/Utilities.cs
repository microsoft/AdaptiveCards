using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Adaptive;

namespace Adaptive
{
    /// <summary>
    /// Renderer of AdaptiveCard schema into ElementT types 
    /// </summary>
    /// <typeparam name="ElementT">the base type of rendered elements</typeparam>
    public static class Utilities
    {
        private static Regex TextFunctionRegex = new Regex(@"\{\{(?<func>DATE|TIME){1}\((?<date>.+?){1}(?:,\s*(?<hint>Short|Long){1}\s*)??\)\}\}", RegexOptions.Compiled | RegexOptions.ExplicitCapture | RegexOptions.IgnoreCase);
        private static Regex _regexBinding = new Regex(@"(?<property>\{\{\w+?\}\})+?", RegexOptions.Compiled | RegexOptions.ExplicitCapture);

        private enum Functions { DATE, TIME };

        private enum TimeHints { LONG, SHORT };

        /// <summary>
        /// This funct will return modified text replacing {{DATE|TIME()}} style functions as the formatted text
        /// </summary>
        /// <param name="text"></param>
        /// <returns></returns>
        public static string ApplyTextFunctions(string text)
        {
            foreach (Match match in TextFunctionRegex.Matches(text))
            {
                Functions function;
                if (Enum.TryParse<Functions>(match.Groups[1].Value.ToUpper(), out function))
                {
                    DateTime date;
                    if (DateTime.TryParse(match.Groups[2].Value, out date))
                    {
                        TimeHints timeHint;
                        if (!Enum.TryParse<TimeHints>(match.Groups[3].Value.ToUpper(), out timeHint))
                            timeHint = TimeHints.LONG;

                        string dateTimeFormat = "D";
                        if (function == Functions.DATE)
                        {
                            dateTimeFormat = (timeHint == TimeHints.LONG) ? "D" : "d";
                        }
                        else if (function == Functions.TIME)
                        {
                            dateTimeFormat = (timeHint == TimeHints.LONG) ? "T" : "t";
                        }
                        text = text.Replace(match.Value, date.ToString(dateTimeFormat));
                    }
                }
            }
            return text;
        }

        /// <summary>
        /// This function will parse text for {{binding}} statements and replace with appropriate values from the data object passed in
        /// </summary>
        /// <param name="data">data to bind fromt</param>
        /// <param name="text"></param>
        /// <param name="url">true if url text is a url (escaping will be applied to the vaue of the binding)</param>
        /// <returns></returns>
        public static string BindData(dynamic data, string text, bool url = false)
        {
            foreach (Match match in _regexBinding.Matches(text))
            {
                var key = match.Value.Trim('{', '}');
                var val = data[key]?.ToString() ?? String.Empty;
                if (url)
                    val = Uri.EscapeDataString(val);
                text = text.Replace(match.Value, val);
            }

            return text;
        }

        /// <summary>
        /// Render card to desired width (height is variable)
        /// </summary>
        /// <param name="card">card to render</param>
        /// <param name="width">desired width of image</param>
        /// <returns>BitmapSource of the card</returns>
        public static async Task<BitmapSource> XamlToImageAsync(UIElement uiElement, int width)
        {
            uiElement.Measure(new System.Windows.Size(width, 4000));
            uiElement.Arrange(new Rect(new System.Windows.Size(width, uiElement.DesiredSize.Height)));
            uiElement.UpdateLayout();

            RenderTargetBitmap bitmapImage = new RenderTargetBitmap((int)width, (int)uiElement.DesiredSize.Height, 96, 96, PixelFormats.Default);
            await Task.Delay(1000);
            // Dispatcher.Invoke(new Action(() => { }), DispatcherPriority.ContextIdle, null);
            bitmapImage.Render(uiElement);
            return bitmapImage;
        }

    }
}
