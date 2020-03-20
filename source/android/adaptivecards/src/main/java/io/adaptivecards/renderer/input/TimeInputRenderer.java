// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.DateInput;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TimeInput;
import io.adaptivecards.renderer.inputhandler.TimeInputHandler;
import io.adaptivecards.renderer.inputhandler.validation.IInputValidator;
import io.adaptivecards.renderer.inputhandler.validation.TextInputRangeValidator;
import io.adaptivecards.renderer.inputhandler.validation.TextInputRequiredValidator;
import io.adaptivecards.renderer.inputhandler.validation.TextInputValidator;
import io.adaptivecards.renderer.readonly.RendererUtil;

import java.sql.Time;
import java.text.DateFormat;
import java.text.ParseException;
import java.util.Date;
import java.util.Vector;

import static android.text.InputType.TYPE_NULL;

public class TimeInputRenderer extends TextInputRenderer
{
    protected TimeInputRenderer()
    {
    }

    public static TimeInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new TimeInputRenderer();
        }

        return s_instance;
    }

    private class TimeInputRangeValidator extends TextInputRangeValidator
    {
        public TimeInputRangeValidator(IInputValidator inputValidator, Object min, Object max)
        {
            super(inputValidator, min, max);
        }

        @Override
        public boolean isInRange(String value, Object min, Object max)
        {
            long minTime = RendererUtil.getTime((String)min).getTime().getTime();
            long maxTime = RendererUtil.getTime((String)max).getTime().getTime();
            long timeVal = RendererUtil.getTime(value).getTime().getTime();

            return (minTime <= timeVal) && (timeVal <= maxTime);
        }
    }

    public boolean requiresValidation(TimeInput timeInput)
    {
        boolean requiresValidation = timeInput.GetIsRequired();

        if (!(timeInput.GetMin().isEmpty()))
        {
            requiresValidation = true;
        }

        if (!(timeInput.GetMax().isEmpty()))
        {
            requiresValidation = true;
        }

        return requiresValidation;
    }

    public IInputValidator generateValidator(TimeInput timeInput)
    {
        IInputValidator inputValidator = new TextInputValidator();

        if (timeInput.GetIsRequired())
        {
            inputValidator = new TextInputRequiredValidator(inputValidator);
        }

        String minTime = timeInput.GetMin(), maxTime = timeInput.GetMax();

        if (!(minTime.isEmpty() && maxTime.isEmpty()))
        {
            String rangeMinTime = "00:00 AM", rangeMaxTime = "11:59 PM";

            if (!minTime.isEmpty())
            {
                rangeMinTime = minTime;
            }

            if (!maxTime.isEmpty())
            {
                rangeMaxTime = maxTime;
            }

            inputValidator = new TimeInputRangeValidator(inputValidator, rangeMinTime, rangeMaxTime);
        }

        return inputValidator;
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            final Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs)
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Time is not allowed"));
            return null;
        }

        TimeInput timeInput = null;
        if (baseCardElement instanceof TimeInput)
        {
            timeInput = (TimeInput) baseCardElement;
        }
        else if ((timeInput = TimeInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TimeInput object model.");
        }

        View separator = setSpacingAndSeparator(context, viewGroup, timeInput.GetSpacing(), timeInput.GetSeparator(), hostConfig, true /* horizontal line */);

        TimeInputHandler timeInputHandler = new TimeInputHandler(timeInput, fragmentManager);
        String time = TimeInputRenderer.getTimeFormat().format(RendererUtil.getTime(timeInput.GetValue()).getTime());

        boolean requiresValidation = requiresValidation(timeInput);
        IInputValidator inputValidator = null;
        if (requiresValidation)
        {
            inputValidator = generateValidator(timeInput);
        }

        TagContent tagContent = new TagContent(timeInput, timeInputHandler, separator, viewGroup);
        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                timeInput,
                time,
                timeInput.GetPlaceholder(),
                timeInputHandler,
                hostConfig,
                tagContent,
                renderArgs,
                requiresValidation,
                inputValidator);
        editText.setRawInputType(TYPE_NULL);
        editText.setFocusable(false);
        editText.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                TagContent tagContent = (TagContent) v.getTag();
                TimeInputHandler timeInputHandler = (TimeInputHandler) tagContent.GetInputHandler();
                TimeInput timeInput = (TimeInput) timeInputHandler.getBaseInputElement();
                TimePickerFragment timePickerFragment = new TimePickerFragment();
                timePickerFragment.initialize(timeInput, (EditText) v, context);
                Bundle args = new Bundle();
                args.putString("title", TITLE);
                timePickerFragment.setArguments(args);

                FragmentManager fm = timeInputHandler.getFragmentManager();
                timePickerFragment.show(fm, TITLE);

            }
        });

        editText.setTag(tagContent);
        setVisibility(baseCardElement.GetIsVisible(), editText);

        return editText;
    }

    public static DateFormat getTimeFormat()
    {
        return DateFormat.getTimeInstance(DateFormat.SHORT);
    }

    private static TimeInputRenderer s_instance = null;
    private static final String TITLE = "Set Time";
}
