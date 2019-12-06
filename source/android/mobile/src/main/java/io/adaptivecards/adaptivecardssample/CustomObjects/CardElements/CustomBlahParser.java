package io.adaptivecards.adaptivecardssample.CustomObjects.CardElements;

import org.json.JSONException;
import org.json.JSONObject;

import io.adaptivecards.adaptivecardssample.MainActivityAdaptiveCardsSample;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseCardElementParser;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;

public class CustomBlahParser extends BaseCardElementParser
{
    @Override
    public BaseCardElement Deserialize(ParseContext context, JsonValue value)
    {
        CustomCardElement element = new CustomCardElement(CardElementType.Custom);
        element.SetElementTypeString("blah");
        element.SetId("BlahDeserialize");
        String val = value.getString();
        try
        {
            JSONObject obj = new JSONObject(val);
            element.setSecretString(obj.getString("secret"));
        }
        catch (JSONException e)
        {
            e.printStackTrace();
            element.setSecretString("Failed");
        }
        return element;
    }

    @Override
    public BaseCardElement DeserializeFromString(ParseContext context, String jsonString)
    {
        CustomCardElement element = new CustomCardElement(CardElementType.Custom);
        element.SetElementTypeString("blah");
        element.SetId("BlahDeserialize");
        try
        {
            JSONObject obj = new JSONObject(jsonString);
            element.setSecretString(obj.getString("secret"));
        }
        catch (JSONException e)
        {
            e.printStackTrace();
            element.setSecretString("Failed");
        }
        return element;
    }
}
