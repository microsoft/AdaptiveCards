package io.adaptivecards.renderer.inputhandler.validation;

import android.view.View;

import java.util.List;

public class InputValidator implements IInputValidator
{
    public InputValidator (IInputValidator inputValidator)
    {
        m_inputValidator = inputValidator;
    }

    @Override
    public boolean isValid()
    {
        return false;
    }

    @Override
    public void setViewForValidation(View v) {
        return;
    }

    @Override
    public List<View> getViewsForValidation() {
        return null;
    }

    private IInputValidator m_inputValidator;
}
