package io.adaptivecards.renderer.inputhandler;

public abstract class IInputRequiredValidator implements IInputValidator
{
    @Override
    public boolean isValid() {
        return compliesRequired();
    }

    public abstract boolean compliesRequired();
}
