// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.support.v4.content.ContextCompat;
import android.widget.LinearLayout;
import android.widget.RadioGroup;

import io.adaptivecards.R;

/**
 * ValidatedRadioGroup is an extension of RadioGroup that supports the usage of the adaptive_state_input_invalid
 * boolean flag defined in attrs.xml for using a custom background drawable
 */
public class ValidatedRadioGroup extends RadioGroup implements IValidatedInputView
{
    /**
     * Creates an instance of a ValidatedRadioGroup setting the background drawable adaptive_choiceset_expanded_background.
     * This constructor is necessary to have a constructor matching any of RadioGroup class constructors.
     * @param context Context necessary for UI object creation
     */
    private ValidatedRadioGroup(Context context)
    {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        setBackground(ContextCompat.getDrawable(context, R.drawable.adaptive_choiceset_expanded_background));
        setOrientation(RadioGroup.VERTICAL);

        m_isInvalid = false;
    }

    /**
     * Creates an instance of ValidatedRadioGroup.
     * @param context Context necessary for UI object creation
     * @param errorColor Color used for tinting the border outline of the RadioGroup
     */
    public ValidatedRadioGroup(Context context, int errorColor)
    {
        this(context);
        m_errorColor = errorColor;
    }

    /**
     * Updates the rendered edit text to display the error visual cues
     * @param isValid Value signalizing if input has valid value
     */
    @Override
    public void setValidationResult(boolean isValid)
    {
        setInputInvalid(!isValid);

        if (!isValid && getBackground() != null)
        {
            getBackground().setColorFilter(m_errorColor, PorterDuff.Mode.SRC_ATOP);
        }
        invalidate();
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
    private int m_errorColor = Color.TRANSPARENT;

    private static final int[] STATE_INPUT_INVALID = {R.attr.state_error};
}
