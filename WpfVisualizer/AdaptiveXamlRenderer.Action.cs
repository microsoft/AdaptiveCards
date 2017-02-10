using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml;
using MarkedNet;
using Xceed.Wpf.Toolkit;
using AC = Adaptive.Schema.Net;

namespace WpfVisualizer
{
    public partial class AdaptiveXamlRenderer
    {

        public UIElement Render(AC.ActionBase action, List<Control> inputControls, object content = null)
        {
            if (action is AC.OpenUrlAction)
                return Render((AC.OpenUrlAction)action, inputControls, content);

            if (action is AC.SubmitAction)
                return Render((AC.SubmitAction)action, inputControls, content);

            if (action is AC.CancelAction)
                return Render((AC.CancelAction)action, inputControls, content);

            if (action is AC.ShowCardAction)
                return Render((AC.ShowCardAction)action, inputControls, content);

            if (action is AC.HttpAction)
                return Render((AC.HttpAction)action, inputControls, content);

            return new Grid();
        }


        /// <summary>
        /// HttpAction
        /// </summary>
        /// <param name="httpAction"></param>
        /// <returns></returns>
        public UIElement Render(AC.HttpAction httpAction, List<Control> inputControls, object content)
        {
            var uiActionGroup = new Grid();
            var actionInstance = new ActionInstance() { Action = httpAction, Inputs = inputControls };
            Hyperlink link = new Hyperlink(new Run() { Text = httpAction.Title });
            link.Tag = actionInstance;
            return uiActionGroup;
        }

        /// <summary>
        /// ShowCard
        /// </summary>
        /// <param name="showCardAction"></param>
        /// <returns></returns>
        public UIElement Render(AC.ShowCardAction showCardAction, List<Control> inputControls, object content)
        {
            Button uiButton = _createActionButton(showCardAction, content);
            uiButton.Click += (sender, e) =>
            {
                ShowCardWindow dialog = new ShowCardWindow(showCardAction.Card, this.resources);
                dialog.ShowDialog();
            };
            return uiButton;
        }

        /// <summary>
        /// OpenUrl
        /// </summary>
        /// <param name="openUrlAction"></param>
        /// <returns></returns>
        public UIElement Render(AC.OpenUrlAction openUrlAction, List<Control> inputControls, object content)
        {
            Button uiButton = _createActionButton(openUrlAction, content);
            uiButton.Click += (sender, e) =>
            {
                Process.Start(openUrlAction.Url);
            };
            return uiButton;
        }

        /// <summary>
        /// SubmitAction
        /// </summary>
        /// <param name="submitAction"></param>
        /// <returns></returns>
        public UIElement Render(AC.SubmitAction submitAction, List<Control> inputControls, object content)
        {
            Button uiButton = _createActionButton(submitAction, content);
            uiButton.Click += (sender, e) =>
            {
            };
            return uiButton;
        }

        /// <summary>
        /// CancelAction
        /// </summary>
        /// <param name="cancelAction"></param>
        /// <returns></returns>
        public UIElement Render(AC.CancelAction cancelAction, List<Control> inputControls, object content)
        {
            Button uiButton = _createActionButton(cancelAction, content);
            uiButton.Click += (sender, e) =>
            {
                ActionInstance.Reset(inputControls);
                var hostWindow = uiButton.DataContext as Window;
                if (hostWindow is ShowCardWindow)
                    hostWindow.Close();
            };
            return uiButton;
        }
        private Button _createActionButton(AC.ActionBase action, object content)
        {
            var uiButton = new Button();
            if (content == null)
            {
                TextBlock uiTitle = new TextBlock() { Text = action.Title };
                uiTitle.Style = resources["Adaptive.Action.Title"] as Style;
                uiButton.Content = uiTitle;
            }
            else
                uiButton.Content = content;
            uiButton.Style = resources[$"Adaptive.Action.{action.GetType().Name}"] as Style;
            return uiButton;
        }


    }
}