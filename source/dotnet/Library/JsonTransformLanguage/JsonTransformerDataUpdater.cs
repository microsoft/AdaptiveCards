using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerDataUpdater
    {
        private List<JsonTransformerBinding> _enabledBindings = new List<JsonTransformerBinding>();

        public void EnableBinding(JsonTransformerBinding binding)
        {
            _enabledBindings.Add(binding);
        }

        public void UpdateData(JToken currentData, JToken updatedData)
        {
            if (currentData.Type != updatedData.Type)
            {
                throw new InvalidOperationException("Data types must match");
            }

            if (currentData is JObject currObj && updatedData is JObject updatedObj)
            {
                currObj.Merge(updatedObj);

                foreach (var b in _enabledBindings)
                {
                    HandleTriggerBinding(b, updatedObj, currObj);
                }
            }
            else
            {
                throw new InvalidOperationException("Data types must both be objects");
            }
        }

        private void HandleTriggerBinding(JsonTransformerBinding binding, JObject updatedObj, JObject newCurrData)
        {
            foreach (var d in binding.Dependencies)
            {
                if (ContainsDependency(d, updatedObj))
                {
                    binding.TriggerBindingUpdated(newCurrData);
                    return;
                }
            }
        }

        private bool ContainsDependency(string dependency, JObject updatedObj)
        {
            if (updatedObj.TryGetValue(dependency, out JToken val))
            {
                return true;
            }

            return false;
        }
    }
}
