// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler

import io.adaptivecards.objectmodel.BaseInputElement
import io.adaptivecards.renderer.inputhandler.BaseInputHandler
import android.widget.AutoCompleteTextView
import io.adaptivecards.renderer.input.customcontrols.ValidatedInputLayout
import io.adaptivecards.objectmodel.ChoiceSetInput
import android.view.accessibility.AccessibilityEvent
import io.adaptivecards.objectmodel.ChoiceInput
import io.adaptivecards.objectmodel.ChoiceInputVector
import io.adaptivecards.renderer.Util

class AutoCompleteTextViewHandler(baseInputElement: BaseInputElement?) : BaseInputHandler(baseInputElement) {
    // For validation visual cues we draw the spinner inside a ValidatedSpinnerLayout so we query for this
    protected val autoCompleteTextView: AutoCompleteTextView
        protected get() =// For validation visual cues we draw the spinner inside a ValidatedSpinnerLayout so we query for this
            if (m_view is ValidatedInputLayout) {
                (m_view as ValidatedInputLayout).getChildAt(0) as AutoCompleteTextView
            } else m_view as AutoCompleteTextView

    private var inputIsEmpty = false;

    override fun getInput(): String {
        // To get the input, we have to transform the text inside of the AutoCompleteTextView into the value
        val choiceSetInput = m_baseInputElement as ChoiceSetInput
        val inputText = autoCompleteTextView.editableText.toString()
        inputIsEmpty = inputText.isEmpty()
        return getValueForTitle(inputText, choiceSetInput.GetChoices())
    }

    override fun setInput(value: String) {
        // To set the input, we have to transform the value received and set the according title into the AutoCompleteTextView
        val choiceSetInput = m_baseInputElement as ChoiceSetInput
        val title = getTitleForValue(value, choiceSetInput.GetChoices())
        autoCompleteTextView.setText(title)
    }

    override fun setFocusToView() {
        Util.forceFocus(m_view)
        m_view.sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED)
    }

    override fun isValidOnSpecifics(inputValue: String): Boolean {
        // Before looking for the value we verify if the input was initially empty, if so the input is valid
        if (inputIsEmpty){
            return true;
        }

        val choiceSetInput = m_baseInputElement as ChoiceSetInput
        // if we can't find the title in the choice list, then the returned value is -1
        return findValueIndex(inputValue, choiceSetInput.GetChoices()) != -1
    }

    private fun findIndexForChoiceInput(choiceInputVector: ChoiceInputVector, expectedValue: String, retriever: (ChoiceInput) -> String): Int {
        var index = -1
        val choiceInputVectorSize = choiceInputVector.size
        for (i in 0 until choiceInputVectorSize) {
            if (retriever(choiceInputVector[i]) == expectedValue) {
                index = i
            }
        }
        return index
    }

    private fun findTitleIndex(title: String, choiceInputVector: ChoiceInputVector): Int {
        return findIndexForChoiceInput(choiceInputVector, title, { choiceInput: ChoiceInput -> choiceInput.GetTitle() })
    }

    private fun findValueIndex(value: String, choiceInputVector: ChoiceInputVector): Int {
        return findIndexForChoiceInput(choiceInputVector, value, { choiceInput: ChoiceInput -> choiceInput.GetValue() })
    }

    private fun findStringForIndex(index: Int, choiceInputVector: ChoiceInputVector, retriever: (ChoiceInput) -> String): String {
        var selectedItem = ""
        if (index >= 0 && index < choiceInputVector.size) {
            selectedItem = retriever(choiceInputVector[index])
        }
        return selectedItem
    }

    private fun getTitleForValue(value: String, choiceInputVector: ChoiceInputVector): String {
        val index = findValueIndex(value, choiceInputVector)
        return findStringForIndex(index, choiceInputVector, { choiceInput: ChoiceInput -> choiceInput.GetTitle() })
    }

    private fun getValueForTitle(title: String, choiceInputVector: ChoiceInputVector): String {
        // Find index for the title
        val index = findTitleIndex(title, choiceInputVector)
        return findStringForIndex(index, choiceInputVector, { choiceInput: ChoiceInput -> choiceInput.GetValue() })
    }
}
