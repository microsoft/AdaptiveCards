using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;

namespace JsonTransformLanguage
{
    public class JsonTransformerBinding : INotifyPropertyChanged
    {
        public event EventHandler BindingUpdated;
        public event PropertyChangedEventHandler PropertyChanged;

        [JsonProperty(PropertyName = "expression")]
        public string Expression { get; set; }

        [JsonProperty(PropertyName = "dependencies")]
        public string[] Dependencies { get; set; }

        [JsonIgnore]
        public object Value { get; set; }

        internal void TriggerBindingUpdated(JToken newCurrentData)
        {
            Value = JsonTransformer.Transform(JToken.FromObject(Expression), newCurrentData, null);
            BindingUpdated?.Invoke(this, new EventArgs());
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(nameof(Value)));
        }
    }
}
