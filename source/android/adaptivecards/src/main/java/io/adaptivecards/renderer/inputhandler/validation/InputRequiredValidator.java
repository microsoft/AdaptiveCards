package io.adaptivecards.renderer.inputhandler.validation;

public abstract class InputRequiredValidator implements IInputValidator
{
    /**
     * This method must be overriden by every type as they have different ways of validating
     * whether they have fulfilled the requirement (i.e. an Input.Text has text in it or an
     * ChoiceSet has an element selected)
     * @return true if the input has been completed, false otherwise
     */
    public abstract boolean compliesRequired();

    public InputRequiredValidator(boolean isRequired) {
        m_isRequired = isRequired;
    }

    @Override
    public boolean isValid() {
        if (!m_isRequired)
        {
            return true;
        }
        else
        {
            return compliesRequired();
        }
    }

    private boolean m_isRequired = false;
}
