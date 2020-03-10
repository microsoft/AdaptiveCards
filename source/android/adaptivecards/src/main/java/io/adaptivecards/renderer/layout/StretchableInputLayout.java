package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.widget.TextView;

public class StretchableInputLayout extends StretchableElementLayout
{
    public StretchableInputLayout(Context context)
    {
        super(context);
    }



    private TextView m_failLabel = null;

    private IInputValidator m_inputValidator = null;
    private IInputIsRequiredValidator m_isRequiredValidator = null;
}
