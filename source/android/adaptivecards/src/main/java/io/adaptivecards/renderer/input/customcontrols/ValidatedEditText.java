// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input.customcontrols;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.util.TypedValue;
import android.widget.EditText;
import android.widget.LinearLayout;

import io.adaptivecards.R;

/**
 * ValidatedEditText is an extension of EditText that supports the usage of the adaptive_state_input_invalid
 * boolean flag defined in attrs.xml for using a custom background drawable or element color tinting.
 */
@SuppressLint("AppCompatCustomView")
public class ValidatedEditText extends EditText implements IValidatedInputView
{
    /**
     * Creates an instance of a ValidatedEditText and verifies if custom drawables are being used.
     * This constructor is necessary to have a constructor matching any of EditText class constructors.
     * @param context Context necessary for UI object creation
     */
    private ValidatedEditText(Context context)
    {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        m_isInvalid = false;
        verifyIfUsingCustomInputs(context);
    }

    /**
     * Creates an instance of ValidatedEditText.
     * @param context Context necessary for UI object creation
     * @param errorColor Color used for tinting the border outline of the EditText
     */
    public ValidatedEditText(Context context, int errorColor)
    {
        this(context);
        m_errorColor = errorColor;
    }

    /**
     * Peeks the usingCustomInputs attribute in the style to verify if custom inputs are being used
     * @param context Context to retrieve the value from
     */
    public void verifyIfUsingCustomInputs(Context context)
    {
        Resources.Theme theme = context.getTheme();
        TypedValue isUsingCustomInputs = new TypedValue();

        if (theme.resolveAttribute(R.attr.adaptiveUsingCustomTextInputs, isUsingCustomInputs, true))
        {
            m_isUsingCustomInputs = (isUsingCustomInputs.data != 0);
        }
        else
        {
            m_isUsingCustomInputs = false;
        }
    }

    /**
     * Updates the rendered edit text to display the error visual cues
     * @param isValid Value signalizing if input has valid value
     */
    public void setValidationResult(boolean isValid)
    {
        if (m_isUsingCustomInputs)
        {
            // If using custom inputs, set the selector state for state_input_invalid as true
            setInputInvalid(!isValid);
        }
        else
        {
            // If not using custom inputs, tint the whole input with attention color
            if (isValid)
            {
                getBackground().setColorFilter(null);
            }
            else
            {
                getBackground().setColorFilter(m_errorColor, PorterDuff.Mode.SRC_ATOP);
            }
            invalidate();
        }
    }

    /**
     * Refreshes the visual selector state for valid or invalid style
     * @param isInvalid Value signalizing if the input has failed validation
     */
    public void setInputInvalid(boolean isInvalid)
    {
        m_isInvalid = isInvalid;
        refreshDrawableState();
    }

    /**
     * Updates the possible states to be available for this visual element by adding the
     * adaptive_state_input_invalid state
     * @param extraSpace
     * @return An array that contains the original states and the new state added
     */
    @Override
    protected int[] onCreateDrawableState(int extraSpace)
    {
        final int[] drawableState = super.onCreateDrawableState(extraSpace + 1);
        if (m_isInvalid)
        {
            mergeDrawableStates(drawableState, STATE_INPUT_INVALID);
        }

        return drawableState;
    }

    private boolean m_isInvalid = false;
    private boolean m_isUsingCustomInputs = false;
    private int m_errorColor = Color.TRANSPARENT;

    private static final int[] STATE_INPUT_INVALID = {R.attr.state_error};
}
