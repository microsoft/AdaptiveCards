using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using Windows.UI.Core;

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
            if(!TimerIsRunning)
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
            await Windows.ApplicationModel.Core.CoreApplication.MainView.CoreWindow.Dispatcher.RunAsync(CoreDispatcherPriority.Normal, () =>
            {
                GenericDocumentView.MakeErrorsLike();
            });
            
        }


    }
}
