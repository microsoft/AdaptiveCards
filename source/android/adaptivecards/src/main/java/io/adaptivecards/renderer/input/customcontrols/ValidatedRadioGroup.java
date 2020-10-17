package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.support.v4.content.ContextCompat;
import android.widget.LinearLayout;
import android.widget.RadioGroup;

import io.adaptivecards.R;

public class ValidatedRadioGroup extends RadioGroup implements IValidatedInputView
{

    public ValidatedRadioGroup(Context context)
    {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        setBackground(ContextCompat.getDrawable(context, R.drawable.adaptive_choiceset_expanded_background));
        setOrientation(RadioGroup.VERTICAL);

        m_isInvalid = false;
    }

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

    private static final int[] STATE_INPUT_INVALID = {R.attr.adaptive_state_input_invalid};
}
