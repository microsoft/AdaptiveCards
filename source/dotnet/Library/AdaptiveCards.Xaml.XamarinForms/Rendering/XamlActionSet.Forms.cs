using System.Collections.Generic;
using System.Linq;
using AsNum.XFControls;
using Xamarin.Forms;


namespace AdaptiveCards.Rendering
{
    public static partial class XamlActionSet 
    {
        public static void AddActions(Grid uiContainer, List<ActionBase> actions, RenderContext context, string[] supportedActions, int maxActions)
        {

            if (supportedActions == null)
                return;
            var actionsToProcess = actions
                .Where(a => supportedActions?.Contains(a.Type) == true)
                .Take(maxActions).ToList();
            if (!actionsToProcess.Any())
                return;                
                   
            var uiActionBar = new UniformGrid();
            //uiActionBar.Rows = 1;
            //uiActionBar.HorizontalAlignment = System.Windows.HorizontalAlignment.Right;
            //uiActionBar.VerticalAlignment = System.Windows.VerticalAlignment.Bottom;

            int iCol = 0;
            foreach (var action in actionsToProcess)
            {
                // add actions
                var uiAction = context.Render(action);
                if (uiAction != null)
                {
                    Grid.SetColumn(uiAction, iCol++);
                    uiActionBar.Children.Add(uiAction);
                }
            }
            uiActionBar.Style = context.GetStyle("Adaptive.Actions");
            uiContainer.RowDefinitions.Add(new RowDefinition() { Height = GridLength.Auto });
            Grid.SetRow(uiActionBar, uiContainer.RowDefinitions.Count - 1);
            uiContainer.Children.Add(uiActionBar);
        }
    }
}