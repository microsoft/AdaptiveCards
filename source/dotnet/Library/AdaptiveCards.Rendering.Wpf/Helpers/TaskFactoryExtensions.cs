using System;
using System.Threading;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class TaskFactoryExtensions
    {
        private static readonly TaskScheduler _staScheduler = new StaTaskScheduler(numberOfThreads: Environment.ProcessorCount);

        public static Task<T> StartNewSta<T>(this TaskFactory factory, Func<T> action)
        {
            return factory.StartNew(action, CancellationToken.None, TaskCreationOptions.None, _staScheduler);
        }
    }
}