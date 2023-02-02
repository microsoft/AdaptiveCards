// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler

import io.adaptivecards.objectmodel.BaseInputElement
import io.adaptivecards.renderer.input.customcontrols.ValidatedInputLayout
import android.view.accessibility.AccessibilityEvent
import io.adaptivecards.renderer.Util
import io.adaptivecards.renderer.input.customcontrols.ValidatedTextView

class TypeAheadTextViewHandler(baseInputElement: BaseInputElement?) : BaseInputHandler(baseInputElement) {
    // For validation visual cues we draw the spinner inside a ValidatedSpinnerLayout so we query for this
    protected val editTextView: ValidatedTextView
        protected get() =// For validation visual cues we draw the spinner inside a ValidatedSpinnerLayout so we query for this
            if (m_view is ValidatedInputLayout) {
                (m_view as ValidatedInputLayout).getChildAt(0) as ValidatedTextView
            } else m_view as ValidatedTextView

    private var inputIsEmpty = false
    private var inputValue: String = ""

    override fun getInput(): String {
        val inputText = editTextView.toString()
        inputIsEmpty = inputText.isEmpty()
        return inputValue
    }

    override fun setInput(value: String) {
        inputValue = value
    }

    fun setInput(title: String, value: String) {
        editTextView.text = title
        input = value
    }

    fun getInputTitle(): String {
        return editTextView.text.toString()
    }

    override fun setFocusToView() {
        Util.forceFocus(m_view)
        m_view.sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED)
    }

    override fun isValidOnSpecifics(inputValue: String): Boolean = !inputIsEmpty
}
