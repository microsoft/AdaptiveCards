using System;
using System.Threading;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class TaskFactoryExtensions
    {
        private static readonly TaskScheduler _staScheduler = new StaTaskScheduler(numberOfThreads: Environment.ProcessorCount);

        public static Task<TResult> StartNewSta<TResult>(this TaskFactory factory, Func<TResult> action)
        {
            return factory.StartNew(action, CancellationToken.None, TaskCreationOptions.None, _staScheduler);
        }
    }
}