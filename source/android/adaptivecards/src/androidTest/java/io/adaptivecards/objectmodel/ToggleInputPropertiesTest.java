package io.adaptivecards.objectmodel;

import junit.framework.Assert;

import org.junit.Test;

import static org.junit.Assert.*;

public class ToggleInputPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String dateInputNoDefaultValues =
            "{\"id\":\"id\"," +
                "\"title\":\"Sample title\"," +
                "\"type\":\"Input.Toggle\"," +
                "\"value\":\"Sample value\"," +
                "\"valueOff\":\"Sample value off\"," +
                "\"valueOn\":\"Sample value on\"," +
                "\"wrap\":true}\n";

        ToggleInput toggleInput = TestUtil.createMockToggleInput();
        toggleInput.SetTitle("Sample title");
        toggleInput.SetValue("Sample value");
        toggleInput.SetValueOff("Sample value off");
        toggleInput.SetValueOn("Sample value on");
        toggleInput.SetWrap(true);

        Assert.assertEquals(dateInputNoDefaultValues, toggleInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String dateInputNoDefaultValues =
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"title\":\"Sample title\"," +
                "\"type\":\"Input.Toggle\"," +
                "\"value\":\"Sample value\"," +
                "\"valueOff\":\"Sample value off\"," +
                "\"valueOn\":\"Sample value on\"," +
                "\"wrap\":true}\n";

        ToggleInput toggleInput = TestUtil.createMockToggleInput();
        toggleInput.SetFallbackType(FallbackType.Content);
        toggleInput.SetFallbackContent(TestUtil.createMockImage());
        toggleInput.SetHeight(HeightType.Stretch);
        toggleInput.SetIsVisible(false);
        toggleInput.SetTitle("Sample title");
        toggleInput.SetSeparator(true);
        toggleInput.SetSpacing(Spacing.Medium);
        toggleInput.SetValue("Sample value");
        toggleInput.SetValueOff("Sample value off");
        toggleInput.SetValueOn("Sample value on");
        toggleInput.SetWrap(true);

        Assert.assertEquals(dateInputNoDefaultValues, toggleInput.Serialize());
    }

    @Test
    public void TitleTest() throws Exception
    {
        {
            final String inputToggleDefaultTitle = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";

            ToggleInput toggleInput = TestUtil.createMockToggleInput();
            Assert.assertEquals(inputToggleDefaultTitle, toggleInput.Serialize());

            toggleInput.SetTitle("");
            Assert.assertEquals(inputToggleDefaultTitle, toggleInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleDefaultTitle), "1.0");
            ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedToggleInput.GetTitle());
        }

        {
            final String inputToggleTitleTemplate = "{\"id\":\"id\",\"title\":\"%s\",\"type\":\"Input.Toggle\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputToggleTitleJson = String.format(inputToggleTitleTemplate, tests[i]);

                ToggleInput toggleInput = TestUtil.createMockToggleInput();
                toggleInput.SetTitle(tests[i]);
                Assert.assertEquals(inputToggleTitleJson, toggleInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleTitleJson), "1.0");
                ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedToggleInput.GetTitle());
            }
        }
    }

    @Test
    public void ValueTest() throws Exception
    {
        {
            final String inputToggleDefaultValue = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";

            ToggleInput toggleInput = TestUtil.createMockToggleInput();
            Assert.assertEquals(inputToggleDefaultValue, toggleInput.Serialize());

            toggleInput.SetValue("");
            Assert.assertEquals(inputToggleDefaultValue, toggleInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleDefaultValue), "1.0");
            ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedToggleInput.GetValue());
        }

        {
            final String inputToggleValueTemplate = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"value\":\"%s\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputToggleValueJson = String.format(inputToggleValueTemplate, tests[i]);

                ToggleInput toggleInput = TestUtil.createMockToggleInput();
                toggleInput.SetValue(tests[i]);
                Assert.assertEquals(inputToggleValueJson, toggleInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleValueJson), "1.0");
                ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedToggleInput.GetValue());
            }
        }
    }

    @Test
    public void ValueOffTest() throws Exception
    {
        {
            final String inputToggleDefaultValue = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";

            ToggleInput toggleInput = TestUtil.createMockToggleInput();
            Assert.assertEquals(inputToggleDefaultValue, toggleInput.Serialize());

            toggleInput.SetValueOff("false");
            Assert.assertEquals(inputToggleDefaultValue, toggleInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleDefaultValue), "1.0");
            ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("false", parsedToggleInput.GetValueOff());
        }

        {
            final String inputToggleValueTemplate = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"valueOff\":\"%s\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputToggleValueOffJson = String.format(inputToggleValueTemplate, tests[i]);

                ToggleInput toggleInput = TestUtil.createMockToggleInput();
                toggleInput.SetValueOff(tests[i]);
                Assert.assertEquals(inputToggleValueOffJson, toggleInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleValueOffJson), "1.0");
                ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedToggleInput.GetValueOff());
            }
        }
    }

    @Test
    public void ValueOnTest() throws Exception
    {
        {
            final String inputToggleDefaultValue = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";

            ToggleInput toggleInput = TestUtil.createMockToggleInput();
            Assert.assertEquals(inputToggleDefaultValue, toggleInput.Serialize());

            toggleInput.SetValueOn("true");
            Assert.assertEquals(inputToggleDefaultValue, toggleInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleDefaultValue), "1.0");
            ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("true", parsedToggleInput.GetValueOn());
        }

        {
            final String inputToggleValueTemplate = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"valueOn\":\"%s\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputToggleValueOnJson = String.format(inputToggleValueTemplate, tests[i]);

                ToggleInput toggleInput = TestUtil.createMockToggleInput();
                toggleInput.SetValueOn(tests[i]);
                Assert.assertEquals(inputToggleValueOnJson, toggleInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleValueOnJson), "1.0");
                ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedToggleInput.GetValueOn());
            }
        }
    }

    @Test
    public void WrapTest() throws Exception
    {
        {
            final String inputToggleDefaultWrap = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";

            ToggleInput toggleInput = TestUtil.createMockToggleInput();
            Assert.assertEquals(inputToggleDefaultWrap, toggleInput.Serialize());

            toggleInput.SetWrap(false);
            Assert.assertEquals(inputToggleDefaultWrap, toggleInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleDefaultWrap), "1.0");
            ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedToggleInput.GetWrap());
        }

        {
            final String inputToggleWrapJson = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"wrap\":true}\n";

            ToggleInput toggleInput = TestUtil.createMockToggleInput();
            toggleInput.SetWrap(true);
            Assert.assertEquals(inputToggleWrapJson, toggleInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputToggleWrapJson), "1.0");
            ToggleInput parsedToggleInput = TestUtil.castToToggleInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedToggleInput.GetWrap());
        }
    }

}
