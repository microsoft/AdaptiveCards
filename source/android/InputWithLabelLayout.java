package com.example.testapplication;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.Nullable;

public class InputWithLabelLayout extends LinearLayout
{
    public InputWithLabelLayout(Context context) {
        super(context);
    }

    public InputWithLabelLayout(Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public InputWithLabelLayout(Context context, @Nullable AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    public InputWithLabelLayout(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    private void initializeComponents()
    {
        addView(m_inputContainer);
        addView(m_);
    }





    private View m_inputContainer = null;
    private TextView m_ = null;
}
