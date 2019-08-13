package io.adaptivecards.adaptivecardssample.CustomObjects.CardElements;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.CardElementType;

public class CustomCardElement extends BaseCardElement
{

    public CustomCardElement(CardElementType type) {
        super(type);
    }

    public String getSecretString()
    {
        return secretString;
    }

    public void setSecretString(String secret)
    {
        secretString = secret;
    }

    private String secretString;

}
