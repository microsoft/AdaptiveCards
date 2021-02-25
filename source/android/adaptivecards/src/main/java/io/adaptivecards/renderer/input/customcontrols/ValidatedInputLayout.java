// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.support.v4.content.ContextCompat;
import android.widget.LinearLayout;

import io.adaptivecards.R;

/**
 * ValidatedSpinnerLayout is an extension of the LinearLayout control that is used to contain multiple
 * visual elements. LinearLayouts are used to contain CheckBoxes for multichoice extended ChoiceSet
 * elements and Spinners as they are a special case of input elements that already have a background drawable
 */
public class ValidatedInputLayout extends LinearLayout implements IValidatedInputView
{
    /**
     * Creates an instance of a ValidatedInputLayout. This constructor is necessary to have a
     * constructor matching any of LinearLayout class constructors.
     * @param context Context necessary for UI object creation
     */
    private ValidatedInputLayout(Context context)
    {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        setOrientation(VERTICAL);
        m_isInvalid = false;
    }

    /**
     * Creates an instance of ValidatedInputLayout.
     * @param context Context necessary for UI object creation
     * @param drawableId Drawable numeric identifier, ie. R.drawable.some_drawable
     * @param errorColor Color used for tinting the border outline of the Layout
     */
    public ValidatedInputLayout(Context context, int drawableId, int errorColor)
    {
        this(context);
        setBackground(ContextCompat.getDrawable(context, drawableId));
        m_errorColor = errorColor;
    }

    /**
     * Updates the rendered edit text to display the error visual cues
     * @param isValid Value signalizing if input has valid value
     */
    public void setValidationResult(boolean isValid)
    {
        setInputInvalid(!isValid);

        if (!isValid)
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
