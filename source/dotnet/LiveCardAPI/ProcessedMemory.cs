using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LiveCardAPI
{
    public class ProcessedMemory<T>
    {
        private HashSet<string> memory = new HashSet<string>();
        private Func<T, string> identity;

        public ProcessedMemory(Func<T, string> identity)
        {
            this.identity = identity;
        }

        public bool UnProcessed(T item)
        {
            return !memory.Contains(this.identity(item));
        }

        public void MarkProcessed(T item)
        {
            memory.Add(this.identity(item));
        }

        public void Reset(T item)
        {
            memory.Remove(identity(item));
        }

        public void ResetAll()
        {
            this.memory.Clear();
        }
    }

    //public static class OnceExtensions
    //{
    //    public static IEnumerable<T> UnProcessed<T>(this IEnumerable<T> items, ProcessedMemory<T> once)
    //    {
    //        foreach (var item in items)
    //        {
    //            if (once.UnProcessed(item))
    //            {
    //                once.Processed(item);
    //                yield return item;
    //            }
    //        }
    //        yield break;
    //    }
    //}
}
