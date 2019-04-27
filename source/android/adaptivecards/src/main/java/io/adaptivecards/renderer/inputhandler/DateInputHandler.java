// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import io.adaptivecards.objectmodel.BaseInputElement;

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

    private FragmentManager m_fragmentManager;

    public static final String DATE_FORMAT = "yyyy-MM-dd";
    public static DateFormat s_simpleDateFormat = new SimpleDateFormat(DATE_FORMAT);
}
