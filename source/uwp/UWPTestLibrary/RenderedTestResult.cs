// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.Uwp;
using System;
using Windows.UI.Xaml;

namespace UWPTestLibrary
{
    public class RenderedTestResult
    {
        public string Error { get; set; }
        public string RoundTrippedJSON { get; set; }
        public UIElement Tree { get; set; }
        public double CardWidth { get; set; }
        public WeakReference WeakCard { get; set; }

        public bool IsLeaked
        {
            get
            {
                return WeakCard != null ? WeakCard.Target != null : false;
            }
        }
    }
}
