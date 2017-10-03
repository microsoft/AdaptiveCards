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
        public static bool UseAsyncRenderMethod
        {
            get { ApplicationData.Current.RoamingSettings.Values.TryGetValue("UseAsyncRenderMethod", out object result); return result is bool && (bool)result; }
            set { ApplicationData.Current.RoamingSettings.Values["UseAsyncRenderMethod"] = value; }
        }
    }
}
