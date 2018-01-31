package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.ColorConfig;
import com.microsoft.adaptivecards.objectmodel.ColorsConfig;
import com.microsoft.adaptivecards.objectmodel.ForegroundColor;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.SeparatorThickness;
import com.microsoft.adaptivecards.objectmodel.Spacing;
import com.microsoft.adaptivecards.objectmodel.SpacingConfig;

/**
 * Created by bekao on 5/11/2017.
 */

public abstract class BaseCardElementRenderer implements IBaseCardElementRenderer
{
    protected static int getSpacingSize(Spacing spacing, SpacingConfig defaultSpacingConfig)
    {
        long spacingSize = 0;
        if (spacing.swigValue() == Spacing.None.swigValue())
        {
            return 0;
        }
        else if (spacing.swigValue() == Spacing.Default.swigValue())
        {
            spacingSize = defaultSpacingConfig.getDefaultSpacing();
        }
        else if (spacing.swigValue() == Spacing.ExtraLarge.swigValue())
        {
            spacingSize = defaultSpacingConfig.getExtraLargeSpacing();
        }
        else if (spacing.swigValue() == Spacing.Large.swigValue())
        {
            spacingSize = defaultSpacingConfig.getLargeSpacing();
        }
        else if (spacing.swigValue() == Spacing.Medium.swigValue())
        {
            spacingSize = defaultSpacingConfig.getMediumSpacing();
        }
        else if (spacing.swigValue() == Spacing.Small.swigValue())
        {
            spacingSize = defaultSpacingConfig.getSmallSpacing();
        }
//        else if (spacing.swigValue() == Spacing.Padding.swigValue())
//        {
//            spacingSize = defaultSpacingConfig.getSmallSpacing();
//        }
        else
        {
            throw new IllegalArgumentException("Unknown spacing style: " + spacing.toString());
        }

        return (int) spacingSize;
    }

    protected static int getColor(ForegroundColor color, ColorsConfig colorsConfig, boolean isSubtle)
    {
        com.microsoft.adaptivecards.objectmodel.ColorConfig colorConfig;
        if (color.swigValue() == ForegroundColor.Accent.swigValue())
        {
            colorConfig = colorsConfig.getAccent();
        }
        else if (color.swigValue() == ForegroundColor.Attention.swigValue())
        {
            colorConfig = colorsConfig.getAttention();
        }
        else if (color.swigValue() == ForegroundColor.Dark.swigValue())
        {
            colorConfig = colorsConfig.getDark();
        }
        else if (color.swigValue() == ForegroundColor.Default.swigValue())
        {
            colorConfig = colorsConfig.getDefaultColor();
        }
        else if (color.swigValue() == ForegroundColor.Good.swigValue())
        {
            colorConfig = colorsConfig.getGood();
        }
        else if (color.swigValue() == ForegroundColor.Light.swigValue())
        {
            colorConfig = colorsConfig.getLight();
        }
        else if (color.swigValue() == ForegroundColor.Warning.swigValue())
        {
            colorConfig = colorsConfig.getWarning();
        }
        else
        {
            throw new IllegalArgumentException("Unknown color: " + color.toString());
        }

        return android.graphics.Color.parseColor(isSubtle ? colorConfig.getSubtleColor() : colorConfig.getDefaultColor());
    }

    protected static void setSpacingAndSeparator(
            Context context,
            ViewGroup viewGroup,
            Spacing spacing,
            boolean separator,
            HostConfig hostConfig,
            boolean horizontalLine)
    {
        int spacingSize = getSpacingSize(spacing, hostConfig.getSpacing());
        int separatorThickness = (int)hostConfig.getSeparator().getLineThickness();
        int separatorColor = android.graphics.Color.parseColor(hostConfig.getSeparator().getLineColor());

        View view = new ImageView(context);
        LinearLayout.LayoutParams params;
        if (separator && separatorThickness > 0)
        {
            view.setBackgroundColor(separatorColor);
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : separatorThickness,
                    horizontalLine ? separatorThickness : LinearLayout.LayoutParams.MATCH_PARENT);
        }
        else
        {
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : LinearLayout.LayoutParams.WRAP_CONTENT,
                    horizontalLine ? LinearLayout.LayoutParams.WRAP_CONTENT : LinearLayout.LayoutParams.MATCH_PARENT);
        }
        params.setMargins(
                horizontalLine ? 0 : spacingSize /* left */,
                horizontalLine ? spacingSize : 0 /* top */,
                horizontalLine ? 0 : spacingSize /* right */,
                horizontalLine ? spacingSize : 0 /* bottom */);
        view.setLayoutParams(params);
        viewGroup.addView(view);
    }
}
