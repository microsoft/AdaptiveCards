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
            "{\"id\":\"id\"," +
                "\"max\":10," +
                "\"min\":1," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"type\":\"Input.Number\"," +
                "\"value\":5}\n";

        NumberInput numberInput = TestUtil.createMockNumberInput();
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
            "{\"fallback\":{\"type\":\"Image\",\"url\":\"http://\"}," +
                "\"height\":\"Stretch\"," +
                "\"id\":\"id\"," +
                "\"isVisible\":false," +
                "\"max\":100," +
                "\"min\":-10," +
                "\"placeholder\":\"Sample placeholder\"," +
                "\"separator\":true," +
                "\"spacing\":\"medium\"," +
                "\"type\":\"Input.Number\"," +
                "\"value\":60}\n";

        NumberInput numberInput = TestUtil.createMockNumberInput();
        numberInput.SetFallbackType(FallbackType.Content);
        numberInput.SetFallbackContent(TestUtil.createMockImage());
        numberInput.SetHeight(HeightType.Stretch);
        numberInput.SetIsVisible(false);
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
        {
            final String inputNumberDefaultMax = "{\"id\":\"id\",\"type\":\"Input.Number\"}\n";

            NumberInput numberInput = TestUtil.createMockNumberInput();
            numberInput.SetMax(null);
            Assert.assertEquals(inputNumberDefaultMax, numberInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputNumberDefaultMax), "1.0");
            NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(2147483647, parsedNumberInput.GetMax().intValue());
        }

        {
            final String inputNumberMaxTemplate =
                "{\"id\":\"id\",\"max\":%d,\"type\":\"Input.Number\"}\n";
            int[] tests = {-2147483648, -100, -25, -10, -5, -1, 0, 1, 5, 10, 25, 50};

            for (int i = 0; i < tests.length; ++i)
            {
                String maxJson = String.format(inputNumberMaxTemplate, tests[i]);

                NumberInput numberInput = TestUtil.createMockNumberInput();
                numberInput.SetMax(tests[i]);
                Assert.assertEquals(maxJson, numberInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(maxJson), "1.0");
                NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedNumberInput.GetMax().intValue());
            }
        }

    }

    @Test
    public void MinTest() throws Exception
    {
        {
            final String inputNumberDefaultMin = "{\"id\":\"id\",\"type\":\"Input.Number\"}\n";

            NumberInput numberInput = TestUtil.createMockNumberInput();
            numberInput.SetMin(null);
            Assert.assertEquals(inputNumberDefaultMin, numberInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputNumberDefaultMin), "1.0");
            NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(-2147483648, parsedNumberInput.GetMin().intValue());
        }

        {
            final String inputNumberMinTemplate =
                "{\"id\":\"id\",\"min\":%d,\"type\":\"Input.Number\"}\n";
            int[] tests = {-100, -25, -10, -5, -1, 0, 1, 5, 10, 25, 50, 2147483647};

            for (int i = 0; i < tests.length; ++i)
            {
                String minJson = String.format(inputNumberMinTemplate, tests[i]);

                NumberInput numberInput = TestUtil.createMockNumberInput();
                numberInput.SetMin(tests[i]);
                Assert.assertEquals(minJson, numberInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(minJson), "1.0");
                NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedNumberInput.GetMin().intValue());
            }
        }

    }

    @Test
    public void PlaceholderTest() throws Exception
    {
        {
            final String inputNumberDefaultPlaceholder = "{\"id\":\"id\",\"type\":\"Input.Number\"}\n";

            NumberInput numberInput = TestUtil.createMockNumberInput();
            numberInput.SetPlaceholder("");
            Assert.assertEquals(inputNumberDefaultPlaceholder, numberInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputNumberDefaultPlaceholder), "1.0");
            NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals("", parsedNumberInput.GetPlaceholder());
        }

        {
            final String inputNumberPlaceholderTemplate = "{\"id\":\"id\",\"placeholder\":\"%s\",\"type\":\"Input.Number\"}\n";
            String tests[] = {"Sample text",
                "This is just a little bit tiny teeny bit larger than the one before this one a.k.a. index [0]",
                "The quick brown fox jumps over the lazy dog",
                "{{DATE(2017-02-14T06:08:39Z,LONG)}}",
                "This is some **bold** text"};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTextPlaceholderJson = String.format(inputNumberPlaceholderTemplate, tests[i]);

                NumberInput numberInput = TestUtil.createMockNumberInput();
                numberInput.SetPlaceholder(tests[i]);
                Assert.assertEquals(inputTextPlaceholderJson, numberInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextPlaceholderJson), "1.0");
                NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedNumberInput.GetPlaceholder());
            }
        }
    }

    @Test
    public void ValueTest() throws Exception
    {
        {
            final String inputNumberDefaultValue = "{\"id\":\"id\",\"type\":\"Input.Number\"}\n";

            NumberInput numberInput = TestUtil.createMockNumberInput();
            numberInput.SetValue(null);
            Assert.assertEquals(inputNumberDefaultValue, numberInput.Serialize());

            ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputNumberDefaultValue), "1.0");
            NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
            Assert.assertEquals(0, parsedNumberInput.GetValue().intValue());
        }

        {
            final String inputNumberValueTemplate = "{\"id\":\"id\",\"type\":\"Input.Number\",\"value\":%d}\n";
            int[] tests = {-2147483648, -100, -25, -10, -5, -1, 1, 5, 10, 25, 50, 2147483647};

            for (int i = 0; i < tests.length; ++i)
            {
                String inputTextValueJson = String.format(inputNumberValueTemplate, tests[i]);

                NumberInput numberInput = TestUtil.createMockNumberInput();
                numberInput.SetValue(tests[i]);
                Assert.assertEquals(inputTextValueJson, numberInput.Serialize());

                ParseResult result = AdaptiveCard.DeserializeFromString(TestUtil.encloseElementJsonInCard(inputTextValueJson), "1.0");
                NumberInput parsedNumberInput = TestUtil.castToNumberInput(result.GetAdaptiveCard().GetBody().get(0));
                Assert.assertEquals(tests[i], parsedNumberInput.GetValue().intValue());
            }
        }
    }

}
