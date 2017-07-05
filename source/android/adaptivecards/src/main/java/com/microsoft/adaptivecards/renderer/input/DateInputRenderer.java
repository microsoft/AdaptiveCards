package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.microsoft.adaptivecards.renderer.inputhandler.DateInputHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.DateInput;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

import java.util.Vector;

import static android.text.InputType.TYPE_NULL;

/**
 * Created by bekao on 6/25/2017.
 */

public class DateInputRenderer extends TextInputRenderer
{
    private DateInputRenderer()
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
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        DateInput dateInput = null;
        if (baseCardElement instanceof DateInput)
        {
            dateInput = (DateInput) baseCardElement;
        }
        else if ((dateInput = DateInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to DateInput object model.");
        }

        DateInputHandler dateInputHandler = new DateInputHandler(dateInput, fragmentManager);
        EditText editText = renderInternal(
                context,
                viewGroup,
                dateInput,
                dateInput.GetValue(),
                dateInput.GetPlaceholder(),
                dateInputHandler,
                inputActionHandlerList,
                hostConfig);
        editText.setRawInputType(TYPE_NULL);
        editText.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                DateInputHandler dateInputHandler = (DateInputHandler) v.getTag();
                DateInput dateInput = (DateInput) dateInputHandler.getBaseInputElement();
                DatePickerFragment datePickerFragment = new DatePickerFragment();
                datePickerFragment.initialize(dateInput, (EditText) v);
                Bundle args = new Bundle();
                args.putString("title", TITLE);
                datePickerFragment.setArguments(args);

                FragmentManager fm = dateInputHandler.getFragmentManager();
                datePickerFragment.show(fm, TITLE);

            }
        });

        setSeparationConfig(context, viewGroup, dateInput.GetSeparationStyle(), hostConfig.getDateInput().getSeparation(), hostConfig.getStrongSeparation(), true /* horizontal line */);
        return editText;
    }

    private static DateInputRenderer s_instance = null;
    private static final String TITLE = "Set Date";
}
