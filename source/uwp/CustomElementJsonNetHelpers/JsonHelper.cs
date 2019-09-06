using Windows.Data.Json;
using Newtonsoft.Json.Linq;

namespace CustomElementJsonNetHelpers
{
    // Provides static methods to aid in conversion between Newtonsoft.Json and Windows.Data.Json types
    internal class JsonHelper
    {
        static public JsonValue JTokenToJsonValue(JToken jtoken)
        {
            JsonValue value;

            switch (jtoken.Type)
            {
                case JTokenType.None:
                    {
                        value = JsonValue.CreateNullValue();
                        break;
                    }
                case JTokenType.Float:
                case JTokenType.Integer:
                    {
                        value = JsonValue.CreateNumberValue((double)jtoken);
                        break;
                    }
                case JTokenType.Boolean:
                    {
                        value = JsonValue.CreateBooleanValue((bool)jtoken);
                        break;
                    }
                case JTokenType.Array:
                case JTokenType.Object:
                    {
                        value = JsonValue.Parse(jtoken.ToString());
                        break;
                    }
                case JTokenType.String:
                default:
                    {
                        value = JsonValue.CreateStringValue((string)jtoken);
                        break;
                    }
            }

            return value;
        }

        static public JToken JsonValueToJToken(IJsonValue jsonValue)
        {
            switch (jsonValue.ValueType)
            {
                case JsonValueType.Boolean:
                    return new JValue(jsonValue.GetBoolean());

                case JsonValueType.Number:
                    return new JValue(jsonValue.GetNumber());

                case JsonValueType.String:
                    return new JValue(jsonValue.GetString());

                case JsonValueType.Object:
                    return JObject.Parse(jsonValue.GetObject().Stringify());

                case JsonValueType.Array:
                    return JObject.Parse(jsonValue.GetArray().Stringify());

                case JsonValueType.Null:
                default:
                    return JValue.CreateNull();
            }
        }
    }
}
