using System.Collections.Generic;
using System.Linq;
using Xamarin.Forms;


namespace AdaptiveCards.Rendering
{
    public static partial class AdaptiveActionSetRenderer 
    {
        public static void AddActions(Grid uiContainer, List<AdaptiveAction> actions, RenderContext context, AdaptiveInternalID iid)
        {
            var actionsToProcess = actions
                .Take(context.Config.Actions.MaxActions).ToList();
            if (!actionsToProcess.Any())
                return;                
             
            // TODO: Bring back UniformGrid
            //var uiActionBar = new UniformGrid();

            var uiActionBar = new Grid();
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
