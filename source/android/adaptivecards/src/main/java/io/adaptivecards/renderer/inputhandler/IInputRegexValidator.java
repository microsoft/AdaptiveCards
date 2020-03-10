package io.adaptivecards.renderer.inputhandler;

public abstract class IInputRegexValidator extends IInputRequiredValidator
{
    @Override
    public boolean isValid()
    {
        return compliesRequired() && fulfillsRegex();
    }

    @Override
    public boolean compliesRequired() {
        return false;
    }

    public abstract boolean fulfillsRegex();
}
