using System;
using System.Diagnostics;
using System.Threading.Tasks;
using System.Windows;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class LayoutHelpers
    {
        public static Task AwaitLayoutUpdated(this FrameworkElement element)
        {
            var tcs = new TaskCompletionSource<object>();
            element.InvokeOnLayoutUpdated(() =>
            {
                Debug.WriteLine("Layout updated");
                tcs.SetResult(new object());
            });
            // TODO: This delay should not really be necessary? But the images don't load property to image if I remove it
            return Task.WhenAny(tcs.Task, Task.Delay(10));
        }

        public static void InvokeOnLayoutUpdated(this FrameworkElement element, Action action)
        {
            void Handler(object sender, EventArgs args)
            {
                action();
                element.LayoutUpdated -= Handler;
            }

            element.LayoutUpdated += Handler;
            element.UpdateLayout();
        }
    }
}
