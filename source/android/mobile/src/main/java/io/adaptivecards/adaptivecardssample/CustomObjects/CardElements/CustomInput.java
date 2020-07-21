// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.adaptivecardssample.CustomObjects.CardElements;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.LinearLayout;

import org.json.JSONException;
import org.json.JSONObject;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseCardElementParser;
import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;

/**
 * CustomInput is a class used to demonstrate and test the user experience for creating a custom
 * input element. This class inherits from BaseInputElement and contains a BaseInputHandler class
 * to test input retrieval, a BaseCardElementParser to test element parsing and a
 * BaseCardElementRenderer to test element rendering and automatically rendered properties such as
 * errorMessage, label or spacing
 */
public class CustomInput extends BaseInputElement
{
    public CustomInput(CardElementType cardElementType)
    {
        super(cardElementType);
    }

    /**
     * The CustomInputHandler class extends from BaseInputHandler, extending this class is required
     * for any input element as it defines how it retrieves the values
     */
    public static class CustomInputHandler extends BaseInputHandler
    {
        public CustomInputHandler(BaseInputElement baseInputElement, EditText editText)
        {
            super(baseInputElement);
            m_view = editText;
        }

        @Override
        public String getInput()
        {
            return ((EditText)m_view).getText().toString();
        }

        @Override
        public void setInput(String input)
        {
            ((EditText)m_view).setText(input);
        }

        @Override
        public void setFocusToView()
        {
            m_view.requestFocus();
        }
    }

    /**
     * CustomInputRenderer as the name might hint, renders the custom input. This class extends
     * from BaseCardElementRenderer. It's important to set a tag to the rendered element so
     * some properties as visibility work properly.
    */
    public static class CustomInputRenderer extends BaseCardElementRenderer
    {
        @Override
        public View render(RenderedAdaptiveCard renderedCard,
                           Context context,
                           FragmentManager fragmentManager,
                           ViewGroup viewGroup,
                           BaseCardElement baseCardElement,
                           ICardActionHandler cardActionHandler,
                           HostConfig hostConfig,
                           RenderArgs renderArgs) throws Exception
        {
            EditText renderedInput = new EditText(context);
            renderedInput.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));

            renderedInput.setBackgroundColor(Color.GREEN);
            renderedInput.setTag(new TagContent(baseCardElement));
            viewGroup.addView(renderedInput);

            BaseInputElement inputElement = Util.castTo(baseCardElement, BaseInputElement.class);
            renderedCard.registerInputHandler(new CustomInputHandler(inputElement, renderedInput), renderArgs.getContainerCardId());
            return renderedInput;
        }
    }

    /**
     * CustomInputParser as the name might hint, parses the custom input. This class extends
     * from BaseCardElementParser. This example is really simple and only gets the Id and label
     * for the input.
     */
    public static class CustomInputParser extends BaseCardElementParser
    {
        @Override
        public BaseCardElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomInput element = new CustomInput(CardElementType.Custom);
            element.SetElementTypeString(customInputTypeString);
            String val = value.getString();
            try
            {
                JSONObject obj = new JSONObject(val);
                element.SetId(obj.getString("id"));
                element.SetLabel(obj.getString("label"));
            }
            catch (JSONException e)
            {
                e.printStackTrace();
            }
            return element;
        }

        @Override
        public BaseCardElement DeserializeFromString(ParseContext context, String jsonString)
        {
            CustomInput element = new CustomInput(CardElementType.Custom);
            element.SetElementTypeString(customInputTypeString);
            try
            {
                JSONObject obj = new JSONObject(jsonString);
                element.SetId(obj.getString("id"));
                element.SetLabel(obj.getString("label"));
            }
            catch (JSONException e)
            {
                e.printStackTrace();
            }
            return element;
        }
    }

    public final static String customInputTypeString = "customInput";
}
