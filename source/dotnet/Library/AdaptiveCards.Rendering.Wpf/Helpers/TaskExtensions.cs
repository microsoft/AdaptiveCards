using System;
using System.Threading;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class TaskExtensions
    {
        private static readonly TaskScheduler _staScheduler = new StaTaskScheduler(1); //numberOfThreads: Environment.ProcessorCount);

        public static Task<T> StartNewSta<T>(this TaskFactory factory, Func<T> action)
        {
            return factory.StartNew(action, CancellationToken.None, TaskCreationOptions.None, _staScheduler);
        }

        public static async Task<T> WithCancellation<T>(this Task<T> task, CancellationToken cancellationToken)
        {
            var tcs = new TaskCompletionSource<bool>();
            using (cancellationToken.Register(
                s => ((TaskCompletionSource<bool>)s).TrySetResult(true), tcs))
                if (task != await Task.WhenAny(task, tcs.Task))
                    throw new OperationCanceledException(cancellationToken);
            return await task;
        }

        public static async Task WithCancellation(this Task task, CancellationToken cancellationToken)
        {
            var tcs = new TaskCompletionSource<object>();
            using (cancellationToken.Register(
                s => ((TaskCompletionSource<object>)s).TrySetResult(new object()), tcs))
                if (task != await Task.WhenAny(task, tcs.Task))
                    throw new OperationCanceledException(cancellationToken);
        }
    }
}