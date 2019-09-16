// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace AdaptiveCards
{
    public class ToggleElementsConverter : JsonConverter
    {

        public override bool CanConvert(Type objectType)
        {
            return typeof(List<AdaptiveTargetElement>).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var array = JArray.Load(reader);
            List<object> list = array.ToObject<List<object>>();
            List<AdaptiveTargetElement> arrayList = new List<AdaptiveTargetElement>();

            foreach(object obj in list)
            {
                if(obj is string s)
                {
                    arrayList.Add(new AdaptiveTargetElement(s));
                }
                else
                {
                    JObject jobj = (JObject)obj;
                    arrayList.Add((AdaptiveTargetElement)jobj.ToObject(typeof(AdaptiveTargetElement)));
                }
            }
            return arrayList;
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            List<AdaptiveTargetElement> targetElements = (List<AdaptiveTargetElement>)value;

            JArray jArray = new JArray();

            foreach (var el in targetElements)
            {
                if (el.IsVisible == null)
                {
                    jArray.Add(JToken.FromObject(el.ElementId));
                }
                else
                {
                    jArray.Add(JToken.FromObject(el));
                }
            }

            jArray.WriteTo(writer);
        }

    }
}
