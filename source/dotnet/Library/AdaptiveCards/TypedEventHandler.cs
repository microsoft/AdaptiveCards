using System;

namespace AdaptiveCards
{
    public delegate void TypedEventHandler<in TSender, in TEventArgs>(
        TSender sender,
        TEventArgs e
    ) where TEventArgs : EventArgs;
}