using Jurassic;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class AdaptiveTransformer
    {
        private ScriptEngine _scriptEngine;

        public AdaptiveTransformer()
        {
            _scriptEngine = new ScriptEngine();

            // Load the JS script from embedded resource
            _scriptEngine.Execute(GetJS());
            _scriptEngine.Execute(GetJsHelper());
        }

        private static string _js;
        /// <summary>
        /// Gets the JavaScript templating library script. Result is cached after first time called.
        /// </summary>
        /// <returns></returns>
        private static string GetJS()
        {
            if (_js == null)
            {
                _js = EmbeddedResourceHelper.GetResource("AdaptiveCards.Templating.js.adaptivecards-templating.min.js");
            }
            return _js;
        }

        private static string _jsHelper;
        private static string GetJsHelper()
        {
            if (_jsHelper == null)
            {
                _jsHelper = EmbeddedResourceHelper.GetResource("AdaptiveCards.Templating.js.script.js");
            }
            return _jsHelper;
        }

        public string Transform(string jsonTemplate, string jsonData)
        {
            return _scriptEngine.CallGlobalFunction<string>("transform", jsonTemplate, jsonData);
        }
    }
}
