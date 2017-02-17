using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using WPF = System.Windows.Controls;
using Adaptive.Schema.Net;
using AC = Adaptive.Schema.Net;
using Newtonsoft.Json.Linq;
using System.Text.RegularExpressions;
using System;
using System.Text;

namespace Adaptive.Renderers
{
    public partial class AdaptiveXamlRenderer
    {
        private static Regex _regexBinding = new Regex(@"(?<property>\{\{\w+?\}\})+?", RegexOptions.Compiled | RegexOptions.ExplicitCapture);

        private UIElement _renderAction(ActionBase action, List<FrameworkElement> inputControls, FrameworkElement content = null)
        {
            if (action is ActionOpenUrl)
                return Render((ActionOpenUrl)action, inputControls, content);

            if (action is ActionSubmit)
                return Render((ActionSubmit)action, inputControls, content);

            if (action is ActionShowCard)
                return Render((ActionShowCard)action, inputControls, content);

            if (action is ActionHttp)
                return Render((ActionHttp)action, inputControls, content);

            return new Grid();
        }


        /// <summary>
        /// HttpAction
        /// </summary>
        /// <param name="httpAction"></param>
        /// <returns></returns>
        protected virtual UIElement Render(ActionHttp httpAction, List<FrameworkElement> inputControls, FrameworkElement content)
        {
            Button uiButton = _createActionButton(httpAction, content);
            uiButton.Click += (sender, e) =>
            {
                dynamic data = new JObject();
                _mergeDataFromControls(data, inputControls);

                string body = (string)httpAction.Body?.ToString() ?? String.Empty;

                OnAction?.Invoke(uiButton, new ActionEventArgs()
                {
                    Action = new ActionHttp()
                    {
                        Title = httpAction.Title,
                        Method = httpAction.Method,
                        Url = _bindData(data, httpAction.Url, url: true),
                        Headers = httpAction.Headers,
                        Body = _bindData(data, body),
                    },
                    Data = data
                });
            };
            return uiButton;
        }

        private static string _bindData(dynamic data, string body, bool url = false)
        {
            foreach (Match match in _regexBinding.Matches(body))
            {
                var key = match.Value.Trim('{', '}');
                var val = data[key]?.ToString() ?? String.Empty;
                if (url)
                    val = Uri.EscapeDataString(val);
                body = body.Replace(match.Value, val);
            }

            return body;
        }

        /// <summary>
        /// ShowCard
        /// </summary>
        /// <param name="showCardAction"></param>
        /// <returns></returns>
        protected virtual UIElement Render(ActionShowCard showCardAction, List<FrameworkElement> inputControls, FrameworkElement content)
        {
            Button uiButton = _createActionButton(showCardAction, content);
            uiButton.Click += (sender, e) =>
            {
                OnAction?.Invoke(uiButton, new ActionEventArgs() { Action = showCardAction, Data = null });
            };
            return uiButton;
        }

        /// <summary>
        /// OpenUrl
        /// </summary>
        /// <param name="openUrlAction"></param>
        /// <returns></returns>
        protected virtual UIElement Render(ActionOpenUrl openUrlAction, List<FrameworkElement> inputControls, FrameworkElement content)
        {
            Button uiButton = _createActionButton(openUrlAction, content);
            uiButton.Click += (sender, e) =>
            {
                OnAction?.Invoke(uiButton, new ActionEventArgs() { Action = openUrlAction });
            };
            return uiButton;
        }

        /// <summary>
        /// SubmitAction
        /// </summary>
        /// <param name="submitAction"></param>
        /// <returns></returns>
        protected virtual UIElement Render(ActionSubmit submitAction, List<FrameworkElement> inputControls, FrameworkElement content)
        {
            Button uiButton = _createActionButton(submitAction, content);
            uiButton.Click += (sender, e) =>
            {
                dynamic data = (submitAction.Data != null) ? ((JToken)submitAction.Data).DeepClone() : new JObject();
                _mergeDataFromControls(data, inputControls);

                OnAction?.Invoke(uiButton, new ActionEventArgs() { Action = submitAction, Data = data });
            };
            return uiButton;
        }

        ///// <summary>
        ///// CancelAction
        ///// </summary>
        ///// <param name="cancelAction"></param>
        ///// <returns></returns>
        //protected virtual UIElement Render(CancelAction cancelAction, List<FrameworkElement> inputControls, FrameworkElement content)
        //{
        //    Button uiButton = _createActionButton(cancelAction, content);
        //    uiButton.Click += (sender, e) =>
        //    {
        //        _resetInputControls(inputControls);
        //        OnAction?.Invoke(uiButton, new ActionEventArgs() { Action = cancelAction });
        //    };
        //    return uiButton;
        //}

        private Button _createActionButton(ActionBase action, FrameworkElement content)
        {
            var uiButton = new Button();
            if (content == null)
            {
                WPF.TextBlock uiTitle = new WPF.TextBlock() { Text = action.Title };
                uiTitle.Style = this.GetStyle("Adaptive.Action.Title");
                uiButton.Content = uiTitle;
                uiButton.Style = this.GetStyle($"Adaptive.Action.{action.GetType().Name}");
            }
            else
            {
                uiButton.Content = content;
                uiButton.Style = this.GetStyle($"Adaptive.Action.Tap");
            }
            return uiButton;
        }


    }
}