package io.adaptivecards.renderer.input;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.TimeInput;
import io.adaptivecards.renderer.inputhandler.TimeInputHandler;

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

        setSpacingAndSeparator(context, viewGroup, timeInput.GetSpacing(), timeInput.GetSeparator(), hostConfig, true /* horizontal line */);

        TimeInputHandler timeInputHandler = new TimeInputHandler(timeInput, fragmentManager);
        String time = timeInput.GetValue();

        try
        {
            Date date = TimeInputHandler.s_simpleDateFormat.parse(timeInput.GetValue());
            time = DateFormat.getTimeInstance().format(date);
        }
        catch (ParseException e)
        {
            //TODO: Log this
        }

        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                timeInput,
                time,
                timeInput.GetPlaceholder(),
                timeInputHandler,
                hostConfig);
        editText.setRawInputType(TYPE_NULL);
        editText.setFocusable(false);
        editText.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                TimeInputHandler timeInputHandler = (TimeInputHandler) v.getTag();
                TimePickerFragment timePickerFragment = new TimePickerFragment();
                timePickerFragment.initialize((EditText) v);
                Bundle args = new Bundle();
                args.putString("title", TITLE);
                timePickerFragment.setArguments(args);

                FragmentManager fm = timeInputHandler.getFragmentManager();
                timePickerFragment.show(fm, TITLE);

            }
        });

        return editText;
    }

    private static TimeInputRenderer s_instance = null;
    private static final String TITLE = "Set Time";
}
