using System.Collections.Generic;

namespace AdaptiveCards
{
    internal interface ILogWarnings
    {
        IList<AdaptiveWarning> Warnings { get; set; }
    }
}