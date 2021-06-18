package io.adaptivecards.renderer.inputhandler;

import android.view.accessibility.AccessibilityEvent;
import android.widget.AutoCompleteTextView;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetInput;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.input.customcontrols.ValidatedInputLayout;

public class AutoCompleteTextViewHandler extends BaseInputHandler
{
    public AutoCompleteTextViewHandler(BaseInputElement baseInputElement)
    {
        super(baseInputElement);
    }

    protected AutoCompleteTextView getAutoCompleteTextView()
    {
        // For validation visual cues we draw the spinner inside a ValidatedSpinnerLayout so we query for this
        if (m_view instanceof ValidatedInputLayout)
        {
            return (AutoCompleteTextView) (((ValidatedInputLayout)m_view).getChildAt(0));
        }
        return (AutoCompleteTextView) m_view;
    }

    @Override
    public String getInput()
    {
        // To get the input, we have to transform the text inside of the AutoCompleteTextView into the value
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        return getValueForTitle(getAutoCompleteTextView().getEditableText().toString(), choiceSetInput.GetChoices());
    }

    @Override
    public void setInput(String value)
    {
        // To set the input, we have to transform the value received and set the according title into the AutoCompleteTextView
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        String title = getTitleForValue(value, choiceSetInput.GetChoices());
        getAutoCompleteTextView().setText(title);
    }

    @Override
    public void setFocusToView()
    {
        Util.forceFocus(m_view);
        m_view.sendAccessibilityEvent(AccessibilityEvent.TYPE_VIEW_ACCESSIBILITY_FOCUSED);
    }

    @Override
    public boolean isValidOnSpecifics(String inputValue)
    {
        ChoiceSetInput choiceSetInput = (ChoiceSetInput) m_baseInputElement;
        // if we can't find the title in the choice list, then the returned value is -1
        return (findTitleIndex(inputValue, choiceSetInput.GetChoices()) != -1);
    }

    protected interface ChoiceInputPropertyValueRetriever
    {
        String getPropertyValue(ChoiceInput choiceInput);
    }

    private int findIndexForChoiceInput(ChoiceInputVector choiceInputVector, String expectedValue, ChoiceInputPropertyValueRetriever retriever)
    {
        int index = -1;
        int choiceInputVectorSize = choiceInputVector.size();
        for (int i = 0; i < choiceInputVectorSize; ++i)
        {
            if (retriever.getPropertyValue(choiceInputVector.get(i)).equals(expectedValue))
            {
                index = i;
            }
        }
        return index;
    }

    private int findTitleIndex(String title, ChoiceInputVector choiceInputVector)
    {
        return findIndexForChoiceInput(choiceInputVector, title,
            (choiceInput) -> choiceInput.GetTitle());
    }

    private int findValueIndex(String value, ChoiceInputVector choiceInputVector)
    {
        return findIndexForChoiceInput(choiceInputVector, value,
            (choiceInput -> choiceInput.GetValue()));
    }

    private String findStringForIndex(int index, ChoiceInputVector choiceInputVector, ChoiceInputPropertyValueRetriever retriever)
    {
        String selectedItem = "";
        if (index >= 0 && index < choiceInputVector.size())
        {
            selectedItem = retriever.getPropertyValue(choiceInputVector.get(index));
        }
        return selectedItem;
    }

    private String getTitleForValue(String value, ChoiceInputVector choiceInputVector)
    {
        int index = findValueIndex(value, choiceInputVector);
        return findStringForIndex(index, choiceInputVector, (choiceInput -> choiceInput.GetTitle()));
    }

    private String getValueForTitle(String title, ChoiceInputVector choiceInputVector)
    {
        // Find index for the title
        int index = findTitleIndex(title, choiceInputVector);
        return findStringForIndex(index, choiceInputVector, (choiceInput -> choiceInput.GetValue()));
    }
}
