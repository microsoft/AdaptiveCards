// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.TimeInput;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.input.TimeInputRenderer;
import io.adaptivecards.renderer.readonly.RendererUtil;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Map;


public class TimeInputHandler extends TextInputHandler
{
    public TimeInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager)
    {
        super(baseInputElement);
        m_fragmentManager = fragmentManager;
    }

    public FragmentManager getFragmentManager()
    {
        return m_fragmentManager;
    }

    @Override
    public String getInput()
    {
        EditText editText = getEditText();
        try
        {
            Date time = DateFormat.getTimeInstance().parse(editText.getText().toString());
           return s_simpleDateFormat.format(time);
        }
        catch (ParseException e)
        {
            return editText.getText().toString();
        }
    }

    @Override
    public boolean isValidOnSpecifics(String timeInputValue)
    {
        TimeInput timeInput = Util.tryCastTo(m_baseInputElement, TimeInput.class);
        if (timeInput == null)
        {
            return false;
        }

        Date currentTime = null;
        try
        {
            currentTime = getCurrentValue(getInput());
        }
        catch (Exception e)
        {
            return false;
        }

        String minTime = timeInput.GetMin();
        if (!minTime.isEmpty())
        {
            Date min = RendererUtil.getTime(minTime).getTime();
            if (!beforeOrSame(min, currentTime))
            {
                return false;
            }
        }

        String maxTime = timeInput.GetMax();
        if (!maxTime.isEmpty())
        {
            Date max = RendererUtil.getTime(maxTime).getTime();
            if (!beforeOrSame(currentTime, max))
            {
                return false;
            }
        }

        return true;
    }

    private Date getCurrentValue(String timeInputValue) throws Exception
    {
        Date currentTime = TimeInputRenderer.getTimeFormat().parse(timeInputValue);
        Calendar currentValueDate = Calendar.getInstance();
        currentValueDate.setTime(currentTime);

        Date currentDate = new Date();
        Calendar currentDateCalendar = Calendar.getInstance();
        currentDateCalendar.setTime(currentDate);

        currentDateCalendar.set(Calendar.HOUR_OF_DAY, currentValueDate.get(Calendar.HOUR_OF_DAY));
        currentDateCalendar.set(Calendar.MINUTE, currentValueDate.get(Calendar.MINUTE));

        currentTime = currentDateCalendar.getTime();

        return currentTime;
    }

    /**
     * The before method in Date doesn't work as the miliseconds difference introduced by calculations messes the behaviour
     * @param before
     * @param after
     * @return
     */
    private boolean beforeOrSame(Date before, Date after)
    {
        Calendar calendar = Calendar.getInstance();
        calendar.setTime(before);
        int beforeHour = calendar.get(Calendar.HOUR_OF_DAY);
        int beforeMinute = calendar.get(Calendar.MINUTE);

        calendar.setTime(after);
        int afterHour = calendar.get(Calendar.HOUR_OF_DAY);
        int afterMinute = calendar.get(Calendar.MINUTE);

        // If the hour is the same, compare against minutes. Seconds are not considered
        return (beforeHour < afterHour || (beforeHour == afterHour && beforeMinute <= afterMinute));
    }

    private FragmentManager m_fragmentManager;

    public static final String TIME_FORMAT_SUBMIT = "kk:mm";
    public static SimpleDateFormat s_simpleDateFormat = new SimpleDateFormat(TIME_FORMAT_SUBMIT);
}
