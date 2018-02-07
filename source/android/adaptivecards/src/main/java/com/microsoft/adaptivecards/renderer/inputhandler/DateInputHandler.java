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
    }

    private FragmentManager m_fragmentManager;

    public static final String DATE_FORMAT = "M/d/yyyy";
    public static SimpleDateFormat s_simpleDateFormat = new SimpleDateFormat(DATE_FORMAT);
}