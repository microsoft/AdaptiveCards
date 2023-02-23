// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input.customcontrols

import android.content.Context
import android.util.TypedValue
import android.view.View
import android.widget.LinearLayout
import androidx.appcompat.widget.AppCompatTextView
import androidx.core.content.ContextCompat
import io.adaptivecards.R


class ValidatedTextView(context: Context, usingCustomInputs: Boolean) : AppCompatTextView(context), IValidatedInputView {

    private var mIsInvalid = false
    private var mIsUsingCustomInputs = false

    private val STATE_INPUT_INVALID = intArrayOf(R.attr.state_error)

    /**
     * Creates an instance of a ValidatedSpinner setting the background drawable adaptive_choiceset_compact_background.
     * @param context Context necessary for UI object creation
     * @param usingCustomInputs Flag signalizing if a custom drawable is being used
     */
    init {
        layoutParams = LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT)
        mIsInvalid = false
        verifyIfUsingCustomInputs(context)
        mIsUsingCustomInputs = usingCustomInputs
        if (mIsUsingCustomInputs) {
            background = ContextCompat.getDrawable(context, R.drawable.adaptive_choiceset_compact_background)
        }
    }

    /**
     * Peeks the usingCustomInputs attribute in the style to verify if custom inputs are being used
     * @param context Context to retrieve the value from
     */
    fun verifyIfUsingCustomInputs(context: Context) {
        val theme = context.theme
        val isUsingCustomInputs = TypedValue()
        mIsUsingCustomInputs = if (theme.resolveAttribute(
                R.attr.adaptiveUsingCustomTextInputs,
                isUsingCustomInputs,
                true
            )
        ) {
            isUsingCustomInputs.data != 0
        } else {
            false
        }
    }

    /**
     * Updates the rendered edit text to display the error visual cues
     * @param isValid Value signalizing if input has valid value
     */
    override fun setValidationResult(isValid: Boolean) {
        if (mIsUsingCustomInputs) {
            // If using custom inputs, set the selector state for state_input_invalid as true
            setInputInvalid(!isValid)
        }
    }

    /**
     * Refreshes the visual selector state for valid or invalid style
     * @param isInvalid Value signalizing if the input has failed validation
     */
    fun setInputInvalid(isInvalid: Boolean) {
        mIsInvalid = isInvalid
        refreshDrawableState()
    }

    /**
     * Updates the possible states to be available for this visual element by adding the
     * adaptive_state_input_invalid state
     * @param extraSpace
     * @return An array that contains the original states and the new state added
     */
    protected override fun onCreateDrawableState(extraSpace: Int): IntArray? {
        val drawableState: IntArray = super.onCreateDrawableState(extraSpace + 1)
        if (mIsInvalid) {
            View.mergeDrawableStates(drawableState, STATE_INPUT_INVALID)
        }
        return drawableState
    }
}