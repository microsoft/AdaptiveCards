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
import io.adaptivecards.objectmodel.DateTimePreparser;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.DateInputHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.DateInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.readonly.RendererUtil;

import java.text.DateFormat;
import java.text.ParseException;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;
import java.util.Vector;

import static android.text.InputType.TYPE_NULL;

public class DateInputRenderer extends TextInputRenderer
{
    protected DateInputRenderer()
    {
    }

    public static DateInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new DateInputRenderer();
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
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Date is not allowed"));
            return null;
        }

        DateInput dateInput = null;
        if (baseCardElement instanceof DateInput)
        {
            dateInput = (DateInput) baseCardElement;
        }
        else if ((dateInput = DateInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to DateInput object model.");
        }

        View separator = setSpacingAndSeparator(context, viewGroup, dateInput.GetSpacing(), dateInput.GetSeparator(), hostConfig, true /* horizontal line */);

        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, fragmentManager);

        String dateString = DateFormat.getDateInstance().format(RendererUtil.getDate(dateInput.GetValue()).getTime());

        TagContent tagContent = new TagContent(dateInput, dateInputHandler, separator, viewGroup);
        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                dateInput,
                dateString,
                dateInput.GetPlaceholder(),
                dateInputHandler,
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
                DateInputHandler dateInputHandler = (DateInputHandler) tagContent.GetInputHandler();
                DateInput dateInput = (DateInput) dateInputHandler.getBaseInputElement();
                DatePickerFragment datePickerFragment = new DatePickerFragment();
                datePickerFragment.initialize(dateInput, (EditText) v, context);
                Bundle args = new Bundle();
                args.putString("title", TITLE);
                datePickerFragment.setArguments(args);

                FragmentManager fm = dateInputHandler.getFragmentManager();
                datePickerFragment.show(fm, TITLE);

            }
        });

        editText.setTag(tagContent);
        setVisibility(baseCardElement.GetIsVisible(), editText);

        return editText;
    }

    private static DateInputRenderer s_instance = null;
    private static final String TITLE = "Set Date";
}
