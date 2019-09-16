package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import io.adaptivecards.objectmodel.ActionElementParser;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;

public class CustomGreenActionParser extends ActionElementParser
{
    @Override
    public BaseActionElement Deserialize(ParseContext context, JsonValue value)
    {
        CustomGreenActionElement element = new CustomGreenActionElement(ActionType.Custom);
        element.SetElementTypeString(CustomGreenActionElement.CustomActionId);
        element.SetId("greenActionDeserialize");
        return element;
    }

    @Override
    public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
    {
        CustomGreenActionElement element = new CustomGreenActionElement(ActionType.Custom);
        element.SetElementTypeString(CustomGreenActionElement.CustomActionId);
        element.SetId("greenActionDeserialize");
        return element;
    }
}
