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

public class CustomInput extends BaseInputElement
{
    public CustomInput(CardElementType cardElementType)
    {
        super(cardElementType);
    }

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


    public static class CustomInputParser extends BaseCardElementParser
    {
        @Override
        public BaseCardElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomInput element = new CustomInput(CardElementType.Custom);
            Util.deserializeBaseInputProperties(context, value, element);

            element.SetElementTypeString(customInputTypeString);
            String val = value.getString();
            try
            {
                JSONObject obj = new JSONObject(val);
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
            Util.deserializeBaseInputPropertiesFromString(context, jsonString, element);

            element.SetElementTypeString(customInputTypeString);
            try
            {
                JSONObject obj = new JSONObject(jsonString);
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
