package com.microsoft.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;
import com.microsoft.adaptivecards.objectmodel.DateInput;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Created by bekao on 7/4/2017.
 */

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
    protected void internalValidate()
            throws ParseException
    {
        super.internalValidate();
        DateInput dateInput = (DateInput) m_baseInputElement;

        EditText editText = getEditText();
        Date value = s_simpleDateFormat.parse(editText.getText().toString());
        Date minDate = s_simpleDateFormat.parse(dateInput.GetMin());
        if (value.compareTo(minDate) < 0)
        {
            throw new IllegalArgumentException("Input, " + dateInput.GetId() + ", contains value, " + editText.getText().toString() + ", that is less than the minimum value, " + dateInput.GetMin() + ", allowed.");
        }

        Date maxDate = s_simpleDateFormat.parse(dateInput.GetMax());
        if (value.compareTo(maxDate) > 0)
        {
            throw new IllegalArgumentException("Input, " + dateInput.GetId() + ", contains value, " + editText.getText().toString() + ", that is greater than the maximum value, " + dateInput.GetMax() + ", allowed.");
        }
    }

    private FragmentManager m_fragmentManager;

    public static final String DATE_FORMAT = "M/d/yyyy";
    public static SimpleDateFormat s_simpleDateFormat = new SimpleDateFormat(DATE_FORMAT);
}