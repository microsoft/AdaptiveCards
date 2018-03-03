package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.microsoft.adaptivecards.objectmodel.ContainerStyle;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.TimeInput;
import com.microsoft.adaptivecards.renderer.inputhandler.TimeInputHandler;

import java.text.DateFormat;
import java.text.ParseException;
import java.util.Date;
import java.util.Vector;

import static android.text.InputType.TYPE_NULL;

public class TimeInputRenderer extends TextInputRenderer
{
    private TimeInputRenderer()
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
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
    {
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
                context,
                viewGroup,
                timeInput,
                time,
                timeInput.GetPlaceholder(),
                timeInputHandler,
                inputActionHandlerList,
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
