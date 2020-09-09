// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.app.DatePickerDialog;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import androidx.fragment.app.DialogFragment;
import android.widget.DatePicker;
import android.widget.EditText;

import io.adaptivecards.objectmodel.DateInput;
import io.adaptivecards.renderer.readonly.RendererUtil;

import java.text.DateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.GregorianCalendar;

public class DatePickerFragment extends DialogFragment
        implements DatePickerDialog.OnDateSetListener
{
    public void initialize(DateInput dateInput, EditText editText, Context context)
    {
        m_dateInput = dateInput;
        m_editText = editText;
        m_context = context;
    }

    @Override
    public Dialog onCreateDialog(Bundle savedInstanceState)
    {
        Calendar calendar;

        try
        {
            Date value = DateFormat.getDateInstance().parse(m_editText.getText().toString());
            calendar = new GregorianCalendar();
            calendar.setTime(value);
        }
        catch (Exception excep)
        {
            // Use current date as default date
            calendar = Calendar.getInstance();
        }

        DatePickerDialog datePickerDialog = new DatePickerDialog(m_context, this, calendar.get(Calendar.YEAR), calendar.get(Calendar.MONTH), calendar.get(Calendar.DAY_OF_MONTH));

        if (!m_dateInput.GetMin().isEmpty())
        {
            datePickerDialog.getDatePicker().setMinDate(RendererUtil.getDate(m_dateInput.GetMin()).getTime().getTime());
        }

        if (!m_dateInput.GetMax().isEmpty())
        {
            datePickerDialog.getDatePicker().setMaxDate(RendererUtil.getDate(m_dateInput.GetMax()).getTime().getTime());
        }

        return datePickerDialog;
    }

    @Override
    public void onDateSet(DatePicker view, int year, int month, int dayOfMonth)
    {
        Calendar calendar = new GregorianCalendar(year, month, dayOfMonth);
        Date date = calendar.getTime();
        String value = DateFormat.getDateInstance().format(date);
        m_editText.setText(value);
    }

    private DateInput m_dateInput;
    private EditText m_editText;
    private Context m_context;
}
