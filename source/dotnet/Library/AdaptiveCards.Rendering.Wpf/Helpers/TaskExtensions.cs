// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Threading;
using System.Threading.Tasks;

namespace AdaptiveCards.Rendering.Wpf
{
    public static class TaskExtensions
    {
        private static readonly TaskScheduler _staScheduler = new StaTaskScheduler(1); //numberOfThreads: Environment.ProcessorCount);

        /// <summary>
        /// Starts a new STA thread. This is necessary for rendering WPF to bitmaps from a console app or server
        /// </summary>
        public static Task<T> StartNewSta<T>(this TaskFactory factory, Func<T> action)
        {
            return factory.StartNew(action, CancellationToken.None, TaskCreationOptions.None, _staScheduler);
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
