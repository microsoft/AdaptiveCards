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
        String time = DateFormat.getTimeInstance().format(RendererUtil.getTime(timeInput.GetValue()).getTime());

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
                tagContent);
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

    private static TimeInputRenderer s_instance = null;
    private static final String TITLE = "Set Time";
}
