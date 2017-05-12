package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Color;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.SeparationOptions;
import com.microsoft.adaptivecards.objectmodel.SeparationStyle;

/**
 * Created by bekao on 5/11/2017.
 */

public class BaseCardElementRenderer implements IBaseCardElementRenderer
{
    protected static void setSeparationOptions(
            Context context,
            ViewGroup viewGroup,
            SeparationStyle separationStyle,
            SeparationOptions defaultSeparationOptions,
            SeparationOptions strongSeparationOptions,
            boolean horizontalLine)
    {
        if (separationStyle.swigValue() == SeparationStyle.None.swigValue())
        {
            return;
        }

        SeparationOptions separationOptions;
        if (separationStyle.swigValue() == SeparationStyle.Default.swigValue())
        {
            separationOptions = defaultSeparationOptions;
        }
        else if (separationStyle.swigValue() == SeparationStyle.Strong.swigValue())
        {
            separationOptions = strongSeparationOptions;
        }
        else
        {
            throw new IllegalArgumentException("Unknown separation style: " + separationStyle.toString());
        }

        View view = new ImageView(context);
        long lineThickness = separationOptions.getLineThickness();
        LinearLayout.LayoutParams params;
        if (lineThickness > 0)
        {
            view.setBackgroundColor(Color.parseColor(separationOptions.getLineColor()));
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : (int) separationOptions.getLineThickness(),
                    horizontalLine ? (int) separationOptions.getLineThickness() : LinearLayout.LayoutParams.MATCH_PARENT);
        }
        else
        {
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : LinearLayout.LayoutParams.WRAP_CONTENT,
                    horizontalLine ? LinearLayout.LayoutParams.WRAP_CONTENT : LinearLayout.LayoutParams.MATCH_PARENT);
        }
        params.setMargins(
                horizontalLine ? 0 : (int)separationOptions.getSpacing() /* left */,
                horizontalLine ? (int)separationOptions.getSpacing() : 0 /* top */,
                horizontalLine ? 0 : (int)separationOptions.getSpacing() /* right */,
                horizontalLine ? (int)separationOptions.getSpacing() : 0 /* bottom */);
        view.setLayoutParams(params);
        viewGroup.addView(view);
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
    {
        return viewGroup;
    }
}
