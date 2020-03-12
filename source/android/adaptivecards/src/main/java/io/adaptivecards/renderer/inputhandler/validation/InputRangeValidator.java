package io.adaptivecards.renderer.inputhandler.validation;

public abstract class InputRangeValidator extends InputValidator
{
    public InputRangeValidator(IInputValidator inputValidator) {
        super(inputValidator);
    }

    @Override
    public boolean isValid() {
        return super.isValid() && isInputInRange();
    }

    public abstract boolean isInputInRange();
}
