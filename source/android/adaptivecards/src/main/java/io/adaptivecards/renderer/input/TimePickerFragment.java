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

    private long getTimeInMiliseconds(long hours, long minutes)
    {
        return (hours * 60 + minutes) * 10000000 * 60;
    }

    private Calendar getTime(String s)
    {
        Calendar calendar = new GregorianCalendar();
        long[] hour = {0}, minutes = {0};

        if (DateTimePreparser.TryParseSimpleTime(s, hour, minutes))
        {
            Date date = new Date();
            date.setTime(getTimeInMiliseconds(hour[0], minutes[0]));
            calendar.setTime(date);
        }

        return calendar;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        Calendar calendar;

        try
        {
            calendar = getTime(m_editText.getText().toString());
        }
        catch (Exception excep)
        {
            // Get Current Time
            calendar = Calendar.getInstance();
        }

        TimePickerDialog timePickerDialog = new TimePickerDialog(m_context, this, calendar.get(Calendar.HOUR_OF_DAY), calendar.get(Calendar.MINUTE), false);

        return timePickerDialog;
    }

    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int min)
    {
        Calendar calendar = new GregorianCalendar(0, 0, 0, hourOfDay, min);
        String value = DateFormat.getTimeInstance().format(calendar.getTime());
        m_editText.setText(value);
    }

    private TimeInput m_timeInput;
    private EditText m_editText;
    private Context m_context;
}
