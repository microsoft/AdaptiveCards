package io.adaptivecards.objectmodel;

import android.util.Pair;

import junit.framework.Assert;

import org.junit.Test;

import java.util.ArrayList;

import static org.junit.Assert.*;

public class NumberInputPropertiesTest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void AllPropertiesTest()
    {
        final String numberInputNoDefaultValues =
            "{\"errorMessage\":\"Error message\"," +
                "\"id\":\"id\"," +
                "\"label\":\"Input label\"," +
                "\"max\":10," +
                "\"min\":1," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"type\":\"Input.Number\"," +
                "\"value\":5}\n";

        NumberInput numberInput = TestUtil.createMockNumberInput();
        numberInput.SetErrorMessage("Error message");
        numberInput.SetLabel("Input label");
        numberInput.SetMax(10);
        numberInput.SetMin(1);
        numberInput.SetPlaceholder("Sample placeholder");
        numberInput.SetValue(5);

        Assert.assertEquals(numberInputNoDefaultValues, numberInput.Serialize());
    }

    @Test
    public void AllPropertiesWithInheritedTest()
    {
        final String textInputNoDefaultValues =
            "{\"errorMessage\":\"Error message\"," +
                "\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"label\":\"Input label\"," +
                "\"max\":100," +
                "\"min\":-10," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"Input.Number\"," +
                "\"value\":60}\n";

        NumberInput numberInput = TestUtil.createMockNumberInput();
        numberInput.SetErrorMessage("Error message");
        numberInput.SetFallbackType(FallbackType.Content);
        numberInput.SetFallbackContent(TestUtil.createMockImage());
        numberInput.SetHeight(HeightType.Stretch);
        numberInput.SetIsVisible(false);
        numberInput.SetLabel("Input label");
        numberInput.SetMax(100);
        numberInput.SetMin(-10);
        numberInput.SetPlaceholder("Sample placeholder");
        numberInput.SetSeparator(true);
        numberInput.SetSpacing(Spacing.Medium);
        numberInput.SetValue(60);

        Assert.assertEquals(textInputNoDefaultValues, numberInput.Serialize());
    }

    @Test
    public void MaxTest() throws Exception
    {
        NumberInputCommand<Integer> c = new NumberInputCommand<Integer>() {
            @Override
            public Integer get(NumberInput element) { return element.GetMax(); }

            @Override
            public void set(Integer value, NumberInput element) { element.SetMax(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputNumber, 2147483647);

        final String inputNumberMaxTemplate = "{\"id\":\"id\",\"max\":%d,\"type\":\"Input.Number\"}\n";
        TestUtil.executeTests(c, inputNumberMaxTemplate, TestUtil.c_numericalMinValue);
        TestUtil.executeTests(c, inputNumberMaxTemplate, TestUtil.c_numericalTestCases);
    }

    @Test
    public void MinTest() throws Exception
    {
        NumberInputCommand<Integer> c = new NumberInputCommand<Integer>() {
            @Override
            public Integer get(NumberInput element) { return element.GetMin(); }

            @Override
            public void set(Integer value, NumberInput element) { element.SetMin(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputNumber, -2147483648);

        final String inputNumberMinTemplate = "{\"id\":\"id\",\"min\":%d,\"type\":\"Input.Number\"}\n";
        TestUtil.executeTests(c, inputNumberMinTemplate, TestUtil.c_numericalMaxValue);
        TestUtil.executeTests(c, inputNumberMinTemplate, TestUtil.c_numericalTestCases);
    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        NumberInputCommand<String> c = new NumberInputCommand<String>() {
            @Override
            public String get(NumberInput element) { return element.GetPlaceholder(); }

            @Override
            public void set(String value, NumberInput element) { element.SetPlaceholder(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputNumber, "");

        final String inputToggleLabelTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Number\"}\n";
        TestUtil.executeTests(c, inputToggleLabelTemplate, TestUtil.c_regularStringTestCases);
        TestUtil.executeTests(c, inputToggleLabelTemplate, TestUtil.c_dateStringTestCases);
    }

    @Test
    public void ValueTest() throws Exception
    {
        NumberInputCommand<Integer> c = new NumberInputCommand<Integer>() {
            @Override
            public Integer get(NumberInput element) { return element.GetValue(); }

            @Override
            public void set(Integer value, NumberInput element) { element.SetValue(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputNumber, 0);

        final String inputNumberValueTemplate = "{\"id\":\"id\",\"type\":\"Input.Number\",\"value\":%d}\n";
        TestUtil.executeTests(c, inputNumberValueTemplate, TestUtil.c_numericalTestCases);
    }

    @Test
    public void LabelTest() throws Exception
    {
        NumberInputCommand<String> c = new NumberInputCommand<String>() {
            @Override
            public String get(NumberInput element) { return element.GetLabel(); }

            @Override
            public void set(String value, NumberInput element) { element.SetLabel(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputNumber, "");

        final String inputToggleLabelTemplate = "{\"id\":\"id\",\"label\":\"%s\",\"type\":\"Input.Number\"}\n";
        TestUtil.executeTests(c, inputToggleLabelTemplate, TestUtil.c_regularStringTestCases);
    }

    @Test
    public void ErrorMessageTest() throws Exception
    {
        NumberInputCommand<String> c = new NumberInputCommand<String>() {
            @Override
            public String get(NumberInput element) { return element.GetErrorMessage(); }

            @Override
            public void set(String value, NumberInput element) { element.SetErrorMessage(value); }
        };

        TestUtil.executeDefaultTestCase(c, c_defaultInputNumber, "");

        final String inputToggleErrorMessageTemplate = "{\"errorMessage\":\"%s\",\"id\":\"id\",\"type\":\"Input.Number\"}\n";
        TestUtil.executeTests(c, inputToggleErrorMessageTemplate, TestUtil.c_regularStringTestCases);
    }

    private abstract class NumberInputCommand<E> implements TestUtil.Command<NumberInput, E>
    {
        @Override
        public NumberInput getMockObject()
        {
            return TestUtil.createMockNumberInput();
        }

        @Override
        public NumberInput castTo(BaseCardElement element) {
            return TestUtil.castToNumberInput(element);
        }
    }

    private final String c_defaultInputNumber = "{\"id\":\"id\",\"type\":\"Input.Number\"}\n";
}
