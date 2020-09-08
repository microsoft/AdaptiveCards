package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.widget.LinearLayout;

public class ColumnSetLayout extends LinearLayout
{
    public ColumnSetLayout(Context context)
    {
        super(context);
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
    {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }
}
