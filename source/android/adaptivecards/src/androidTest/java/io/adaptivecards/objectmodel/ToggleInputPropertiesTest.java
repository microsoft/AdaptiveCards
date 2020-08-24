package io.adaptivecards.objectmodel;

import junit.framework.Assert;
import org.junit.Test;

public class ToggleInputPropertiesTest
{
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String dateInputNoDefaultValues =
            "{\"errorMessage\":\"Error message\"," +
                "\"id\":\"id\"," +
                "\"label\":\"Input label\"," +
                "\"title\":\"Sample title\"," +
                "\"type\":\"Input.Toggle\"," +
                "\"value\":\"Sample value\"," +
                "\"valueOff\":\"Sample value off\"," +
                "\"valueOn\":\"Sample value on\"," +
                "\"wrap\":true}\n";

        ToggleInput toggleInput = TestUtil.createMockToggleInput();
        toggleInput.SetErrorMessage("Error message");
        toggleInput.SetLabel("Input label");
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
            "{\"errorMessage\":\"Error message\"," +
            "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"label\":\"Input label\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"title\":\"Sample title\"," +
                "\"type\":\"Input.Toggle\"," +
                "\"value\":\"Sample value\"," +
                "\"valueOff\":\"Sample value off\"," +
                "\"valueOn\":\"Sample value on\"," +
                "\"wrap\":true}\n";

        ToggleInput toggleInput = TestUtil.createMockToggleInput();
        toggleInput.SetErrorMessage("Error message");
        toggleInput.SetFallbackType(FallbackType.Content);
        toggleInput.SetFallbackContent(TestUtil.createMockImage());
        toggleInput.SetHeight(HeightType.Stretch);
        toggleInput.SetIsVisible(false);
        toggleInput.SetLabel("Input label");
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
        ToggleInputCommand<String> c = new ToggleInputCommand<String>() {
            @Override
            public String get(ToggleInput element) { return element.GetTitle(); }

            @Override
            public void set(String value, ToggleInput element) { element.SetTitle(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputToggle, "");

        final String inputToggleTitleTemplate = "{\"id\":\"id\",\"title\":\"%s\",\"type\":\"Input.Toggle\"}\n";
        TestUtil.executeTests(c, inputToggleTitleTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputToggleTitleTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void ValueTest() throws Exception
    {
        ToggleInputCommand<String> c = new ToggleInputCommand<String>() {
            @Override
            public String get(ToggleInput element) { return element.GetValue(); }

            @Override
            public void set(String value, ToggleInput element) { element.SetValue(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputToggle, "");

        final String inputToggleValueTemplate = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"value\":\"%s\"}\n";
        TestUtil.executeTests(c, inputToggleValueTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputToggleValueTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void ValueOffTest() throws Exception
    {
        ToggleInputCommand<String> c = new ToggleInputCommand<String>() {
            @Override
            public String get(ToggleInput element) { return element.GetValueOff(); }

            @Override
            public void set(String value, ToggleInput element) { element.SetValueOff(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputToggle, "false");

        final String inputToggleValueTemplate = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"valueOff\":\"%s\"}\n";
        TestUtil.executeTests(c, inputToggleValueTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputToggleValueTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void ValueOnTest() throws Exception
    {
        ToggleInputCommand<String> c = new ToggleInputCommand<String>() {
            @Override
            public String get(ToggleInput element) { return element.GetValueOn(); }

            @Override
            public void set(String value, ToggleInput element) { element.SetValueOn(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputToggle, "true");

        final String inputToggleValueTemplate = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"valueOn\":\"%s\"}\n";
        TestUtil.executeTests(c, inputToggleValueTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputToggleValueTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void WrapTest() throws Exception
    {
        ToggleInputCommand<Boolean> c = new ToggleInputCommand<Boolean>() {
            @Override
            public Boolean get(ToggleInput element) { return element.GetWrap(); }

            @Override
            public void set(Boolean value, ToggleInput element) { element.SetWrap(value); }
        };

        TestUtil.executeBooleanTests(c, c_defaultInputToggle, "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\",\"wrap\":%b}\n", false);
    }

    @Test
    public void LabelTest() throws Exception
    {
        ToggleInputCommand<String> c = new ToggleInputCommand<String>() {
            @Override
            public String get(ToggleInput element) { return element.GetLabel(); }

            @Override
            public void set(String value, ToggleInput element) { element.SetLabel(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputToggle, "");

        final String inputToggleLabelTemplate = "{\"id\":\"id\",\"label\":\"%s\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";
        TestUtil.executeTests(c, inputToggleLabelTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void ErrorMessageTest() throws Exception
    {
        ToggleInputCommand<String> c = new ToggleInputCommand<String>() {
            @Override
            public String get(ToggleInput element) { return element.GetErrorMessage(); }

            @Override
            public void set(String value, ToggleInput element) { element.SetErrorMessage(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputToggle, "");

        final String inputToggleErrorMessageTemplate = "{\"errorMessage\":\"%s\",\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";
        TestUtil.executeTests(c, inputToggleErrorMessageTemplate, TestUtil.c_regularStringTestCases);
    }

    private abstract class ToggleInputCommand<E> implements TestUtil.Command<ToggleInput, E>
    {
        @Override
        public ToggleInput getMockObject()
        {
            return TestUtil.createMockToggleInput();
        }

        @Override
        public ToggleInput castTo(BaseCardElement element) {
            return TestUtil.castToToggleInput(element);
        }
    }

    private final String c_defaultInputToggle = "{\"id\":\"id\",\"title\":\"\",\"type\":\"Input.Toggle\"}\n";
}
