package com.microsoft.adaptivecards.renderer.inputhandler;

import android.support.v4.app.FragmentManager;
import android.widget.EditText;

import com.microsoft.adaptivecards.objectmodel.BaseInputElement;

import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Map;


public class TimeInputHandler extends TextInputHandler
{
    public TimeInputHandler(BaseInputElement baseInputElement, FragmentManager fragmentManager)
    {
        super(baseInputElement);
        m_fragmentManager = fragmentManager;
    }

    public FragmentManager getFragmentManager()
    {
        return m_fragmentManager;
    }

    @Override
    protected void internalValidate()
            throws ParseException
    {

    }

    @Override
    public Exception getData(Map<String, String> data)
    {
        EditText editText = getEditText();
        try {
            Date time = DateFormat.getTimeInstance().parse(editText.getText().toString());
            data.put(m_baseInputElement.GetId(), s_simpleDateFormat.format(time));
        } catch (ParseException e) {
            data.put(m_baseInputElement.GetId(), editText.getText().toString());
        }

        return null;
    }

    private FragmentManager m_fragmentManager;

    public static final String TIME_FORMAT_SUBMIT = "kk:mm";
    public static SimpleDateFormat s_simpleDateFormat = new SimpleDateFormat(TIME_FORMAT_SUBMIT);
}
