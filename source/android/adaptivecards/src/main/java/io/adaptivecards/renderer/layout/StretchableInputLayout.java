package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.view.View;
import android.widget.TextView;

import io.adaptivecards.objectmodel.TextInput;
import io.adaptivecards.renderer.inputhandler.validation.IInputValidator;

/**
 * This class is only supposed to be used for inputs that have: label, validation, isRequired or stretch height
 */
public class StretchableInputLayout extends StretchableElementLayout
{
    public StretchableInputLayout(Context context, boolean mustStretch)
    {
        super(context, mustStretch);
    }

    public View getLabel()
    {
        return m_label;
    }

    public void setLabel(View label)
    {
        addView(label);
        m_label = label;
    }

    public View getInputView()
    {
        return m_inputView;
    }

    public void setInputView(View input)
    {
        // addView(input);
        m_inputView = input;
    }

    public View getValidationLabel()
    {
        return m_validationLabel;
    }

    public void setValidationLabel(View validationLabel)
    {
        m_validationLabel = validationLabel;
    }

    private View m_label = null;
    private View m_inputView = null;
    private View m_validationLabel = null;

    // private IInputValidator m_inputValidator = null;
}
