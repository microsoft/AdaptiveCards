// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;

import io.adaptivecards.R;

/**
 * ValidatedSpinnerLayout is an extension of ValidatedInputLayout that rules the behaviour for
 * Spinners. Spinners are a special case of input elements as they already have a background drawable
 * for defining their shape, so the only option found for drawing an attention color border while
 * keeping the original Spinner drawable was enclosing the latter inside a Layout.
 */
public class ValidatedSpinnerLayout extends ValidatedInputLayout
{
    /**
     * Creates an instance of ValidatedCheckBoxLayout.
     * @param context Context necessary for UI object creation
     * @param errorColor Color used for tinting the border outline of the layout containing the CheckBoxes
     */
    public ValidatedSpinnerLayout(Context context, int errorColor)
    {
        super(context, R.drawable.adaptive_choiceset_compact_background, errorColor);
    }
}
