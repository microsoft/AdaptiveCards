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
}
