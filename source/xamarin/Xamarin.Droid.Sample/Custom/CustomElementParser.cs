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
using Newtonsoft.Json;
using Org.Json;

namespace AdaptiveCards.Rendering.Xamarin.Android.Sample.Custom
{
    class CustomElementParser : BaseCardElementParser
    {

        public override BaseCardElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomElement customElement = new CustomElement(CardElementType.Custom);
            customElement.ElementTypeString = "CustomElement";
            customElement.Id = "CustomElementDeserialize";

            try
            {
                JSONObject jSONObject = new JSONObject(value.String);
                customElement.SomeData = jSONObject.GetString("someData");
                // customElement.SomeData = "A";
            }
            catch (Exception e) { }

            return customElement;
        }

        public override BaseCardElement DeserializeFromString(ParseContext context, string value)
        {
            CustomElement customElement = new CustomElement(CardElementType.Custom);
            customElement.ElementTypeString = "CustomElement";
            customElement.Id = "CustomElementDeserialize";

            try
            {
                JSONObject jSONObject = new JSONObject(value);
                customElement.SomeData = jSONObject.GetString("someData");
            }
            catch (Exception e) { }

            return customElement;
        }

    }
}
