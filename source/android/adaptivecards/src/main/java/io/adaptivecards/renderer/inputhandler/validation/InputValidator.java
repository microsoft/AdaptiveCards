package io.adaptivecards.renderer.inputhandler.validation;

public class InputValidator implements IInputValidator
{

    public InputValidator (IInputValidator inputValidator)
    {
        m_inputValidator = inputValidator;
    }

    @Override
    public boolean isValid() {
        return false;
    }

    private IInputValidator m_inputValidator;
}
