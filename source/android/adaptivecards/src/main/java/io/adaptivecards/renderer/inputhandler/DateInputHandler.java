// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.DateInput;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.readonly.RendererUtil;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Map;

public class DateInputHandler extends TextInputHandler
{
    public DateInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager)
    {
        super(baseInputElement);
        m_fragmentManager = fragmentManager;
        s_simpleDateFormat.setLenient(false);
    }

    public FragmentManager getFragmentManager()
    {
        return m_fragmentManager;
    }

    @Override
    public String getInput()
    {
        EditText editText = getEditText();
        try {
            Date date = DateFormat.getDateInstance().parse(editText.getText().toString());
            return s_simpleDateFormat.format(date);
        } catch (ParseException e) {
           return editText.getText().toString();
        }
    }

    @Override
    public boolean isValidOnSpecifics(String inputValue)
    {
        DateInput dateInput = Util.tryCastTo(m_baseInputElement, DateInput.class);

        if (dateInput == null)
        {
            return false;
        }

        Date currentDate = RendererUtil.getDate(inputValue).getTime();

        String minDate = dateInput.GetMin();
        if (!minDate.isEmpty())
        {
            Date min = RendererUtil.getDate(minDate).getTime();

            if (!beforeOrSame(min, currentDate))
            {
                return false;
            }
        }

        String maxTime = dateInput.GetMax();
        if (!maxTime.isEmpty())
        {
            Date max = RendererUtil.getDate(maxTime).getTime();
            if (!beforeOrSame(currentDate, max))
            {
                return false;
            }
        }

        return true;
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
        int beforeYear = calendar.get(Calendar.YEAR);
        int beforeMonth = calendar.get(Calendar.MONTH);
        int beforeDay = calendar.get(Calendar.DAY_OF_MONTH);

        calendar.setTime(after);
        int afterYear = calendar.get(Calendar.YEAR);
        int afterMonth = calendar.get(Calendar.MONTH);
        int afterDay = calendar.get(Calendar.DAY_OF_MONTH);

        // this contains the logic for validating a before date
        // (beforeYear < afterYear || (beforeYear == afterYear && (beforeMonth < afterMonth || (beforeMonth == afterMonth && beforeDay <= afterDay))))
        // as it's hard to read, extra variables were added to make it readable

        // If the months are the same, then the day must be the same or smaller
        boolean beforeOrSameDayOfTheSameMonth = (beforeMonth == afterMonth && beforeDay <= afterDay);
        // If the years are the same, then the month must be smaller or the previous variable must have been satisfied
        boolean beforeOrSameMonthOfTheSameYear = (beforeYear == afterYear && (beforeMonth < afterMonth || beforeOrSameDayOfTheSameMonth));
        // If the years are the same, then the previous variable must have been satisfied
        return (beforeYear < afterYear || beforeOrSameMonthOfTheSameYear);
    }

    private FragmentManager m_fragmentManager;

    public static final String DATE_FORMAT = "yyyy-MM-dd";
    public static DateFormat s_simpleDateFormat = new SimpleDateFormat(DATE_FORMAT);
}
