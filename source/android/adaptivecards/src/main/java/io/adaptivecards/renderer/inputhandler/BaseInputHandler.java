package io.adaptivecards.renderer.inputhandler;

import android.view.View;
import android.widget.Toast;

import io.adaptivecards.objectmodel.BaseInputElement;

import java.text.ParseException;

public abstract class BaseInputHandler implements IInputHandler
{
    public BaseInputHandler(BaseInputElement baseInputElement)
    {
        m_baseInputElement = baseInputElement;
    }

    public void setView(View view)
    {
        m_view = view;
    }

    public BaseInputElement getBaseInputElement()
    {
        return m_baseInputElement;
    }

    protected abstract void setDefaultTextColor();

    protected abstract void setInvalidTextColor();

    protected abstract void internalValidate() throws ParseException;

    public Exception validate()
    {
        try
        {
            internalValidate();
            setDefaultTextColor();
            return null;
        }
        catch (Exception excep)
        {
            setInvalidTextColor();
            Toast.makeText(m_view.getContext(), excep.getMessage(), Toast.LENGTH_LONG).show();
            return excep;
        }
    }

    protected BaseInputElement m_baseInputElement = null;
    protected View m_view = null;

}
