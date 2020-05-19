// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import io.adaptivecards.objectmodel.BaseInputElement;
import io.adaptivecards.objectmodel.DateInput;
import io.adaptivecards.renderer.readonly.RendererUtil;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
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
        DateInput dateInput = null;
        if (m_baseInputElement instanceof DateInput)
        {
            dateInput = (DateInput) m_baseInputElement;
        }
        else if ((dateInput = DateInput.dynamic_cast(m_baseInputElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to TimeInput object model.");
        }

        Date currentDate = RendererUtil.getDate(inputValue).getTime();

        String minDate = dateInput.GetMin();
        if (!minDate.isEmpty())
        {
            Date min = RendererUtil.getDate(minDate).getTime();
            if (currentDate.before(min))
            {
                return false;
            }
        }

        String maxTime = dateInput.GetMax();
        if (!maxTime.isEmpty())
        {
            Date max = RendererUtil.getDate(maxTime).getTime();
            if (currentDate.after(max))
            {
                return false;
            }
        }

        return true;
    }

    private FragmentManager m_fragmentManager;

    public static final String DATE_FORMAT = "yyyy-MM-dd";
    public static DateFormat s_simpleDateFormat = new SimpleDateFormat(DATE_FORMAT);
}
