using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class AdaptiveElementDefinitions : Dictionary<string, object>
    {
        public AdaptiveElementDefinitions() { }

        internal AdaptiveElementDefinitions(Dictionary<string, object> existing) : base(existing) { }

        public bool TryGetElementDefinition(string typeName, out AdaptiveElementDefinition elementDefinition)
        {
            if (this.TryGetValue(typeName, out object defObj))
            {
                if (defObj is AdaptiveElementDefinition existingDefinition)
                {
                    elementDefinition = existingDefinition;
                    return true;
                }

                string definition;
                if (defObj is string url)
                {
                    HttpClient c = new HttpClient();
                    var task = c.GetStringAsync(url);
                    task.Wait();
                    definition = task.Result;
                }
                else
                {
                    definition = defObj.ToString();
                }

                AdaptiveElementDefinition parsedDefinition = JsonConvert.DeserializeObject<AdaptiveElementDefinition>(definition, new JsonSerializerSettings
                {
                    Converters = { new StrictIntConverter() }
                });

                if (parsedDefinition.Element != null)
                {
                    // Cache it for next time
                    this[typeName] = parsedDefinition;
                    elementDefinition = parsedDefinition;
                    return true;
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("Element definition was empty for " + typeName);
                    elementDefinition = null;
                    return false;
                }
            }

            System.Diagnostics.Debug.WriteLine("No element definition found for " + typeName);
            elementDefinition = null;
            return false;
        }
    }
}
