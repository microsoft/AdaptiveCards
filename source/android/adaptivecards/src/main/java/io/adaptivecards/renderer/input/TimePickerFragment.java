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

public class TimePickerFragment extends DialogFragment
        implements TimePickerDialog.OnTimeSetListener
{
    public void initialize(EditText editText, Context context)
    {
        m_editText = editText;
        m_context = context;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        Calendar calendar;

        try
        {
            Date value = DateFormat.getTimeInstance().parse(m_editText.getText().toString());
            calendar = new GregorianCalendar();
            calendar.setTime(value);
        }
        catch (Exception excep)
        {
            // Get Current Time
            calendar = Calendar.getInstance();
        }

        return new TimePickerDialog(m_context, this, calendar.get(Calendar.HOUR_OF_DAY), calendar.get(Calendar.MINUTE), false);
    }

    @Override
    public void onTimeSet(TimePicker view, int hourOfDay, int min)
    {
        Calendar calendar = new GregorianCalendar(0, 0, 0, hourOfDay, min);
        String value = DateFormat.getTimeInstance().format(calendar.getTime());
        m_editText.setText(value);
    }

    private EditText m_editText;
    private Context m_context;
}
