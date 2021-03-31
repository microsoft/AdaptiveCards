package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import org.json.JSONException;
import org.json.JSONObject;

import io.adaptivecards.objectmodel.ActionElementParser;
import io.adaptivecards.objectmodel.ActionElementParserWrapper;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseElement;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.objectmodel.SubmitActionParser;
import io.adaptivecards.renderer.Util;

public class CustomRedActionParser extends ActionElementParser
{
    @Override
    public BaseActionElement Deserialize(ParseContext context, JsonValue value)
    {
        CustomRedActionElement element = new CustomRedActionElement(ActionType.Custom);
        Util.deserializeBaseActionProperties(context, value, element);

        element.SetElementTypeString(CustomRedActionElement.CustomActionId);
        element.SetId("backwardActionDeserialize");
        String val = value.getString();
        try {
            JSONObject obj = new JSONObject(val);
            element.setBackwardString(obj.getString("backwardString"));
        } catch (JSONException e) {
            e.printStackTrace();
            element.setBackwardString("deliaF");
        }
        return element;
    }

    @Override
    public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
    {
        CustomRedActionElement element = new CustomRedActionElement(ActionType.Custom);
        Util.deserializeBaseActionPropertiesFromString(context, jsonString, element);

        element.SetElementTypeString(CustomRedActionElement.CustomActionId);
        element.SetId("backwardActionDeserialize");
        try {
            JSONObject obj = new JSONObject(jsonString);
            element.setBackwardString(obj.getString("backwardString"));
        } catch (JSONException e) {
            e.printStackTrace();
            element.setBackwardString("deliaF");
        }
        return element;
    }
}
