// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.view.View;

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
        addView(input);
        m_inputView = input;
    }

    public View getErrorMessage()
    {
        return m_errorMessage;
    }

    public void setErrorMessage(View errorMessage)
    {
        addView(errorMessage);
        m_errorMessage = errorMessage;
    }

    private View m_label = null;
    private View m_inputView = null;
    private View m_errorMessage = null;
}
