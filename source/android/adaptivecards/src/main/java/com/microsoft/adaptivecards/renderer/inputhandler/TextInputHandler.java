package com.microsoft.adaptivecards.renderer.inputhandler;

import android.graphics.Color;
import android.text.TextUtils;
import android.widget.EditText;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;

import java.text.ParseException;
import java.util.Map;

/**
 * Created by bekao on 6/27/2017.
 */

public class TextInputHandler implements IInputHandler
{
    public TextInputHandler(BaseInputElement baseInputElement)
    {
        m_baseInputElement = baseInputElement;
    }

    public void setEditText(EditText editText)
    {
        m_editText = editText;
    }

    public BaseInputElement getBaseInputElement()
    {
        return m_baseInputElement;
    }

    private void setEditTextToDefaultTextColor()
    {
        //TypedValue typedValue = new TypedValue();
        //m_editText.getContext().getTheme().resolveAttribute(android.R.attr.editTextColor, typedValue, true);
        //m_editText.setTextColor(typedValue.data);
        m_editText.setTextColor(Color.BLACK);
    }

    private void setEditTextToInvalidTextColor()
    {
        m_editText.setTextColor(Color.RED);
    }

    protected void internalValidate()
            throws ParseException
    {
        String value = m_editText.getText().toString();
        if (TextUtils.isEmpty(value) && m_baseInputElement.GetIsRequired())
        {
            throw new IllegalArgumentException("Input, " + m_baseInputElement.GetId() + ", cannot be empty.");
        }
    }

    public Exception validate()
    {
        try
        {
            internalValidate();
            setEditTextToDefaultTextColor();
            return null;
        }
        catch (Exception excep)
        {
            setEditTextToInvalidTextColor();
            Toast.makeText(m_editText.getContext(), excep.getMessage(), Toast.LENGTH_LONG).show();
            return excep;
        }
    }

    public Exception getData(Map<String, String> data)
    {
        Exception excep = validate();
        if (excep == null)
        {
            data.put(m_baseInputElement.GetId(), m_editText.getText().toString());
        }

        return excep;
    }


    protected BaseInputElement m_baseInputElement = null;
    protected EditText m_editText = null;
}
