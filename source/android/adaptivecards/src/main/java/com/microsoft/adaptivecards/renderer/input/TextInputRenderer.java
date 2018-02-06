package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.text.InputFilter;
import android.text.InputType;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.TextInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.TextInput;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.TextInputStyle;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.Vector;

/**
 * Created by bekao on 6/25/2017.
 */

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
        if (textInputStyle.swigValue() == TextInputStyle.Text.swigValue())
        {
            // do nothing
        }
        else if (textInputStyle.swigValue() == TextInputStyle.Tel.swigValue())
        {
            editText.setInputType(InputType.TYPE_CLASS_PHONE);
        }
        else if (textInputStyle.swigValue() == TextInputStyle.Url.swigValue())
        {
            editText.setInputType(InputType.TYPE_TEXT_VARIATION_URI);
        }
        else if (textInputStyle.swigValue() == TextInputStyle.Email.swigValue())
        {
            editText.setInputType(InputType.TYPE_TEXT_VARIATION_EMAIL_ADDRESS);
        }
        else
        {
            throw new IllegalArgumentException("Unknown TextInputStyle: " + textInputStyle.toString());
        }
    }

    protected EditText renderInternal(
            Context context,
            ViewGroup viewGroup,
            BaseInputElement baseInputElement,
            String value,
            String placeHolder,
            TextInputHandler textInputHandler,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        EditText editText = new EditText(context);
        textInputHandler.setView(editText);
        editText.setTag(textInputHandler);
        editText.setTextColor(Color.BLACK);
        inputActionHandlerList.add(textInputHandler);

        if (!TextUtils.isEmpty(value))
        {
            editText.setText(value);
        }

        if (!TextUtils.isEmpty(placeHolder))
        {
            editText.setHint(placeHolder);
        }

        editText.setOnFocusChangeListener(new View.OnFocusChangeListener()
        {
            @Override
            public void onFocusChange(View v, boolean hasFocus)
            {
                if (!hasFocus)
                {
                    IInputHandler inputHandler = (IInputHandler) v.getTag();
                    inputHandler.validate();
                }
            }
        });

        viewGroup.addView(editText);
        return editText;
    }

    @Override
    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
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
                context,
                viewGroup,
                textInput,
                textInput.GetValue(),
                textInput.GetPlaceholder(),
                textInputHandler,
                inputActionHandlerList,
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
