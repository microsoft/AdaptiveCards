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
            return typeof(List<object>).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var array = JArray.Load(reader);
            List<object> list = array.ToObject<List<object>>();
            List<object> arrayList = new List<object>();

            foreach(object obj in list)
            {
                if(obj is string)
                {
                    arrayList.Add(obj);
                }
                else
                {
                    JObject jobj = (JObject)obj;
                    arrayList.Add(jobj.ToObject(typeof(AdaptiveTargetElement)));
                }
            }
            return arrayList;
        }

        public override bool CanWrite => false;

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }

    }
}
