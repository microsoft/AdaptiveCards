package com.microsoft.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;
import com.microsoft.adaptivecards.objectmodel.TimeInput;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;


public class TimeInputHandler extends TextInputHandler
{
    public TimeInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager)
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
        TimeInput timeInput = (TimeInput) m_baseInputElement;

        EditText editText = (EditText) getEditText();
        Date value = s_simpleDateFormat.parse(editText.getText().toString());
        Date minTime = s_simpleDateFormat.parse(timeInput.GetMin());
        if (value.compareTo(minTime) < 0)
        {
            throw new IllegalArgumentException("Input, " + timeInput.GetId() + ", contains value, " + editText.getText().toString() + ", that is less than the minimum value, " + timeInput.GetMin() + ", allowed.");
        }

        Date maxTime = s_simpleDateFormat.parse(timeInput.GetMax());
        if (value.compareTo(maxTime) > 0)
        {
            throw new IllegalArgumentException("Input, " + timeInput.GetId() + ", contains value, " + editText.getText().toString() + ", that is greater than the maximum value, " + timeInput.GetMax() + ", allowed.");
        }
    }

    private FragmentManager m_fragmentManager;

    public static final String TIME_FORMAT = "hh:mm a";
    public static SimpleDateFormat s_simpleDateFormat = new SimpleDateFormat(TIME_FORMAT);
}
