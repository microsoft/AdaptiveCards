package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;
import org.w3c.dom.Text;

import java.util.ArrayList;

import static org.junit.Assert.*;

public class TextInputPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String textInputNoDefaultValues =
            "{\"id\":\"id\"," +
                "\"inlineAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"isMultiline\":true," +
                "\"maxLength\":10," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"style\":\"Email\"," +
                "\"type\":\"Input.Text\"," +
                "\"value\":\"samplevalue@contoso.com\"}\n";

        TextInput textInput = TestUtil.createMockTextInput();
        textInput.SetInlineAction(TestUtil.createSampleOpenUrlAction());
        textInput.SetIsMultiline(true);
        textInput.SetMaxLength(10);
        textInput.SetPlaceholder("Sample placeholder");
        textInput.SetTextInputStyle(TextInputStyle.Email);
        textInput.SetValue("samplevalue@contoso.com");

        Assert.assertEquals(textInputNoDefaultValues, textInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String textInputNoDefaultValues =
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"inlineAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"isMultiline\":true," +
                "\"isVisible\":false," +
                "\"maxLength\":10," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"style\":\"Email\"," +
                "\"type\":\"Input.Text\"," +
                "\"value\":\"samplevalue@contoso.com\"}\n";

        TextInput textInput = TestUtil.createMockTextInput();
        textInput.SetFallbackType(FallbackType.Content);
        textInput.SetFallbackContent(TestUtil.createMockImage());
        textInput.SetHeight(HeightType.Stretch);
        textInput.SetInlineAction(TestUtil.createSampleOpenUrlAction());
        textInput.SetIsMultiline(true);
        textInput.SetIsVisible(false);
        textInput.SetMaxLength(10);
        textInput.SetPlaceholder("Sample placeholder");
        textInput.SetSeparator(true);
        textInput.SetSpacing(Spacing.Medium);
        textInput.SetTextInputStyle(TextInputStyle.Email);
        textInput.SetValue("samplevalue@contoso.com");

        Assert.assertEquals(textInputNoDefaultValues, textInput.Serialize());
    }

    @Test
    public void InlineActionTest() throws Exception
    {
        {
            final String inputTextDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetInlineAction(null);
            Assert.assertEquals(inputTextDefaultPlaceholder, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultPlaceholder), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(null, parsedTextInput.GetInlineAction());
        }

        {
            final String inputTextInlineOpenUrl =
                "{\"id\":\"id\"," +
                "\"inlineAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetInlineAction(TestUtil.createSampleOpenUrlAction());
            Assert.assertEquals(inputTextInlineOpenUrl, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextInlineOpenUrl), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));

            Assert.assertNotNull(parsedTextInput.GetInlineAction());
            OpenUrlAction openUrlAction = TestUtil.castToOpenUrlAction(parsedTextInput.GetInlineAction());
            Assert.assertEquals("http://", openUrlAction.GetUrl());
        }

        {
            final String inputTextInlineSubmitAction =
                "{\"id\":\"id\"," +
                    "\"inlineAction\":{\"data\":{\"data\":\"Some data\"},\"type\":\"Action.Submit\"}," +
                    "\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetInlineAction(TestUtil.createSampleSubmitAction());
            Assert.assertEquals(inputTextInlineSubmitAction, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextInlineSubmitAction), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertNotNull(parsedTextInput.GetInlineAction());

            SubmitAction submitAction = TestUtil.castToSubmitAction(parsedTextInput.GetInlineAction());
            Assert.assertEquals("{\"data\":\"Some data\"}\n", submitAction.GetDataJson());
        }

        {
            final String inputTextDefaultPlaceholder =
                "{\"id\":\"id\"," +
                    "\"inlineAction\":" +
                        "{\"targetElements\":[" +
                        "\"id1\"," +
                        "{\"elementId\":\"id2\",\"isVisible\":true}," +
                        "{\"elementId\":\"id3\",\"isVisible\":false}]," +
                        "\"type\":\"Action.ToggleVisibility\"}," +
                    "\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetInlineAction(TestUtil.createSampleToggleVisibilityAction());
            Assert.assertEquals(inputTextDefaultPlaceholder, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultPlaceholder), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertNotNull(parsedTextInput.GetInlineAction());

            ToggleVisibilityAction toggleVisibilityAction = TestUtil.castToToggleVisibilityAction(parsedTextInput.GetInlineAction());
            ToggleVisibilityTargetVector targets = toggleVisibilityAction.GetTargetElements();
            Assert.assertEquals(3, targets.size());
            Assert.assertEquals("id1", targets.get(0).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleToggle, targets.get(0).GetIsVisible());
            Assert.assertEquals("id2", targets.get(1).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleTrue, targets.get(1).GetIsVisible());
            Assert.assertEquals("id3", targets.get(2).GetElementId());
            Assert.assertEquals(IsVisible.IsVisibleFalse, targets.get(2).GetIsVisible());
        }

    }

    @Test
    public void MultilineTest() throws Exception
    {
        {
            final String inputTextNoMultiline = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";
            TextInput textInput = TestUtil.createMockTextInput();
            Assert.assertEquals(inputTextNoMultiline, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextNoMultiline), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(false, parsedTextInput.GetIsMultiline());
        }

        {
            final String inputTextMultiline =
                "{\"id\":\"id\",\"isMultiline\":true,\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetIsMultiline(true);
            Assert.assertEquals(inputTextMultiline, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextMultiline), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(true, parsedTextInput.GetIsMultiline());
        }
    }

    @Test
    public void MaxLengthTest() throws Exception
    {
        {
            final String inputTextDefaultMaxLength = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetMaxLength(0);
            Assert.assertEquals(inputTextDefaultMaxLength, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultMaxLength), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(0, parsedTextInput.GetMaxLength());
        }

        {
            final String inputTextMaxLengthTemplate =
                "{\"id\":\"id\",\"maxLength\":%d,\"type\":\"Input.Text\"}\n";
            long[] tests = {1, 5, 10, 25, 50};

            for (int i = 0; i < tests.length; ++i)
            {
                String maxLengthJson = String.format(inputTextMaxLengthTemplate, tests[i]);

                TextInput textInput = TestUtil.createMockTextInput();
                textInput.SetMaxLength(tests[i]);
                Assert.assertEquals(maxLengthJson, textInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxLengthJson), "1.0");
                TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTextInput.GetMaxLength());
            }
        }

    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        {
            final String inputTextDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetPlaceholder("");
            Assert.assertEquals(inputTextDefaultPlaceholder, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultPlaceholder), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTextInput.GetPlaceholder());
        }

        {
            final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Text\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTextPlaceholderJson = String.format(inputTextPlaceholderTemplate, tests[i]);

                TextInput textInput = TestUtil.createMockTextInput();
                textInput.SetPlaceholder(tests[i]);
                Assert.assertEquals(inputTextPlaceholderJson, textInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextPlaceholderJson), "1.0");
                TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTextInput.GetPlaceholder());
            }
        }
    }

    @Test
    public void TextInputStyleTest() throws Exception
    {
        {
            final String inputTextDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetTextInputStyle(TextInputStyle.Text);
            Assert.assertEquals(inputTextDefaultPlaceholder, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultPlaceholder), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(TextInputStyle.Text, parsedTextInput.GetTextInputStyle());
        }

        {
            final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"style\":\"%s\",\"type\":\"Input.Text\"}\n";

            ArrayList<Pair<TextInputStyle, String>> tests = new ArrayList<>();
            tests.add(new Pair<>(TextInputStyle.Tel, String.format(inputTextPlaceholderTemplate, "Tel")));
            tests.add(new Pair<>(TextInputStyle.Url, String.format(inputTextPlaceholderTemplate, "Url")));
            tests.add(new Pair<>(TextInputStyle.Email, String.format(inputTextPlaceholderTemplate, "Email")));

            for (Pair<TextInputStyle, String> test : tests)
            {
                TextInput textInput = TestUtil.createMockTextInput();
                textInput.SetTextInputStyle(test.first);
                Assert.assertEquals(test.second, textInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(test.second), "1.0");
                TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(test.first, parsedTextInput.GetTextInputStyle());
            }
        }
    }

    @Test
    public void ValueTest() throws Exception
    {
        {
            final String inputTextDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetValue("");
            Assert.assertEquals(inputTextDefaultPlaceholder, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultPlaceholder), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTextInput.GetValue());
        }

        {
            final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"type\":\"Input.Text\",\"value\":\"%s\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTextPlaceholderJson = String.format(inputTextPlaceholderTemplate, tests[i]);

                TextInput textInput = TestUtil.createMockTextInput();
                textInput.SetValue(tests[i]);
                Assert.assertEquals(inputTextPlaceholderJson, textInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextPlaceholderJson), "1.0");
                TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTextInput.GetValue());
            }
        }
    }


    @Test
    public void LabelTest() throws Exception
    {
        {
            final String inputTextDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";

            TextInput textInput = TestUtil.createMockTextInput();
            textInput.SetLabel("");
            Assert.assertEquals(inputTextDefaultPlaceholder, textInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextDefaultPlaceholder), "1.0");
            TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedTextInput.GetLabel());
        }

        {
            final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"label\":\"%s\",\"type\":\"Input.Text\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTextPlaceholderJson = String.format(inputTextPlaceholderTemplate, tests[i]);

                TextInput textInput = TestUtil.createMockTextInput();
                textInput.SetLabel(tests[i]);
                Assert.assertEquals(inputTextPlaceholderJson, textInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextPlaceholderJson), "1.0");
                TextInput parsedTextInput = TestUtil.castToTextInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedTextInput.GetLabel());
            }
        }
    }

}
