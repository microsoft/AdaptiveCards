package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.text.InputFilter;
import android.text.InputType;
import android.util.TypedValue;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.TextInput;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.TextInputStyle;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

/**
 * Created by bekao on 6/25/2017.
 */

public class TextInputRenderer extends BaseCardElementRenderer
{
    private TextInputRenderer()
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

    private void setTextInputStyle(EditText editText, TextInputStyle textInputStyle)
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

    @Override
    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostConfig hostConfig)
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

        EditText editText = new EditText(context);
        editText.setTag(baseCardElement);
        editText.setText(textInput.GetValue());
        editText.setHint(textInput.GetPlaceholder());
        editText.setSingleLine(!textInput.GetIsMultiline());
        setTextInputStyle(editText, textInput.GetTextInputStyle());
        setSeparationConfig(context, viewGroup, textInput.GetSeparationStyle(), hostConfig.getTextInput().getSeparation(), hostConfig.getTextInput().getSeparation(), true /* horizontal line */);
        int maxLength = (int) Math.min(textInput.GetMaxLength(), Integer.MAX_VALUE);
        if (maxLength > 0)
        {
            editText.setFilters(new InputFilter[] {new InputFilter.LengthFilter(maxLength)});
        }

        editText.setOnFocusChangeListener(new View.OnFocusChangeListener()
        {
            @Override
            public void onFocusChange(View v, boolean hasFocus)
            {
                EditText editText = (EditText) v;
                if(!hasFocus)
                {
                    Toast.makeText(v.getContext(), "got the focus", Toast.LENGTH_LONG).show();
                }
                else
                {
                    TypedValue typedValue = new TypedValue();
                    v.getContext().getTheme().resolveAttribute(android.R.attr.editTextColor, typedValue, true);
                    editText.setTextColor(typedValue.data);
                }
            }
        });

        viewGroup.addView(editText);
        return viewGroup;
    }
    
    private static TextInputRenderer s_instance = null;
}
