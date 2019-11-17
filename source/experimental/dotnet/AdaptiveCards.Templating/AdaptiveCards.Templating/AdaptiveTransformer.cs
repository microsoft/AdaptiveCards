using Jurassic;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards.Templating
{
    public class AdaptiveTemplate
    {
        private ScriptEngine _scriptEngine;

        public AdaptiveTemplate()
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

        /// <summary>
        /// Expand the template and bind the data
        /// </summary>
        /// <param name="jsonTemplate">Your Json Template</param>
        /// <param name="jsonData">The Data to bind (Json Formatted)</param>
        /// <returns></returns>
        public string Expand(string jsonTemplate, string jsonData)
        {
            return _scriptEngine.CallGlobalFunction<string>("expand", jsonTemplate, jsonData);
        }


        /// <summary>
        /// Expand the template and bind the data
        /// </summary>
        /// <param name="jsonTemplate">Your Json Template</param>
        /// <param name="jsonData">The Data to bind (Serializable Object)</param>
        /// <returns></returns>
        public string Expand(string jsonTemplate, object Data)
        {
            var jsonData = JsonConvert.SerializeObject(Data,
                new JsonSerializerSettings() { ReferenceLoopHandling = ReferenceLoopHandling.Ignore });
            return _scriptEngine.CallGlobalFunction<string>("expand", jsonTemplate, jsonData);
        }

    }
}
