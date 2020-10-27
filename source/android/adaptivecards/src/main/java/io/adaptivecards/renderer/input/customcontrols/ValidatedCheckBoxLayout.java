// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input.customcontrols;

import android.content.Context;

import io.adaptivecards.R;

/**
 * ValidatedCheckBoxLayout is an extension of ValidatedInputLayout that rules the behaviour for
 * CheckBox collections.
 */
public class ValidatedCheckBoxLayout extends ValidatedInputLayout
{
    /**
     * Creates an instance of ValidatedCheckBoxLayout.
     * @param context Context necessary for UI object creation
     * @param errorColor Color used for tinting the border outline of the layout containing the CheckBoxes
     */
    public ValidatedCheckBoxLayout(Context context, int errorColor)
    {
        super(context, R.drawable.adaptive_choiceset_expanded_background, errorColor);
    }
}
