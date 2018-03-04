package io.adaptivecards.renderer.input;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.renderer.inputhandler.TextInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.TextInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TextInputStyle;
import io.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.Vector;

public class TextInputRenderer extends BaseCardElementRenderer
{
    protected TextInputRenderer()
    {
    }

    public static TextInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new TextInputRenderer();
        }

        return s_instance;
    }

    protected void setTextInputStyle(EditText editText, TextInputStyle textInputStyle)
    {
        if (textInputStyle == TextInputStyle.Text)
        {
            // do nothing
        }
        else if (textInputStyle == TextInputStyle.Tel)
        {
            editText.setInputType(InputType.TYPE_CLASS_PHONE);
        }
        else if (textInputStyle == TextInputStyle.Url)
        {
            editText.setInputType(InputType.TYPE_TEXT_VARIATION_URI);
        }
        else if (textInputStyle == TextInputStyle.Email)
        {
            editText.setInputType(InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
        }
        else
        {
            throw new IllegalArgumentException("Unknown TextInputStyle: " + textInputStyle.toString());
        }
    }

    protected EditText renderInternal(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ViewGroup viewGroup,
            BaseInputElement baseInputElement,
            String value,
            String placeHolder,
            TextInputHandler textInputHandler,
            HostConfig hostConfig)
    {
        EditText editText = new EditText(context);
        textInputHandler.setView(editText);
        editText.setTag(textInputHandler);
        editText.setTextColor(Color.BLACK);
        renderedCard.registerInputHandler(textInputHandler);

        if (!TextUtils.isEmpty(value))
        {
            editText.setText(value);
        }

        if (!TextUtils.isEmpty(placeHolder))
        {
            editText.setHint(placeHolder);
        }

        viewGroup.addView(editText);
        return editText;
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
    {
        TextInput textInput = null;
        if (baseCardElement instanceof TextInput)
        {
            textInput = (TextInput) baseCardElement;
        }
        else if ((textInput = TextInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TextInput object model.");
        }

        TextInputHandler textInputHandler = new TextInputHandler(textInput);
        setSpacingAndSeparator(context, viewGroup, textInput.GetSpacing(), textInput.GetSeparator(), hostConfig, true /* horizontal line */);
        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                textInput,
                textInput.GetValue(),
                textInput.GetPlaceholder(),
                textInputHandler,
                hostConfig);
        editText.setSingleLine(!textInput.GetIsMultiline());
        if (textInput.GetIsMultiline())
        {
            editText.setLines(3);
        }
        setTextInputStyle(editText, textInput.GetTextInputStyle());
        int maxLength = (int) Math.min(textInput.GetMaxLength(), Integer.MAX_VALUE);
        if (maxLength > 0)
        {
            editText.setFilters(new InputFilter[] {new InputFilter.LengthFilter(maxLength)});
        }

        return editText;
    }
    
    private static TextInputRenderer s_instance = null;
}
