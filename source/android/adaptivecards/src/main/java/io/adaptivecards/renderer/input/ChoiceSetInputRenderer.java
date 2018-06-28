package io.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.CheckBox;
import android.widget.LinearLayout;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Spinner;

import io.adaptivecards.objectmodel.ChoiceInput;
import io.adaptivecards.objectmodel.ChoiceInputVector;
import io.adaptivecards.objectmodel.ChoiceSetStyle;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.CheckBoxSetInputHandler;
import io.adaptivecards.renderer.inputhandler.ComboBoxInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ChoiceSetInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.inputhandler.RadioGroupInputHandler;

import java.util.Arrays;
import java.util.List;
import java.util.Vector;

public class ChoiceSetInputRenderer extends BaseCardElementRenderer
{
    private ChoiceSetInputRenderer()
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

    public View renderCheckBoxSet(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ChoiceSetInput choiceSetInput)
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
        for (int i = 0; i < size; i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);
            CheckBox checkBox = new CheckBox(context);
            checkBox.setText(choiceInput.GetTitle());

            if (defaults.contains(choiceInput.GetValue()))
            {
                checkBox.setChecked(true);
            }
            checkBoxList.add(checkBox);
            layout.addView(checkBox);
        }

        CheckBoxSetInputHandler checkBoxSetInputHandler = new CheckBoxSetInputHandler(choiceSetInput, checkBoxList);
        checkBoxSetInputHandler.setView(layout);
        layout.setTag(checkBoxSetInputHandler);
        renderedCard.registerInputHandler(checkBoxSetInputHandler);
        return layout;
    }

    public View renderRadioGroup(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ChoiceSetInput choiceSetInput)
    {
        RadioGroup radioGroup = new RadioGroup(context);
        radioGroup.setOrientation(RadioGroup.VERTICAL);
        ChoiceInputVector choiceInputVector = choiceSetInput.GetChoices();
        long size = choiceInputVector.size();
        String value = choiceSetInput.GetValue();
        for (int i = 0; i < size; i++)
        {
            ChoiceInput choiceInput = choiceInputVector.get(i);
            RadioButton radioButton = new RadioButton(context);
            radioButton.setId(i);
            radioButton.setText(choiceInput.GetTitle());
            if (choiceInput.GetValue().equals(value))
            {
                radioButton.setChecked(true);
            }
            radioGroup.addView(radioButton);
        }

        RadioGroupInputHandler radioGroupInputHandler = new RadioGroupInputHandler(choiceSetInput);
        radioGroupInputHandler.setView(radioGroup);
        radioGroup.setTag(radioGroupInputHandler);
        renderedCard.registerInputHandler(radioGroupInputHandler);
        return radioGroup;
    }

    public View renderComboBox(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ChoiceSetInput choiceSetInput)
    {
        Vector<String> titleList = new Vector<String>();
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

        ComboBoxInputHandler comboBoxInputHandler = new ComboBoxInputHandler(choiceSetInput);
        Spinner spinner = new Spinner(context);
        comboBoxInputHandler.setView(spinner);
        spinner.setTag(comboBoxInputHandler);
        renderedCard.registerInputHandler(comboBoxInputHandler);
        ArrayAdapter<String> spinnerArrayAdapter = new ArrayAdapter<String>(context, android.R.layout.simple_spinner_item, titleList);
        spinnerArrayAdapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        spinner.setAdapter(spinnerArrayAdapter);
        spinner.setSelection(selection);
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
            ContainerStyle containerStyle)
    {
        if (!hostConfig.getSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.ChoiceSet is not allowed"));
            return null;
        }

        ChoiceSetInput choiceSetInput = null;
        if (baseCardElement instanceof ChoiceSetInput)
        {
            choiceSetInput = (ChoiceSetInput) baseCardElement;
        }
        else if ((choiceSetInput = ChoiceSetInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ChoiceSetInput object model.");
        }

        setSpacingAndSeparator(context, viewGroup, choiceSetInput.GetSpacing(), choiceSetInput.GetSeparator(), hostConfig, true /* horizontal line */);

        View view = null;

        if (choiceSetInput.GetIsMultiSelect())
        {
            // Create multi-select checkbox
            view = renderCheckBoxSet(renderedCard, context, choiceSetInput);
        }
        else
        {
            if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Expanded)
            {
                // Create radio button group
                view = renderRadioGroup(renderedCard, context, choiceSetInput);
            }
            else if (choiceSetInput.GetChoiceSetStyle() == ChoiceSetStyle.Compact)
            {
                // create ComboBox (Spinner)
                view = renderComboBox(renderedCard, context, choiceSetInput);
            }
            else
            {
                throw new IllegalArgumentException("ChoiceSet Input, " + choiceSetInput.GetId() + ", contains invalid style, " + choiceSetInput.GetChoiceSetStyle().toString() + ".");
            }
        }

        viewGroup.addView(view);
        return view;
    }

    private static ChoiceSetInputRenderer s_instance = null;
}
