package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import static org.junit.Assert.*;

public class ChoiceSetInputPropertiesTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String dateInputNoDefaultValues =
            "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
            "\"errorMessage\":\"Error message\"," +
            "\"id\":\"id\"," +
            "\"isMultiSelect\":true," +
            "\"label\":\"Input label\"," +
            "\"style\":\"Compact\"," +
            "\"type\":\"Input.ChoiceSet\"," +
            "\"value\":\"Sample value\"," +
            "\"wrap\":true}\n";

        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetErrorMessage("Error message");
        choiceSetInput.SetLabel("Input label");
        choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Compact);
        choiceSetInput.SetIsMultiSelect(true);
        choiceSetInput.SetValue("Sample value");
        choiceSetInput.SetWrap(true);

        Assert.assertEquals(dateInputNoDefaultValues, choiceSetInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String choiceSetInputNoDefaultValues =
            "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
            "\"errorMessage\":\"Error message\"," +
            "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
            "\"height\":\"Stretch\"," +
            "\"id\":\"id\"," +
            "\"isMultiSelect\":true," +
            "\"isVisible\":false," +
            "\"label\":\"Input label\"," +
            "\"separator\":true," +
            "\"spacing\":\"medium\"," +
            "\"style\":\"Expanded\"," +
            "\"type\":\"Input.ChoiceSet\"," +
            "\"value\":\"Sample value\"," +
            "\"wrap\":true}\n";

        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Expanded);
        choiceSetInput.SetErrorMessage("Error message");
        choiceSetInput.SetFallbackType(FallbackType.Content);
        choiceSetInput.SetFallbackContent(TestUtil.createMockImage());
        choiceSetInput.SetHeight(HeightType.Stretch);
        choiceSetInput.SetIsMultiSelect(true);
        choiceSetInput.SetIsVisible(false);
        choiceSetInput.SetLabel("Input label");
        choiceSetInput.SetSeparator(true);
        choiceSetInput.SetSpacing(Spacing.Medium);
        choiceSetInput.SetValue("Sample value");
        choiceSetInput.SetWrap(true);

        Assert.assertEquals(choiceSetInputNoDefaultValues, choiceSetInput.Serialize());
    }

    @Test
    public void ChoiceSetStyleTest() throws Exception
    {
        {
            final String inputChoiceSetDefaultValue =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                    "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            Assert.assertEquals(inputChoiceSetDefaultValue, choiceSetInput.Serialize());

            choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Compact);
            Assert.assertEquals(inputChoiceSetDefaultValue, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetDefaultValue), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedChoiceSetInput.GetValue());
        }

        {
            final String inputChoiceSetExpandedStyle =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                "\"id\":\"id\",\"style\":\"Expanded\",\"type\":\"Input.ChoiceSet\"}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Expanded);
            Assert.assertEquals(inputChoiceSetExpandedStyle, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetExpandedStyle), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(ChoiceSetStyle.Expanded, parsedChoiceSetInput.GetChoiceSetStyle());
        }
    }

    @Test
    public void IsMultiSelectTest() throws Exception
    {
        ChoiceSetInputCommand<Boolean> c = new ChoiceSetInputCommand<Boolean>() {
            @Override
            public Boolean get(ChoiceSetInput element) { return element.GetIsMultiSelect(); }

            @Override
            public void set(Boolean value, ChoiceSetInput element) { element.SetIsMultiSelect(value); }
        };

        final String inputChoiceSetIsMultiSelectJson =
            "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                "\"id\":\"id\",\"isMultiSelect\":%b,\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";
        TestUtil.executeBooleanTests(c, c_defaultInputChoiceSet, inputChoiceSetIsMultiSelectJson, false);
    }

    @Test
    public void ValueTest() throws Exception
    {
        ChoiceSetInputCommand<String> c = new ChoiceSetInputCommand<String>() {
            @Override
            public String get(ChoiceSetInput element) { return element.GetValue(); }

            @Override
            public void set(String value, ChoiceSetInput element) { element.SetValue(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputChoiceSet, "");

        final String inputChoiceSetValueTemplate =
            "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\",\"value\":\"%s\"}\n";
        TestUtil.executeTests(c, inputChoiceSetValueTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void WrapTest() throws Exception
    {
        ChoiceSetInputCommand<Boolean> c = new ChoiceSetInputCommand<Boolean>() {
            @Override
            public Boolean get(ChoiceSetInput element) { return element.GetWrap(); }

            @Override
            public void set(Boolean value, ChoiceSetInput element) { element.SetWrap(value); }
        };

        final String inputChoiceSetWrapJson =
            "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\",\"wrap\":%b}\n";
        TestUtil.executeBooleanTests(c, c_defaultInputChoiceSet, inputChoiceSetWrapJson, false);
    }

    @Test
    public void LabelTest() throws Exception
    {
        ChoiceSetInputCommand<String> c = new ChoiceSetInputCommand<String>() {
            @Override
            public String get(ChoiceSetInput element) { return element.GetLabel(); }

            @Override
            public void set(String value, ChoiceSetInput element) { element.SetLabel(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputChoiceSet, "");

        final String inputToggleLabelTemplate = "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                                                "\"id\":\"id\",\"label\":\"%s\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";
        TestUtil.executeTests(c, inputToggleLabelTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void ErrorMessageTest() throws Exception
    {
        ChoiceSetInputCommand<String> c = new ChoiceSetInputCommand<String>() {
            @Override
            public String get(ChoiceSetInput element) { return element.GetErrorMessage(); }

            @Override
            public void set(String value, ChoiceSetInput element) { element.SetErrorMessage(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputChoiceSet, "");

        final String inputChoiceSetErrorMessageTemplate = "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                                                        "\"errorMessage\":\"%s\",\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";

        TestUtil.executeTests(c, inputChoiceSetErrorMessageTemplate, TestUtil.c_regularStringTestCases);
    }

    private abstract class ChoiceSetInputCommand<E> implements TestUtil.Command<ChoiceSetInput, E>
    {
        @Override
        public ChoiceSetInput getMockObject()
        {
            return TestUtil.createMockChoiceSetInput();
        }

        @Override
        public ChoiceSetInput castTo(BaseCardElement element) {
            return TestUtil.castToChoiceSetInput(element);
        }
    }

    private final String c_defaultInputChoiceSet = "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                                                    "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";
}
