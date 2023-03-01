// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Threading;
using System.Threading.Tasks;

#if USE_WINUI3
using CommunityToolkit.WinUI;
#else
using Windows.UI.Core;
#endif

namespace AdaptiveCardVisualizer.ViewModel
{
    public class KeyboardPressTimeCounter
    {
        private GenericDocumentViewModel GenericDocumentView;

        private DateTime LastKeyStroke;

        private bool TimerIsRunning;

        private Timer timer = null;
        private AutoResetEvent autoEvent = null;

        public KeyboardPressTimeCounter(GenericDocumentViewModel documentView)
        {
            GenericDocumentView = documentView;
            ResetCounter();
            TimerIsRunning = false;
        }

        public void ResetCounter()
        {
            LastKeyStroke = DateTime.Now;

            autoEvent = new AutoResetEvent(false);
            if (!TimerIsRunning)
            {
                timer = new Timer(CheckIfSendIsNecessary, autoEvent, 2000, 500);
            }

            TimerIsRunning = true;
        }

        public void CheckIfSendIsNecessary(Object stateInfo)
        {
            if ((DateTime.Now - LastKeyStroke).TotalSeconds >= 2)
            {
                autoEvent.Set();
                timer.Dispose();

                SendShowErrorsUpdateAsync();
                TimerIsRunning = false;
            }
            else
            {
                autoEvent.Reset();
            }
        }

        private async Task SendShowErrorsUpdateAsync()
        {
#if USE_WINUI3
            var dispatcher = Microsoft.UI.Dispatching.DispatcherQueue.GetForCurrentThread();
            if (dispatcher == null)
            { 
                var queueController = Microsoft.UI.Dispatching.DispatcherQueueController.CreateOnCurrentThread();
                dispatcher = queueController.DispatcherQueue;
            }
            // Default priority is Normal
            await dispatcher.EnqueueAsync(() =>
#else
            await Windows.ApplicationModel.Core.CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
#endif
            {
                GenericDocumentView.MakeErrorsLike();
            });
        }
    }
}
