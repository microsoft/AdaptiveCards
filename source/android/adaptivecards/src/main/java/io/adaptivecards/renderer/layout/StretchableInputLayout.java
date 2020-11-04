// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.view.View;
import android.widget.TextView;

import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.input.customcontrols.IValidatedInputView;
import io.adaptivecards.renderer.input.customcontrols.ValidatedSpinnerLayout;

/**
 * This class is only supposed to be used for inputs that have: label, validation, isRequired or stretch height
 */
public class StretchableInputLayout extends StretchableElementLayout
{
    private TextView m_label = null;
    private View m_inputView = null;
    private TextView m_errorMessage = null;

    public StretchableInputLayout(Context context, boolean mustStretch)
    {
        super(context, mustStretch);
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

        if (input instanceof ValidatedSpinnerLayout)
        {
            ValidatedSpinnerLayout layout = (ValidatedSpinnerLayout)input;
            m_inputView = layout.getChildAt(0);
        }
        else
        {
            m_inputView = input;
        }

        int viewId = (int)Util.getViewId(m_inputView);
        if (m_label != null)
        {
            m_label.setLabelFor(viewId);
        }
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
        if (m_inputView instanceof IValidatedInputView)
        {
            ((IValidatedInputView) m_inputView).setValidationResult(isValid);
        }

        if (m_label != null)
        {
            if (isValid)
            {
                m_label.setContentDescription(null);
            }
            else
            {
                m_label.setContentDescription(m_label.getText() + " " + m_errorMessage.getText());
            }
        }
    }
}
