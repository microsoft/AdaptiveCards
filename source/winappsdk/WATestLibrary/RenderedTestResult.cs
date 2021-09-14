// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using AdaptiveCards.Rendering.WinUI3;
using System;
using Windows.UI.Xaml;

namespace WATestLibrary
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
