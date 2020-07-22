package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;
import org.w3c.dom.Text;

import java.lang.reflect.Array;
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
            "{\"errorMessage\":\"Error message\"," +
                "\"id\":\"id\"," +
                "\"inlineAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"isMultiline\":true," +
                "\"label\":\"Input label\"," +
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
        textInput.SetLabel("Input label");
        textInput.SetErrorMessage("Error message");

        Assert.assertEquals(textInputNoDefaultValues, textInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String textInputNoDefaultValues =
            "{\"errorMessage\":\"Error message\"," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"inlineAction\":{\"type\":\"Action.OpenUrl\",\"url\":\"http://\"}," +
                "\"isMultiline\":true," +
                "\"isVisible\":false," +
                "\"label\":\"Input label\"," +
                "\"maxLength\":10," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"style\":\"Email\"," +
                "\"type\":\"Input.Text\"," +
                "\"value\":\"samplevalue@contoso.com\"}\n";

        TextInput textInput = TestUtil.createMockTextInput();
        textInput.SetErrorMessage("Error message");
        textInput.SetFallbackType(FallbackType.Content);
        textInput.SetFallbackContent(TestUtil.createMockImage());
        textInput.SetHeight(HeightType.Stretch);
        textInput.SetInlineAction(TestUtil.createSampleOpenUrlAction());
        textInput.SetIsMultiline(true);
        textInput.SetIsVisible(false);
        textInput.SetLabel("Input label");
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
        TextInputCommand<Boolean> c = new TextInputCommand<Boolean>() {
            @Override
            public Boolean get(TextInput element) { return element.GetIsMultiline(); }

            @Override
            public void set(Boolean value, TextInput element) { element.SetIsMultiline(value); }
        };

        TestUtil.executeBooleanTests(c, c_defaultInputText, "{\"id\":\"id\",\"isMultiline\":%b,\"type\":\"Input.Text\"}\n", false);
    }

    @Test
    public void MaxLengthTest() throws Exception
    {
        TextInputCommand<Long> c = new TextInputCommand<Long>() {
            @Override
            public Long get(TextInput element) { return element.GetMaxLength(); }

            @Override
            public void set(Long value, TextInput element) { element.SetMaxLength(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputText, 0L);

        final String inputTextMaxLengthTemplate = "{\"id\":\"id\",\"maxLength\":%d,\"type\":\"Input.Text\"}\n";
        Long tests[] = {1L, 5L, 10L, 25L, 50L};
        TestUtil.executeTests(c, inputTextMaxLengthTemplate, tests);
    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        TextInputCommand<String> c = new TextInputCommand<String>() {
            @Override
            public String get(TextInput element) { return element.GetPlaceholder(); }

            @Override
            public void set(String value, TextInput element) { element.SetPlaceholder(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputText, "");

        final String inputTextPlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Text\"}\n";
        TestUtil.executeTests(c, inputTextPlaceholderTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputTextPlaceholderTemplate, TestUtil.c_dateStringTestCases);
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
        TextInputCommand<String> c = new TextInputCommand<String>() {
            @Override
            public String get(TextInput element) { return element.GetValue(); }

            @Override
            public void set(String value, TextInput element) { element.SetValue(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputText, "");

        final String inputTextValueTemplate = "{\"id\":\"id\",\"type\":\"Input.Text\",\"value\":\"%s\"}\n";
        TestUtil.executeTests(c, inputTextValueTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputTextValueTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void LabelTest() throws Exception
    {
        TextInputCommand<String> c = new TextInputCommand<String>() {
            @Override
            public String get(TextInput element) { return element.GetLabel(); }

            @Override
            public void set(String value, TextInput element) { element.SetLabel(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputText, "");

        final String inputTextLabelTemplate = "{\"id\":\"id\",\"label\":\"%s\",\"type\":\"Input.Text\"}\n";
        TestUtil.executeTests(c, inputTextLabelTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void ErrorMessageTest() throws Exception
    {
        TextInputCommand<String> c = new TextInputCommand<String>() {
            @Override
            public String get(TextInput element) { return element.GetErrorMessage(); }

            @Override
            public void set(String value, TextInput element) { element.SetErrorMessage(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputText, "");

        final String inputTextErrorMessageTemplate = "{\"errorMessage\":\"%s\",\"id\":\"id\",\"type\":\"Input.Text\"}\n";
        TestUtil.executeTests(c, inputTextErrorMessageTemplate, TestUtil.c_regularStringTestCases);
    }

    private abstract class TextInputCommand<E> implements TestUtil.Command<TextInput, E>
    {
        @Override
        public TextInput getMockObject()
        {
            return TestUtil.createMockTextInput();
        }

        @Override
        public TextInput castTo(BaseCardElement element) {
            return TestUtil.castToTextInput(element);
        }
    }

    private String c_defaultInputText = "{\"id\":\"id\",\"type\":\"Input.Text\"}\n";
}
