// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.app.Dialog;
import android.app.TimePickerDialog;
import android.content.Context;
import android.os.Bundle;
import android.support.v4.app.DialogFragment;
import android.widget.EditText;
import android.widget.TimePicker;

import java.text.DateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

import io.adaptivecards.objectmodel.DateTimePreparser;
import io.adaptivecards.objectmodel.TimeInput;

public class TimePickerFragment extends DialogFragment
        implements TimePickerDialog.OnTimeSetListener
{
    public void initialize(TimeInput timeInput, EditText editText, Context context)
    {
        m_timeInput = timeInput;
        m_editText = editText;
        m_context = context;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        Calendar calendar;

        try
        {
            // Get current value shown to user in the TextEdit
            Date value = TimeInputRenderer.getTimeFormat().parse(m_editText.getText().toString());
            calendar = new GregorianCalendar();
            calendar.setTime(value);
        }
        catch (Exception excep)
        {
            // Get Current Time
            calendar = Calendar.getInstance();
        }

        // Android doesn't support min or max time in a timeDialogPicker

        return new TimePickerDialog(m_context, this, calendar.get(Calendar.HOUR_OF_DAY), calendar.get(Calendar.MINUTE), false);
    }

    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int min)
    {
        Calendar calendar = new GregorianCalendar(0, 0, 0, hourOfDay, min);
        String value = TimeInputRenderer.getTimeFormat().format(calendar.getTime());
        m_editText.setText(value);
    }

    private TimeInput m_timeInput;
    private EditText m_editText;
    private Context m_context;
}
