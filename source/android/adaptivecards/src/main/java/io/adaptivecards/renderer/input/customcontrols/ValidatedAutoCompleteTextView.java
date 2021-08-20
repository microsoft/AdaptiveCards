// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;
import android.content.res.Resources;
import android.util.TypedValue;
import android.widget.LinearLayout;

import androidx.appcompat.widget.AppCompatAutoCompleteTextView;
import androidx.core.content.ContextCompat;

import io.adaptivecards.R;

/**
 * ValidatedAutoCompleteTextView is an extension of AutoCompleteTextView that supports the usage of
 * the adaptive_state_input_invalid boolean flag defined in attrs.xml for using a custom background drawable
 */
public class ValidatedAutoCompleteTextView extends AppCompatAutoCompleteTextView implements IValidatedInputView
{
    /**
     * Creates an instance of a ValidatedAutoCompleteTextView and verifies if custom drawables are being used.
     * @param context Context necessary for UI object creation
     */
    public ValidatedAutoCompleteTextView(Context context)
    {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        m_isInvalid = false;
        verifyIfUsingCustomInputs(context);
    }

    /**
     * Creates an instance of a ValidatedAutoCompleteTextView setting the background drawable adaptive_choiceset_compact_background.
     * @param context Context necessary for UI object creation
     * @param usingCustomInputs Flag signalizing if a custom drawable is being used
     */
    public ValidatedAutoCompleteTextView(Context context, boolean usingCustomInputs)
    {
        this(context);
        m_isUsingCustomInputs = usingCustomInputs;
        if (m_isUsingCustomInputs)
        {
            setBackground(ContextCompat.getDrawable(context, R.drawable.adaptive_choiceset_compact_background));
        }
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

    private static final int[] STATE_INPUT_INVALID = {R.attr.state_error};
}
