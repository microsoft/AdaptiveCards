// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import android.graphics.Color;
import android.graphics.PorterDuff;
import android.opengl.Visibility;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;
import android.widget.TextView;

import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetStyle;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.IsVisible;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.BaseInputHandler;
import io.adaptivecards.renderer.inputhandler.CheckBoxSetInputHandler;
import io.adaptivecards.renderer.inputhandler.ComboBoxInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ChoiceSetInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.renderer.inputhandler.RadioGroupInputHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.Arrays;
import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

public class ChoiceSetInputRenderer extends BaseCardElementRenderer
{
    protected ChoiceSetInputRenderer()
    {
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
                RenderArgs renderArgs)
    {
        LinearLayout layout = new LinearLayout(context);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        layout.setOrientation(LinearLayout.VERTICAL);

        List<CheckBox> checkBoxList = new Vector<CheckBox>();
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        long size = choiceInputVector.size();

        String value = choiceSetInput.GetValue();
        Vector<String> defaults = new Vector<>();
        defaults.addAll(Arrays.asList(value.split(",")));
        final CheckBoxSetInputHandler checkBoxSetInputHandler = new CheckBoxSetInputHandler(choiceSetInput, checkBoxList);
        checkBoxSetInputHandler.setView(layout);

        layout.setTag(new TagContent(choiceSetInput, checkBoxSetInputHandler));

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

            layout.addView(checkBox);
        }

        renderedCard.registerInputHandler(checkBoxSetInputHandler, renderArgs.getContainerCardId());
        return layout;
    }

    public View renderRadioGroup(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ChoiceSetInput choiceSetInput,
            RenderArgs renderArgs)
    {
        RadioGroup radioGroup = new RadioGroup(context);
        final RadioGroupInputHandler radioGroupInputHandler = new RadioGroupInputHandler(choiceSetInput);
        radioGroupInputHandler.setView(radioGroup);

        radioGroup.setTag(new TagContent(choiceSetInput, radioGroupInputHandler));

        radioGroup.setOrientation(RadioGroup.VERTICAL);
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
            titleList.addElement(choiceSetInput.GetPlaceholder());
            selection = (int)size;
        }

        final ComboBoxInputHandler comboBoxInputHandler = new ComboBoxInputHandler(choiceSetInput);
        final Spinner spinner = new Spinner(context);
        spinner.getBackground().setColorFilter(Color.RED, PorterDuff.Mode.SRC_ATOP);
        spinner.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        comboBoxInputHandler.setView(spinner);

        spinner.setTag(new TagContent(choiceSetInput, comboBoxInputHandler));

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
                               Vector<String>items, boolean hasEmptyDefault)
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
        if(choiceSetInput.GetWrap())
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
        return spinner;
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
            inputView = renderCheckBoxSet(renderedCard, context, choiceSetInput, renderArgs);
        }
        else
        {
            if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Expanded)
            {
                // Create radio button group
                inputView = renderRadioGroup(renderedCard, context, choiceSetInput, renderArgs);
            }
            else if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Compact)
            {
                // create ComboBox (Spinner)
                inputView = renderComboBox(renderedCard, context, choiceSetInput, renderArgs);
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
