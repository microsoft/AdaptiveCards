using System;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Threading;

public static class AsyncPump
{
    public static void Run(Func<Task> func)
    {
        if (func == null) throw new ArgumentNullException("func");

        var prevCtx = SynchronizationContext.Current;
        try
        {
            var syncCtx = new DispatcherSynchronizationContext();
            SynchronizationContext.SetSynchronizationContext(syncCtx);

            var t = func();
            if (t == null) throw new InvalidOperationException();

            var frame = new DispatcherFrame();
            t.ContinueWith(_ => { frame.Continue = false; },
                TaskScheduler.Default);
            Dispatcher.PushFrame(frame);

            t.GetAwaiter().GetResult();
        }
        finally
        {
            SynchronizationContext.SetSynchronizationContext(prevCtx);
        }
    }
}