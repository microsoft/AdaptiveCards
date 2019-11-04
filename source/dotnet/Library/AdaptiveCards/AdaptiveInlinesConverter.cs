// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Reflection;

namespace AdaptiveCards
{
    class AdaptiveInlinesConverter : AdaptiveTypedBaseElementConverter 
    {
        public override bool CanRead => true;

        public override bool CanWrite => false;

        public override bool CanConvert(Type objectType)
        {
            return typeof(List<IAdaptiveInline>).GetTypeInfo().IsAssignableFrom(objectType.GetTypeInfo());
        }

        public override object ReadJson(JsonReader reader, Type objectType, object existingValue, JsonSerializer serializer)
        {
            var array = JArray.Load(reader);
            List<object> list = array.ToObject<List<object>>();
            List<IAdaptiveInline> arrayList = new List<IAdaptiveInline>();
            var serializerSettigns = new JsonSerializerSettings
            {
                ContractResolver = new WarningLoggingContractResolver(new AdaptiveCardParseResult(), ParseContext),
                Converters = { new StrictIntConverter() }
            };


            // We only support text runs for now, which can be specified as either a string or an object
            foreach (object obj in list)
            {
                if (obj is string s)
                {
                    arrayList.Add(new AdaptiveTextRun(s));
                }
                else
                {
                    JObject jobj = (JObject)obj;
                    if (jobj.Value<string>("type") != AdaptiveTextRun.TypeName)
                    {
                        throw new AdaptiveSerializationException($"Property 'type' must be '{AdaptiveTextRun.TypeName}'");
                    }

                    if (ParseContext == null)
                    {
                        ParseContext = new ParseContext();
                    }

                    var adaptiveInline = JsonConvert.DeserializeObject<AdaptiveTextRun>(jobj.ToString(), new JsonSerializerSettings
                    {
                        ContractResolver = new WarningLoggingContractResolver(new AdaptiveCardParseResult(), ParseContext),
                        Converters = { new StrictIntConverter() }
                    });
                    arrayList.Add(adaptiveInline);
                }
            }
            return arrayList;
        }

        public override void WriteJson(JsonWriter writer, object value, JsonSerializer serializer)
        {
            throw new NotImplementedException();
        }
    }
}
