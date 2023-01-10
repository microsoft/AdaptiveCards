using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Text;

namespace AdaptiveCards
{
    internal class AdaptiveSelectActionConverter : JsonConverter<AdaptiveSelectAction>
    {
        public override AdaptiveSelectAction ReadJson(JsonReader reader, Type objectType, AdaptiveSelectAction existingValue, bool hasExistingValue, JsonSerializer serializer)
        {
            var job = (JObject)serializer.Deserialize(reader);
            var selectAction = new AdaptiveSelectAction();
            switch ((string)job["type"])
            {
                case AdaptiveOpenUrlAction.TypeName:
                    selectAction.Action = job.ToObject<AdaptiveOpenUrlAction>();
                    break;
                case AdaptiveSubmitAction.TypeName:
                    selectAction.Action = job.ToObject<AdaptiveSubmitAction>();
                    break;
                case AdaptiveToggleVisibilityAction.TypeName:
                    selectAction.Action = job.ToObject<AdaptiveToggleVisibilityAction>();
                    break;
                case AdaptiveExecuteAction.TypeName:
                    selectAction.Action = job.ToObject<AdaptiveExecuteAction>();
                    break;
                case AdaptiveShowCardAction.TypeName:
                    selectAction.Action = job.ToObject<AdaptiveShowCardAction>();
                    break;
                default:
                    selectAction.Action = job.ToObject<AdaptiveUnknownAction>();
                    break;
            }

            return selectAction;
        }

        public override void WriteJson(JsonWriter writer, AdaptiveSelectAction value, JsonSerializer serializer)
        {
            serializer.Serialize(writer, value.Action);
        }
    }
}
