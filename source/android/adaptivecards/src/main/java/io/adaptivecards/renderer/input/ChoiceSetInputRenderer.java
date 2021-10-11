// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import android.content.res.Resources;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.FragmentManager;

import android.os.Build;
import android.text.TextUtils;
import android.util.TypedValue;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.Filter;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.TextView;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetStyle;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.input.customcontrols.ValidatedAutoCompleteTextView;
import io.adaptivecards.renderer.input.customcontrols.ValidatedCheckBoxLayout;
import io.adaptivecards.renderer.input.customcontrols.ValidatedInputLayout;
import io.adaptivecards.renderer.input.customcontrols.ValidatedRadioGroup;
import io.adaptivecards.renderer.input.customcontrols.ValidatedSpinner;
import io.adaptivecards.renderer.input.customcontrols.ValidatedSpinnerLayout;
import io.adaptivecards.renderer.inputhandler.AutoCompleteTextViewHandler;
import io.adaptivecards.renderer.inputhandler.CheckBoxSetInputHandler;
import io.adaptivecards.renderer.inputhandler.ComboBoxInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ChoiceSetInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.inputhandler.RadioGroupInputHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Vector;
import java.util.function.Predicate;
import java.util.stream.Collectors;

public class ChoiceSetInputRenderer extends BaseCardElementRenderer
{
    protected ChoiceSetInputRenderer()
    {
    }

    public boolean isUsingCustomInputs(Context context)
    {
        Resources.Theme theme = context.getTheme();
        TypedValue isUsingCustomInputs = new TypedValue();

        if (theme.resolveAttribute(R.attr.adaptiveUsingCustomChoiceSetInputs, isUsingCustomInputs, true))
        {
            return (isUsingCustomInputs.data != 0);
        }
        else
        {
            return false;
        }
    }

    public static ChoiceSetInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ChoiceSetInputRenderer();
        }

        return s_instance;
    }

    public static class FocusableChoiceListener<T extends CompoundButton> implements View.OnTouchListener
    {
        public FocusableChoiceListener(T firstView)
        {
            m_firstView = firstView;
        }

        @Override
        public boolean onTouch(View view, MotionEvent motionEvent)
        {
            if (motionEvent.getAction() == MotionEvent.ACTION_UP)
            {
                m_firstView.setFocusableInTouchMode(false);
                m_firstView.clearFocus();

                T clickableElement = (T) view;
                // Checkboxes must change their values to the opposite one, radio buttons must always turn on
                if (clickableElement instanceof CheckBox)
                {
                    clickableElement.setChecked(!clickableElement.isChecked());
                }
                else
                {
                    clickableElement.setChecked(true);
                }

            }
            return true;
        }

        private T m_firstView;
    }

    public View renderCheckBoxSet(
                RenderedAdaptiveCard renderedCard,
                Context context,
                ChoiceSetInput choiceSetInput,
                HostConfig hostConfig,
                RenderArgs renderArgs)
    {
        ValidatedCheckBoxLayout checkBoxLayout = new ValidatedCheckBoxLayout(context,
                                                                             getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Attention, false)));

        List<CheckBox> checkBoxList = new Vector<CheckBox>();
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        long size = choiceInputVector.size();

        String value = choiceSetInput.GetValue();
        Vector<String> defaults = new Vector<>();
        defaults.addAll(Arrays.asList(value.split(",")));
        final CheckBoxSetInputHandler checkBoxSetInputHandler = new CheckBoxSetInputHandler(choiceSetInput, checkBoxList);
        checkBoxSetInputHandler.setView(checkBoxLayout);

        checkBoxLayout.setTag(new TagContent(choiceSetInput, checkBoxSetInputHandler));

        for (int i = 0; i < size; i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);
            final CheckBox checkBox = new CheckBox(context);
            checkBox.setText(choiceInput.GetTitle());

            if (!choiceSetInput.GetWrap())
            {
                checkBox.setMaxLines(1);
                checkBox.setEllipsize(TextUtils.TruncateAt.END);
            }

            if (defaults.contains(choiceInput.GetValue()))
            {
                checkBox.setChecked(true);
            }
            checkBoxList.add(checkBox);
            checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
            {
                @Override
                public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
                {
                    CardRendererRegistration.getInstance().notifyInputChange(checkBoxSetInputHandler.getId(), checkBoxSetInputHandler.getInput());
                }
            });

            // Only for the first checkbox we'll add some extra behaviour as it's going to be the element to receive focus
            // When validation fails we'll set the first checkbox with focusableInTouchMode = true, this makes the clicking
            // inconsistent as it needs two clicks to check/uncheck, so once it's clicked, we'll remove the property to false
            // and check/uncheck the box ourselves
            checkBox.setOnTouchListener(new FocusableChoiceListener<CheckBox>(checkBoxList.get(0)));

            checkBoxLayout.addView(checkBox);
        }

        renderedCard.registerInputHandler(checkBoxSetInputHandler, renderArgs.getContainerCardId());
        return checkBoxLayout;
    }

    public View renderRadioGroup(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ChoiceSetInput choiceSetInput,
            HostConfig hostConfig,
            RenderArgs renderArgs)
    {
        ValidatedRadioGroup radioGroup = new ValidatedRadioGroup(context,
                                                                 getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Attention, false)));

        final RadioGroupInputHandler radioGroupInputHandler = new RadioGroupInputHandler(choiceSetInput);
        radioGroupInputHandler.setView(radioGroup);
        radioGroup.setTag(new TagContent(choiceSetInput, radioGroupInputHandler));

        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        long size = choiceInputVector.size();
        String value = choiceSetInput.GetValue();

        for (int i = 0; i < size; i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);
            RadioButton radioButton = new RadioButton(context);
            radioButton.setId(i);

            if(!choiceSetInput.GetWrap())
            {
                radioButton.setMaxLines(1);
                radioButton.setEllipsize(TextUtils.TruncateAt.END);
            }

            radioButton.setText(choiceInput.GetTitle());
            if (choiceInput.GetValue().equals(value))
            {
                radioButton.setChecked(true);
            }

            radioGroup.addView(radioButton);

            radioButton.setOnTouchListener(new FocusableChoiceListener<RadioButton>((RadioButton) radioGroup.getChildAt(0)));
        }
        renderedCard.registerInputHandler(radioGroupInputHandler, renderArgs.getContainerCardId());
        radioGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId)
            {
                CardRendererRegistration.getInstance().notifyInputChange(radioGroupInputHandler.getId(), radioGroupInputHandler.getInput());
            }
        });

        return radioGroup;
    }

    public View renderComboBox(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ChoiceSetInput choiceSetInput,
            HostConfig hostConfig,
            RenderArgs renderArgs)
    {
        final Vector<String> titleList = new Vector<>();
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        long size = choiceInputVector.size();
        int selection = 0;
        String value = choiceSetInput.GetValue();

        for (int i = 0; i < size; i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);

            titleList.addElement(choiceInput.GetTitle());
            if (choiceInput.GetValue().equals(value))
            {
                selection = i;
            }
        }

        // If the default value is empty, then create an empty option at the end to avoid any mess
        // with indexes
        boolean hasEmptyDefault = value.isEmpty();
        if (hasEmptyDefault)
        {
            // Android has an undocumented behaviour where a spinner with an empty option selected
            // will not receive accessibility focus, if we add an single space ' ' then the spinner
            // can receive focus.
            String placeholder = choiceSetInput.GetPlaceholder();
            if (placeholder.isEmpty())
            {
                placeholder = " ";
            }
            titleList.addElement(placeholder);

            selection = (int) size;
        }

        boolean usingCustomInputs = isUsingCustomInputs(context);
        final Spinner spinner = new ValidatedSpinner(context, usingCustomInputs);

        final ComboBoxInputHandler comboBoxInputHandler = new ComboBoxInputHandler(choiceSetInput);

        boolean isRequired = choiceSetInput.GetIsRequired();
        ValidatedInputLayout inputLayout = null;

        // if using custom inputs, we don't have to create the surrounding linear layout
        boolean needsOuterLayout = (isRequired && !usingCustomInputs);
        if (needsOuterLayout)
        {
            inputLayout = new ValidatedSpinnerLayout(context,
                                                     getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Attention, false)));
            inputLayout.setTag(new TagContent(choiceSetInput, comboBoxInputHandler));
            comboBoxInputHandler.setView(inputLayout);
        }
        else
        {
            spinner.setTag(new TagContent(choiceSetInput, comboBoxInputHandler));
            comboBoxInputHandler.setView(spinner);
        }
        renderedCard.registerInputHandler(comboBoxInputHandler, renderArgs.getContainerCardId());

        class TextSpinnerAdapter extends ArrayAdapter<String>
        {
            TextSpinnerAdapter(Context context, int resource,
                               Vector<String> items, boolean hasEmptyDefault)
            {
                super(context, resource, items);
                m_hasEmptyDefault = hasEmptyDefault;
                m_itemCount = items.size();
            }

            public int getCount()
            {
                if (m_hasEmptyDefault)
                {
                    return m_itemCount - 1;
                }
                else
                {
                    return m_itemCount;
                }
            }

            private int m_itemCount = 0;
            private boolean m_hasEmptyDefault = false;
        }

        class WrappedTextSpinnerAdapter extends TextSpinnerAdapter
        {
            WrappedTextSpinnerAdapter(Context context, int resource,
                                      Vector<String> items, boolean hasEmptyDefault)
            {
                super(context, resource, items, hasEmptyDefault);
            }

            @NonNull
            @Override
            // getView returns the view when spinner is not selected
            // override method disables single line setting
            public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent)
            {
                View view = super.getView(position, convertView, parent);
                TextView txtView = view.findViewById(android.R.id.text1);
                txtView.setSingleLine(false);
                return view;
            }
        }

        ArrayAdapter<String> spinnerArrayAdapter;
        if (choiceSetInput.GetWrap())
        {
            spinnerArrayAdapter = new WrappedTextSpinnerAdapter(context, android.R.layout.simple_spinner_item, titleList, hasEmptyDefault);
        }
        else
        {
            spinnerArrayAdapter = new TextSpinnerAdapter(context, android.R.layout.simple_spinner_item, titleList, hasEmptyDefault);
        }

        spinnerArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(spinnerArrayAdapter);

        spinner.setSelection(selection);
        spinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
            {
                CardRendererRegistration.getInstance().notifyInputChange(comboBoxInputHandler.getId(), comboBoxInputHandler.getInput());
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent)
            {
                CardRendererRegistration.getInstance().notifyInputChange(comboBoxInputHandler.getId(), comboBoxInputHandler.getInput());
            }
        });

        spinner.setFocusable(true);

        if (needsOuterLayout)
        {
            inputLayout.addView(spinner);
            return inputLayout;
        }
        else
        {
            return spinner;
        }
    }

    public View renderFilteredComboBox(
        RenderedAdaptiveCard renderedCard,
        Context context,
        ChoiceSetInput choiceSetInput,
        HostConfig hostConfig,
        RenderArgs renderArgs)
    {
        final Vector<String> titleList = new Vector<>();
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        long size = choiceInputVector.size();
        int valueIndex = -1;
        String value = choiceSetInput.GetValue();

        for (int i = 0; i < size; i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);
            titleList.addElement(choiceInput.GetTitle());

            if (choiceInput.GetValue().equals(value))
            {
                valueIndex = i;
            }
        }

        boolean usingCustomInputs = isUsingCustomInputs(context);
        final AutoCompleteTextView autoCompleteTextView = new ValidatedAutoCompleteTextView(context, usingCustomInputs);
        autoCompleteTextView.setThreshold(0);

        final AutoCompleteTextViewHandler autoCompleteTextInputHandler = new AutoCompleteTextViewHandler(choiceSetInput);

        boolean isRequired = choiceSetInput.GetIsRequired();
        ValidatedInputLayout inputLayout = null;

        // if using custom inputs, we don't have to create the surrounding linear layout
        boolean needsOuterLayout = (!usingCustomInputs);
        if (needsOuterLayout)
        {
            inputLayout = new ValidatedSpinnerLayout(context,
                getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Attention, false)));
            inputLayout.setTag(new TagContent(choiceSetInput, autoCompleteTextInputHandler));
            autoCompleteTextInputHandler.setView(inputLayout);
        }
        else
        {
            autoCompleteTextView.setTag(new TagContent(choiceSetInput, autoCompleteTextInputHandler));
            autoCompleteTextInputHandler.setView(autoCompleteTextView);
        }
        renderedCard.registerInputHandler(autoCompleteTextInputHandler, renderArgs.getContainerCardId());

        class FilteredChoiceSetAdapter extends ArrayAdapter<String>
        {
            boolean m_mustWrap = false;

            // m_items contains the items currently being displayed as suggestions
            // m_originalItemsList contains the items provided by the card author when the element was created
            List<String> m_items, m_originalItemsList;

            FilteredChoiceSetAdapter(Context context, int resource,
                                     Vector<String> items, boolean mustWrap)
            {
                super(context, resource, items);
                m_mustWrap = mustWrap;
                m_items = items;
                m_originalItemsList = new ArrayList<>(items);
            }

            @Override
            public int getCount()
            {
                return m_items.size();
            }

            @Override
            public String getItem(int pos)
            {
                return m_items.get(pos);
            }

            @NonNull
            @Override
            // getView returns the view when spinner is not selected
            // override method disables single line setting
            public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent)
            {
                View view = super.getView(position, convertView, parent);
                TextView txtView = view.findViewById(android.R.id.text1);

                if (m_mustWrap)
                {
                    txtView.setSingleLine(false);
                }

                return view;
            }

            @NonNull
            @Override
            public Filter getFilter() {
                return m_substringFilter;
            }

            Filter m_substringFilter = new Filter() {

                @Override
                protected FilterResults performFiltering(CharSequence constraint) {

                    FilterResults filterResults = new FilterResults();

                    // Due to the time it takes for evaluating all options, this part of the code has
                    // to be synchronized, otherwise the worker thread that calls the publishResults
                    // function will throw an illegalstateexception or a concurrentmodificationexception
                    synchronized (filterResults)
                    {
                        List<String> filteredSuggestions = new ArrayList<>();

                        // isEmpty compares against null and 0-length strings
                        if (!TextUtils.isEmpty(constraint))
                        {
                            String lowerCaseConstraint = constraint.toString().toLowerCase();

                            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N)
                            {
                                Predicate<String> bySubstring = choice -> choice.toLowerCase().contains(lowerCaseConstraint);
                                filteredSuggestions = m_originalItemsList.stream().filter(bySubstring).collect(Collectors.toList());
                            }
                            else
                            {
                                for (String choice : m_originalItemsList)
                                {
                                    if (choice.toLowerCase().contains(lowerCaseConstraint))
                                    {
                                        filteredSuggestions.add(choice);
                                    }
                                }
                            }
                        }
                        else
                        {
                            filteredSuggestions = m_originalItemsList;
                        }

                        filterResults.values = filteredSuggestions;
                        filterResults.count = filteredSuggestions.size();

                        return filterResults;
                    }
                }

                @Override
                protected void publishResults(CharSequence constraint, FilterResults filterResults)
                {
                    if (filterResults != null && filterResults.count > 0)
                    {
                        m_items = (ArrayList<String>) filterResults.values;
                        notifyDataSetChanged();
                    }
                    else
                    {
                        notifyDataSetInvalidated();
                    }
                }
            };

        }

        autoCompleteTextView.setAdapter(new FilteredChoiceSetAdapter(context,
                                            android.R.layout.select_dialog_item,
                                            titleList,
                                            choiceSetInput.GetWrap()));
        autoCompleteTextView.setFocusable(true);
        if (valueIndex != -1)
        {
            autoCompleteTextView.setText(titleList.get(valueIndex));
        }

        autoCompleteTextView.setOnTouchListener(new View.OnTouchListener(){
            @Override
            public boolean onTouch(View v, MotionEvent event){
                autoCompleteTextView.showDropDown();
                return false;
            }
        });

        autoCompleteTextView.setOnKeyListener(new View.OnKeyListener() {
            @Override
            public boolean onKey(View view, int i, KeyEvent keyEvent) {
                autoCompleteTextView.showDropDown();
                return false;
            }
        });

        autoCompleteTextView.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
            {
                CardRendererRegistration.getInstance().notifyInputChange(autoCompleteTextInputHandler.getId(), autoCompleteTextInputHandler.getInput());
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent)
            {
                CardRendererRegistration.getInstance().notifyInputChange(autoCompleteTextInputHandler.getId(), autoCompleteTextInputHandler.getInput());
            }
        });

        if (needsOuterLayout)
        {
            inputLayout.addView(autoCompleteTextView);
            return inputLayout;
        }
        else
        {
            return autoCompleteTextView;
        }
    }


    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.ChoiceSet is not allowed"));
            return null;
        }

        ChoiceSetInput choiceSetInput = Util.castTo(baseCardElement, ChoiceSetInput.class);

        View inputView = null;
        if (choiceSetInput.GetIsMultiSelect())
        {
            // Create multi-select checkbox
            inputView = renderCheckBoxSet(renderedCard, context, choiceSetInput, hostConfig, renderArgs);
        }
        else
        {
            if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Expanded)
            {
                // Create radio button group
                inputView = renderRadioGroup(renderedCard, context, choiceSetInput, hostConfig, renderArgs);
            }
            else if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Compact)
            {
                // create ComboBox (Spinner)
                inputView = renderComboBox(renderedCard, context, choiceSetInput, hostConfig, renderArgs);
            }
            else if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Filtered)
            {
                inputView = renderFilteredComboBox(renderedCard, context, choiceSetInput, hostConfig, renderArgs);
            }
            else
            {
                throw new IllegalArgumentException("ChoiceSet Input, " + choiceSetInput.GetId() + ", contains invalid style, " + choiceSetInput.GetChoiceSetStyle().toString() + ".");
            }
        }

        viewGroup.addView(inputView);

        return inputView;
    }

    private static ChoiceSetInputRenderer s_instance = null;
}
