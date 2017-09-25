package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.content.Intent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.Color;
import com.microsoft.adaptivecards.objectmodel.ColorConfig;
import com.microsoft.adaptivecards.objectmodel.ColorsConfig;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.Separator;
import com.microsoft.adaptivecards.objectmodel.SeparatorThickness;
import com.microsoft.adaptivecards.objectmodel.SeparatorThicknessConfig;
import com.microsoft.adaptivecards.objectmodel.Spacing;
import com.microsoft.adaptivecards.objectmodel.SpacingConfig;

/**
 * Created by bekao on 5/11/2017.
 */

public abstract class BaseCardElementRenderer implements IBaseCardElementRenderer
{
    protected static int getSpacingSize(Spacing spacing, SpacingConfig defauiltSpacingConfig)
    {
        long spacingSize = 0;
        if (spacing.swigValue() == Spacing.None.swigValue())
        {
            return 0;
        }
        else if (spacing.swigValue() == Spacing.Default.swigValue())
        {
            spacingSize = defauiltSpacingConfig.getDefaultSpacing();
        }
        else if (spacing.swigValue() == Spacing.ExtraLarge.swigValue())
        {
            spacingSize = defauiltSpacingConfig.getExtraLargeSpacing();
        }
        else if (spacing.swigValue() == Spacing.Large.swigValue())
        {
            spacingSize = defauiltSpacingConfig.getLargeSpacing();
        }
        else if (spacing.swigValue() == Spacing.Medium.swigValue())
        {
            spacingSize = defauiltSpacingConfig.getMediumSpacing();
        }
        else if (spacing.swigValue() == Spacing.Small.swigValue())
        {
            spacingSize = defauiltSpacingConfig.getSmallSpacing();
        }
//        else if (spacing.swigValue() == Spacing.Padding.swigValue())
//        {
//            spacingSize = defauiltSpacingConfig.getSmallSpacing();
//        }
        else
        {
            throw new IllegalArgumentException("Unknown spacing style: " + spacing.toString());
        }

        return (int) spacingSize;
    }

    protected static int getSeparatorThicknessSize(SeparatorThickness separatorThickness, SeparatorThicknessConfig defaultSeparatorThicknessConfig)
    {
        long separatorThicknessSize = 0;
        if (separatorThickness.swigValue() == SeparatorThickness.Default.swigValue())
        {
            separatorThicknessSize = defaultSeparatorThicknessConfig.getDefaultSeparatorThickness();
        }
        else if (separatorThickness.swigValue() == SeparatorThickness.Thick.swigValue())
        {
            separatorThicknessSize = defaultSeparatorThicknessConfig.getThickSeparatorThickness();
        }

        return (int) separatorThicknessSize;
    }

    protected static int getColor(Color color, ColorsConfig colorsConfig, boolean isSubtle)
    {
        com.microsoft.adaptivecards.objectmodel.ColorConfig colorConfig;
        if (color.swigValue() == Color.Accent.swigValue())
        {
            colorConfig = colorsConfig.getAccent();
        }
        else if (color.swigValue() == Color.Attention.swigValue())
        {
            colorConfig = colorsConfig.getAttention();
        }
        else if (color.swigValue() == Color.Dark.swigValue())
        {
            colorConfig = colorsConfig.getDark();
        }
        else if (color.swigValue() == Color.Default.swigValue())
        {
            colorConfig = colorsConfig.getDefaultColor();
        }
        else if (color.swigValue() == Color.Good.swigValue())
        {
            colorConfig = colorsConfig.getGood();
        }
        else if (color.swigValue() == Color.Light.swigValue())
        {
            colorConfig = colorsConfig.getLight();
        }
        else if (color.swigValue() == Color.Warning.swigValue())
        {
            colorConfig = colorsConfig.getWarning();
        }
        else
        {
            throw new IllegalArgumentException("Unknown color: " + color.toString());
        }

        return android.graphics.Color.parseColor(isSubtle ? colorConfig.getSubtle() : colorConfig.getNormal());
    }

    protected static void setSpacingAndSeparator(
            Context context,
            ViewGroup viewGroup,
            Spacing spacing,
            Separator separator,
            HostConfig hostConfig,
            boolean horizontalLine)
    {
        int spacingSize = getSpacingSize(spacing, hostConfig.getSpacing());
        int separatorThickness = getSeparatorThicknessSize(separator.GetThickness(), hostConfig.getSeparatorThickness());
        int separatorColor = getColor(separator.GetColor(), hostConfig.getColors(), false /* TBD: separator subtle always false? */);

        View view = new ImageView(context);
        LinearLayout.LayoutParams params;
        if (separatorThickness > 0)
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
