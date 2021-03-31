package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import io.adaptivecards.objectmodel.ActionElementParser;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.renderer.Util;

public class CustomGreenActionParser extends ActionElementParser
{
    @Override
    public BaseActionElement Deserialize(ParseContext context, JsonValue value)
    {
        CustomGreenActionElement element = new CustomGreenActionElement(ActionType.Custom);
        Util.deserializeBaseActionProperties(context, value, element);

        element.SetElementTypeString(CustomGreenActionElement.CustomActionId);
        element.SetId("greenActionDeserialize");
        return element;
    }

    @Override
    public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
    {
        CustomGreenActionElement element = new CustomGreenActionElement(ActionType.Custom);
        Util.deserializeBaseActionPropertiesFromString(context, jsonString, element);

        element.SetElementTypeString(CustomGreenActionElement.CustomActionId);
        element.SetId("greenActionDeserialize");
        return element;
    }
}
