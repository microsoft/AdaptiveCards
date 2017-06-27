package com.microsoft.adaptivecards.actionhandler;

import android.graphics.Color;
import android.text.TextUtils;
import android.util.TypedValue;
import android.widget.EditText;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.TextInput;

/**
 * Created by bekao on 6/27/2017.
 */

public class TextInputActionHandler
{
    public TextInputActionHandler(TextInput textInput, EditText editText)
    {
        m_textInput = textInput;
        m_editText = editText;
    }

    private void setEditTextToDefaultTextColor()
    {
        TypedValue typedValue = new TypedValue();
        m_editText.getContext().getTheme().resolveAttribute(android.R.attr.editTextColor, typedValue, true);
        m_editText.setTextColor(typedValue.data);
    }

    private void setEditTextToInvalidTextColor()
    {
        m_editText.setTextColor(Color.RED);
    }

    protected void internalValidate()
    {
        String value = m_editText.getText().toString();
        if (TextUtils.isEmpty(value) && m_textInput.GetIsRequired())
        {
            throw new IllegalArgumentException(m_textInput.GetId() + " cannot be empty.");
        }
    }

    public boolean validate()
    {
        try
        {
            internalValidate();
            setEditTextToDefaultTextColor();
            return true;
        }
        catch (IllegalArgumentException illegalArgumentExcep)
        {
            setEditTextToInvalidTextColor();
            Toast.makeText(m_editText.getContext(), illegalArgumentExcep.getMessage(), Toast.LENGTH_LONG).show();
            return false;
        }
    }

    private TextInput m_textInput = null;
    private EditText m_editText = null;
}
