using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using AdaptiveCards.Rendering.Xamarin.Android.ObjectModel;
using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using Org.Json;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample.Custom
{
    class CustomActionParser : ActionElementParser
    {

        public override BaseActionElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomAction customAction = new CustomAction(ActionType.Custom);
            customAction.ElementTypeString = "CustomAction";
            customAction.Id = "CustomActionDeserialize";

            try
            {
                JSONObject jSONObject = new JSONObject(value.String);
                customAction.SomeData = jSONObject.GetString("someData");
                // customElement.SomeData = "A";
            }
            catch (Exception e) { }

            return customAction;
        }

        public override BaseActionElement DeserializeFromString(ParseContext context, string value)
        {
            CustomAction customAction = new CustomAction(ActionType.Custom);
            customAction.ElementTypeString = "CustomAction";
            customAction.Id = "CustomActionDeserialize";

            try
            {
                JSONObject jSONObject = new JSONObject(value);
                customAction.SomeData = jSONObject.GetString("someData");
            }
            catch (Exception e) { }

            return customAction;
        }


    }
}
