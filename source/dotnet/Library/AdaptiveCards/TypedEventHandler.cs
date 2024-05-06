// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;

namespace AdaptiveCards
{
    /// <summary>
    /// Delegate for typed events
    /// </summary>
    /// <typeparam name="TSender"></typeparam>
    /// <typeparam name="TEventArgs"></typeparam>
    /// <param name="sender"></param>
    /// <param name="e"></param>
    public delegate void TypedEventHandler<in TSender, in TEventArgs>(
        TSender sender,
        TEventArgs e
    ) where TEventArgs : EventArgs;
}
