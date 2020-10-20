package io.adaptivecards.renderer.input.customcontrols;

import android.annotation.SuppressLint;
import android.content.Context;
import android.content.res.Resources;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.support.v4.content.ContextCompat;
import android.util.TypedValue;
import android.widget.LinearLayout;
import android.widget.Spinner;

import io.adaptivecards.R;

@SuppressLint("AppCompatCustomView")
public class ValidatedSpinner extends Spinner implements IValidatedInputView
{
    public ValidatedSpinner(Context context)
    {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        m_isInvalid = false;
        verifyIfUsingCustomInputs(context);
    }

    public ValidatedSpinner(Context context, boolean usingCustomInputs)
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

    private static final int[] STATE_INPUT_INVALID = {R.attr.adaptive_state_input_invalid};

}
