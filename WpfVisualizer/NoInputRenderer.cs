using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using Xceed.Wpf.Toolkit;
using Adaptive.Schema.Net;
using Newtonsoft.Json.Linq;
using Adaptive.Renderers;

namespace WpfVisualizer
{
    public class NoInputAdaptiveRenderer : AdaptiveXamlRenderer
    {

        public NoInputAdaptiveRenderer(ResourceDictionary resources) : base(resources)
        {
        }

        protected override Style GetStyle(string styleName)
        {
            if (!styleName.Contains(".Tap") && styleName.Contains(".Input") || styleName.Contains(".Action"))
            {
                return this.Resources["Hidden"] as Style;
            }

            return base.GetStyle(styleName);
        }
    }
}