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
            String text = editText.getText().toString();
            Date time = DateFormat.getTimeInstance(DateFormat.SHORT).parse(text);
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

        // If the time is not required and the time is empty, then consider it valid
        if (!timeInput.GetIsRequired() && timeInputValue.isEmpty())
        {
            return true;
        }

        if (!RendererUtil.isValidTime(timeInputValue))
        {
            return false;
        }

        Date currentTime = null;
        try
        {
            currentTime = getCurrentValue(timeInputValue);
        }
        catch (Exception e)
        {
            return false;
        }

        String minTime = timeInput.GetMin();
        if (!minTime.isEmpty())
        {
            try
            {
                Date min = getCurrentValue(minTime);
                if (!beforeOrSame(min, currentTime))
                {
                    return false;
                }
            }
            catch (Exception e) { /* if the minTime cannot be parsed, skip the min check */ }
        }

        String maxTime = timeInput.GetMax();
        if (!maxTime.isEmpty())
        {
            try
            {
                Date max = RendererUtil.getTime(maxTime).getTime();
                if (!beforeOrSame(currentTime, max))
                {
                    return false;
                }
            }
            catch (Exception e) { /* if the maxTime cannot be parsed, skip the max check */ }
        }

        return true;
    }

    private Date getCurrentValue(String timeInputValue) throws Exception
    {
        String formattedTime = TimeInputRenderer.getTimeFormat().format(RendererUtil.getTime(timeInputValue).getTime());

        Date currentTime = TimeInputRenderer.getTimeFormat().parse(formattedTime);
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
     * @param before The date expected to be the same or prior to after
     * @param after The date expected to be the same or later than before
     * @return True if before is the same or prior to after
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
