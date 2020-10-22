package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.graphics.PorterDuff;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.input.ValidatedEditText;

/**
 * This class is only supposed to be used for inputs that have: label, validation, isRequired or stretch height
 */
public class StretchableInputLayout extends StretchableElementLayout
{
    private TextView m_label = null;
    private View m_inputView = null;
    private TextView m_errorMessage = null;
//    private TextView m_errorLabel;
    private boolean isValid = true;

    public StretchableInputLayout(Context context, boolean mustStretch)
    {
        super(context, mustStretch);

        // Using setContentDescription on EditText is discouraged, so using hidden TextView instead
//        m_errorLabel = new TextView(context);
    }

    public View getLabel()
    {
        return m_label;
    }

    public void setLabel(TextView label)
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
        addView(input);
        m_inputView = input;
//        if(m_inputView.getId() == View.NO_ID) {
//            m_inputView.setId(View.generateViewId());
//        }
        m_label.setLabelFor(m_inputView.getId());
    }

    public View getErrorMessage()
    {
        return m_errorMessage;
    }

    public void setErrorMessage(TextView errorMessage)
    {
        addView(errorMessage);
        m_errorMessage = errorMessage;
        m_errorMessage.setImportantForAccessibility(IMPORTANT_FOR_ACCESSIBILITY_NO);
    }

    public void setValidationResult(boolean isValid)
    {
        BaseCardElementRenderer.setVisibility(!isValid, m_errorMessage);
        if(m_inputView instanceof ValidatedEditText)
        {
            ((ValidatedEditText) m_inputView).setValidationResult(isValid);
        }
        if(isValid)
        {
            m_label.setContentDescription(null);
        }
        else
        {
            m_label.setContentDescription(m_label.getText() + " " + m_errorMessage.getText());
        }
    }

//    private void updateAccessbleLabel() {
//        m_accessibleLabel.removeAllViews();
//        m_accessibleLabel.addView(m_label);
//        m_accessibleLabel.addView(m_errorMessage);
//    }



}
