// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

package io.adaptivecards.renderer.input.customcontrols;

/**
 * IValidatedInputView is the interface base class for all views that should trigger a visual cue
 * when validation fails.
*/
public interface IValidatedInputView
{
    /**
     * Sets the validation result to the view so it can update the visual cue
     * @param isValid boolean flag that specifies if validation succeeded
     */
    void setValidationResult(boolean isValid);
}
