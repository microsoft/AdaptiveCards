package com.microsoft.adaptivecards.renderer.input;

import android.app.Dialog;
import android.app.TimePickerDialog;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.widget.EditText;
import android.widget.TimePicker;

import com.microsoft.adaptivecards.objectmodel.TimeInput;
import com.microsoft.adaptivecards.renderer.inputhandler.TimeInputHandler;

import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

/**
 * Created by bekao on 7/4/2017.
 */

public class TimePickerFragment extends DialogFragment
        implements TimePickerDialog.OnTimeSetListener
{
    public void initialize(TimeInput timeInput, EditText editText)
    {
        m_timeInput = timeInput;
        m_editText = editText;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        Calendar calendar;

        try
        {
            Date value = TimeInputHandler.s_simpleDateFormat.parse(m_editText.getText().toString());
            calendar = new GregorianCalendar();
            calendar.setTime(value);
        }
        catch (Exception excep)
        {
            // Get Current Time
            calendar = Calendar.getInstance();
        }

        return new TimePickerDialog(getActivity(), this, calendar.get(Calendar.HOUR_OF_DAY), calendar.get(Calendar.MINUTE), false);
    }

    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int min)
    {
        Calendar calendar = new GregorianCalendar(0, 0, 0, hourOfDay, min);
        String value = TimeInputHandler.s_simpleDateFormat.format(calendar.getTime());
        m_editText.setText(value);
    }

    private TimeInput m_timeInput;
    private EditText m_editText;
}
