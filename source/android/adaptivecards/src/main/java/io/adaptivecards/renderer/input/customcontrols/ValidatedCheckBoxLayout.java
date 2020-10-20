package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;

import io.adaptivecards.R;

public class ValidatedCheckBoxLayout extends ValidatedInputLayout
{
    public ValidatedCheckBoxLayout(Context context, int errorColor)
    {
        super(context, R.drawable.adaptive_choiceset_expanded_background, errorColor);
    }
}
