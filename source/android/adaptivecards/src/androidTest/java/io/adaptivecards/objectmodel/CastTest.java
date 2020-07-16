package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import io.adaptivecards.renderer.Util;

public class CastTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void ConversionTest() throws Exception
    {
        // Create an element and convert it from TextInput to BaseCardElement
        TextInput input = TestUtil.createMockTextInput();

        BaseInputElement baseInputElement = Util.castTo(input, BaseInputElement.class);
        Assert.assertNotNull(baseInputElement);

        BaseCardElement baseCardElement = Util.castTo(baseInputElement, BaseCardElement.class);
        Assert.assertNotNull(baseCardElement);
    }

    @Test
    public void ConversionTestSpecialization() throws Exception
    {
        ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(TestUtil.createMockTextInput().Serialize()), "1.0");

        BaseCardElementVector elementVector = result.GetAdaptiveCard().GetBody();
        Assert.assertEquals(1, elementVector.size());
        BaseCardElement baseCardElement = elementVector.get(0);

        // Do the conversion from BaseCardElement to TextInput
        BaseInputElement baseInputElement = Util.castTo(baseCardElement, BaseInputElement.class);
        Assert.assertNotNull(baseInputElement);

        TextInput input = Util.castTo(baseCardElement, TextInput.class);
        Assert.assertNotNull(input);

        TextInput input2 = Util.castTo(baseInputElement, TextInput.class);
        Assert.assertNotNull(input2);
    }

    @Test
    public void CustomActionCastTest() throws Exception
    {
        AdaptiveCard card = new AdaptiveCard();
        card.GetBody().add(TestUtil.createMockTextBlock());
        card.GetActions().add(TestUtil.createMockSubmitAction());
        card.GetActions().add(new CustomAction(ActionType.Custom));
        card.GetActions().add(new AnotherCustomAction(ActionType.Custom));

        int actionCount = card.GetActions().size();
        for (int i = 0; i < actionCount * 100000; i += actionCount)
        {
            BaseActionElement submitActionElement = card.GetActions().get(0);
            SubmitAction submitAction = Util.castTo(submitActionElement, SubmitAction.class);
            Assert.assertNotNull(submitAction);

            BaseActionElement actionElement = card.GetActions().get(1);
            BaseActionElement baseActionElement = actionElement.findImplObj();
            CustomAction customAction = (CustomAction)baseActionElement;
            Assert.assertNotNull(customAction);

            BaseActionElement anotherActionElement = card.GetActions().get(2);
            BaseActionElement anotherBaseActionElement = anotherActionElement.findImplObj();
            AnotherCustomAction anotherCustomAction = (AnotherCustomAction)anotherBaseActionElement;
            Assert.assertNotNull(anotherCustomAction);
        }
    }

    @Test
    public void CustomActionParseCastTest() throws Exception
    {
        final String testString = "{\"type\":\"AdaptiveCard\", \"version\":\"1.0\", " +
            "\"body\":[{\"type\":\"TextBlock\", \"text\":\"filler\"}], " +
            "\"actions\":[{\"type\":\"Action.Submit\", \"title\":\"Submit\"}, {\"type\":\"" + CustomAction.CustomActionId + "\"}, {\"type\":\"" + AnotherCustomAction.CustomActionId + "\"}]}";

        ActionParserRegistration actionParserRegistration = new ActionParserRegistration();
        actionParserRegistration.AddParser(CustomAction.CustomActionId, new CustomActionParser());
        actionParserRegistration.AddParser(AnotherCustomAction.CustomActionId, new AnotherCustomActionParser());

        ParseContext parseContext = new ParseContext(null, actionParserRegistration);

        ParseResult result = AdaptiveCard.DeserializeFromString(testString, "1.2",  parseContext);
        AdaptiveCard card = result.GetAdaptiveCard();

        int actionCount = card.GetActions().size();
        for (int i = 0; i < actionCount * 100000; i += actionCount)
        {
            BaseActionElement submitActionElement = card.GetActions().get(0);
            SubmitAction submitAction = Util.castTo(submitActionElement, SubmitAction.class);
            Assert.assertNotNull(submitAction);

            BaseActionElement actionElement = card.GetActions().get(1);
            BaseActionElement baseActionElement = actionElement.findImplObj();
            CustomAction customAction = (CustomAction)baseActionElement;
            Assert.assertNotNull(customAction);

            BaseActionElement anotherActionElement = card.GetActions().get(2);
            BaseActionElement anotherBaseActionElement = anotherActionElement.findImplObj();
            AnotherCustomAction anotherCustomAction = (AnotherCustomAction)anotherBaseActionElement;
            Assert.assertNotNull(anotherCustomAction);
        }
    }

    class CustomAction extends BaseActionElement
    {
        public CustomAction(ActionType type) {
            super(type);
        }

        @Override
        public String GetElementTypeString()
        {
            return CustomActionId;
        }

        public static final String CustomActionId = "Action.Custom";
    }

    class CustomActionParser extends ActionElementParser
    {
        @Override
        public BaseActionElement Deserialize(ParseContext context, JsonValue value)
        {
            return new CustomAction(ActionType.Custom);
        }

        @Override
        public BaseActionElement DeserializeFromString(ParseContext context, String value)
        {
            return new CustomAction(ActionType.Custom);
        }
    }

    class AnotherCustomAction extends BaseActionElement
    {
        public AnotherCustomAction(ActionType type) {
            super(type);
        }

        @Override
        public String GetElementTypeString()
        {
            return CustomActionId;
        }

        public static final String CustomActionId = "Action.AnotherCustom";
    }

    class AnotherCustomActionParser extends ActionElementParser
    {
        @Override
        public BaseActionElement Deserialize(ParseContext context, JsonValue value)
        {
            return new AnotherCustomAction(ActionType.Custom);
        }

        @Override
        public BaseActionElement DeserializeFromString(ParseContext context, String value)
        {
            return new AnotherCustomAction(ActionType.Custom);
        }
    }

}
