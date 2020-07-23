package io.adaptivecards.renderer.input;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.widget.EditText;
import android.widget.LinearLayout;

import io.adaptivecards.renderer.inputhandler.TextInputHandler;

@SuppressLint("AppCompatCustomView")
public class ValidatedEditText extends EditText
{
    public ValidatedEditText(Context context) {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        getBackground().setColorFilter(null);
    }

    public ValidatedEditText(Context context, int errorColor) {
        this(context);
        m_errorColor = errorColor;
    }

    public void setValidationResult(boolean isValid)
    {
        if (isValid)
        {
            // Change border color to original color
            getBackground().setColorFilter(null);
        }
        else
        {
            // Change border to red
            getBackground().setColorFilter(m_errorColor, PorterDuff.Mode.SRC_ATOP);
        }
    }

    private int m_errorColor;
}
