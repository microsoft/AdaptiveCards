// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;

namespace AdaptiveCardVisualizer
{
    public static class Settings
    {
        public static bool UseFixedDimensions
        {
            get { ApplicationData.Current.RoamingSettings.Values.TryGetValue("UseFixedDimensions", out object result); return result is bool && (bool)result; }
            set { ApplicationData.Current.RoamingSettings.Values["UseFixedDimensions"] = value; }
        }
    }
}
