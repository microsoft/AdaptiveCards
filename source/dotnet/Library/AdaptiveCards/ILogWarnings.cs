using System.Collections.Generic;

namespace AdaptiveCards
{
    internal interface ILogWarnings
    {
        List<AdaptiveWarning> Warnings { get; set; }
    }
}