// Copyright (c) Microsoft Corporation. All rights reserved. 
// Licensed under the MIT License. 
using Newtonsoft.Json.Linq;
using System.Collections.Generic;
using System.Net;
using System.Threading;
using System.Timers;
using Windows.UI.Xaml;

namespace UWPDriver
{
    public class BitmapTimer : System.Timers.Timer
    {
        public BitmapTimer(double interval) : base(interval) { }
        public FrameworkElement adaptiveCardElement { get; set; }
        public HttpListenerContext context { get; set; }
        public BoolWrapper bitmapCreated { get; set; }

        public JObject resultJson { get; set; }
        public List<string> warningList { get; set; }
        public List<string> errorList { get; set; }

        public Semaphore signal { get; set; }

    }
}
