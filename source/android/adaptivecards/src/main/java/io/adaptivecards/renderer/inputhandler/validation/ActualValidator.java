package io.adaptivecards.renderer.inputhandler.validation;

import android.view.View;
import android.widget.EditText;

import java.util.List;

public class ActualValidator implements IInputValidator
{

    public ActualValidator(IInputValidator inputValidator)
    {
        this.m_inputValidator = inputValidator;
    }

    @Override
    public boolean isValid()
    {
        return m_inputValidator.isValid();
    }

    @Override
    public void setViewForValidation(View v)
    {
        m_inputValidator.setViewForValidation(v);
    }

    @Override
    public List<View> getViewsForValidation()
    {
        return m_inputValidator.getViewsForValidation();
    }

    /*
    public View getView()
    {
        View view = null;

        if (m_inputValidator instanceof TextInputValidator)
        {
            view = ((TextInputValidator) m_inputValidator).getTextInput();
        }
        else if (m_inputValidator instanceof ActualValidator)
        {
            view = ((ActualValidator)m_inputValidator).getView();
        }

        return view;
    }

    public void setView(EditText editText)
    {
        if (m_inputValidator instanceof TextInputValidator)
        {
            ((TextInputValidator) m_inputValidator).setTextInput(editText);
        }
        else if (m_inputValidator instanceof ActualValidator)
        {
            ((ActualValidator)m_inputValidator).setView(editText);
        }
    }
    */

    protected IInputValidator m_inputValidator;
}
