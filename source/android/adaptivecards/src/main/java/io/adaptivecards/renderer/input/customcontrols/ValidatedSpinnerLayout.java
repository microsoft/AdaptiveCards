package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;

import io.adaptivecards.R;

public class ValidatedSpinnerLayout extends ValidatedInputLayout
{
    public ValidatedSpinnerLayout(Context context, int errorColor)
    {
        super(context, R.drawable.adaptive_choiceset_compact_background, errorColor);
    }
}
