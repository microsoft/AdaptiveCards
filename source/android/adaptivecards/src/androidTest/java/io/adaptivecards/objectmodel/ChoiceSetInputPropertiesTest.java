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
            "\"id\":\"id\"," +
            "\"isMultiSelect\":true," +
            "\"style\":\"Compact\"," +
            "\"type\":\"Input.ChoiceSet\"," +
            "\"value\":\"Sample value\"," +
            "\"wrap\":true}\n";

        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
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
            "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
            "\"height\":\"Stretch\"," +
            "\"id\":\"id\"," +
            "\"isMultiSelect\":true," +
            "\"isVisible\":false," +
            "\"separator\":true," +
            "\"spacing\":\"medium\"," +
            "\"style\":\"Expanded\"," +
            "\"type\":\"Input.ChoiceSet\"," +
            "\"value\":\"Sample value\"," +
            "\"wrap\":true}\n";

        ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
        choiceSetInput.SetChoiceSetStyle(ChoiceSetStyle.Expanded);
        choiceSetInput.SetFallbackType(FallbackType.Content);
        choiceSetInput.SetFallbackContent(TestUtil.createMockImage());
        choiceSetInput.SetHeight(HeightType.Stretch);
        choiceSetInput.SetIsMultiSelect(true);
        choiceSetInput.SetIsVisible(false);
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
        {
            final String inputChoiceSetDefaultWrap =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                    "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            Assert.assertEquals(inputChoiceSetDefaultWrap, choiceSetInput.Serialize());

            choiceSetInput.SetIsMultiSelect(false);
            Assert.assertEquals(inputChoiceSetDefaultWrap, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetDefaultWrap), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedChoiceSetInput.GetIsMultiSelect());
        }

        {
            final String inputChoiceSetWrapJson =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                    "\"id\":\"id\",\"isMultiSelect\":true,\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            choiceSetInput.SetIsMultiSelect(true);
            Assert.assertEquals(inputChoiceSetWrapJson, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetWrapJson), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedChoiceSetInput.GetIsMultiSelect());
        }
    }

    @Test
    public void ValueTest() throws Exception
    {
        {
            final String inputChoiceSetDefaultValue =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            Assert.assertEquals(inputChoiceSetDefaultValue, choiceSetInput.Serialize());

            choiceSetInput.SetValue("");
            Assert.assertEquals(inputChoiceSetDefaultValue, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetDefaultValue), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedChoiceSetInput.GetValue());
        }

        {
            final String inputChoiceSetValueTemplate =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                    "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\",\"value\":\"%s\"}\n";

            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputChoiceSetValueJson = String.format(inputChoiceSetValueTemplate, tests[i]);

                ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
                choiceSetInput.SetValue(tests[i]);
                Assert.assertEquals(inputChoiceSetValueJson, choiceSetInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetValueJson), "1.0");
                ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedChoiceSetInput.GetValue());
            }
        }
    }

    @Test
    public void WrapTest() throws Exception
    {
        {
            final String inputChoiceSetDefaultWrap =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                    "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\"}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            Assert.assertEquals(inputChoiceSetDefaultWrap, choiceSetInput.Serialize());

            choiceSetInput.SetWrap(false);
            Assert.assertEquals(inputChoiceSetDefaultWrap, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetDefaultWrap), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedChoiceSetInput.GetWrap());
        }

        {
            final String inputChoiceSetWrapJson =
                "{\"choices\":[{\"title\":\"sample title\",\"value\":\"sample value\"}]," +
                    "\"id\":\"id\",\"style\":\"Compact\",\"type\":\"Input.ChoiceSet\",\"wrap\":true}\n";

            ChoiceSetInput choiceSetInput = TestUtil.createMockChoiceSetInput();
            choiceSetInput.SetWrap(true);
            Assert.assertEquals(inputChoiceSetWrapJson, choiceSetInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputChoiceSetWrapJson), "1.0");
            ChoiceSetInput parsedChoiceSetInput = TestUtil.castToChoiceSetInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedChoiceSetInput.GetWrap());
        }
    }
}
