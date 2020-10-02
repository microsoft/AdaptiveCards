package io.adaptivecards.renderer.input;

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.widget.EditText;
import android.widget.LinearLayout;

import io.adaptivecards.renderer.inputhandler.TextInputHandler;

@SuppressLint("AppCompatCustomView")
public class ValidatedEditText extends EditText
{
    public ValidatedEditText(Context context) {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        m_paint.setColor(Color.TRANSPARENT);
    }

    public ValidatedEditText(Context context, int errorColor) {
        this(context);
        m_errorColor = errorColor;
    }

    @SuppressLint("Range")
    @Override
    protected void onDraw(Canvas canvas)
    {
        super.onDraw(canvas);

        // Left vertical line
        canvas.drawRect(0, 0, borderWidth, getHeight(), m_paint);

        // Top horizontal line
        canvas.drawRect(0, 0, getWidth(), borderWidth, m_paint);

        // Bottom horizontal line
        canvas.drawRect(0, getHeight() - borderWidth, getWidth(), getHeight(), m_paint);

        // Right vertical line
        canvas.drawRect(getWidth() - borderWidth, 0, getWidth(), getHeight(), m_paint);
    }

    public void setValidationResult(boolean isValid)
    {
        if (isValid)
        {
            // Change border color to transparent color
            m_paint.setColor(Color.TRANSPARENT);
        }
        else
        {
            // Change border to red
            m_paint.setColor(m_errorColor);
        }
        invalidate();
    }

    private int m_errorColor = Color.TRANSPARENT;
    private final Paint m_paint = new Paint();
    private final float borderWidth = 5.0f;
}
