package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.widget.TextView;
import io.adaptivecards.renderer.inputhandler.validation.IInputValidator;

public class StretchableInputLayout extends StretchableElementLayout
{
    public StretchableInputLayout(Context context)
    {
        super(context);
    }

    private TextView m_failLabel = null;

    private IInputValidator m_inputValidator = null;
}
