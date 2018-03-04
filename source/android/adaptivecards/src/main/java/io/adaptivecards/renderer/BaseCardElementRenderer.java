package io.adaptivecards.renderer;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ColorsConfig;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Spacing;
import io.adaptivecards.objectmodel.SpacingConfig;

public abstract class BaseCardElementRenderer implements IBaseCardElementRenderer
{
    protected static long getSpacingSize(Spacing spacing, SpacingConfig defaultSpacingConfig)
    {
        long spacingSize = 0;
        if (spacing == Spacing.None)
        {
            return 0;
        }
        else if (spacing == Spacing.Default)
        {
            spacingSize = defaultSpacingConfig.getDefaultSpacing();
        }
        else if (spacing == Spacing.ExtraLarge)
        {
            spacingSize = defaultSpacingConfig.getExtraLargeSpacing();
        }
        else if (spacing == Spacing.Large)
        {
            spacingSize = defaultSpacingConfig.getLargeSpacing();
        }
        else if (spacing == Spacing.Medium)
        {
            spacingSize = defaultSpacingConfig.getMediumSpacing();
        }
        else if (spacing == Spacing.Small)
        {
            spacingSize = defaultSpacingConfig.getSmallSpacing();
        }
        else if (spacing == Spacing.Padding)
        {
            spacingSize = defaultSpacingConfig.getPaddingSpacing();
        }
        else
        {
            throw new IllegalArgumentException("Unknown spacing style: " + spacing.toString());
        }

        return (int) spacingSize;
    }

    protected static int getColor(ForegroundColor color, ColorsConfig colorsConfig, boolean isSubtle)
    {
        io.adaptivecards.objectmodel.ColorConfig colorConfig;
        if (color == ForegroundColor.Accent)
        {
            colorConfig = colorsConfig.getAccent();
        }
        else if (color == ForegroundColor.Attention)
        {
            colorConfig = colorsConfig.getAttention();
        }
        else if (color == ForegroundColor.Dark)
        {
            colorConfig = colorsConfig.getDark();
        }
        else if (color == ForegroundColor.Default)
        {
            colorConfig = colorsConfig.getDefaultColor();
        }
        else if (color == ForegroundColor.Good)
        {
            colorConfig = colorsConfig.getGood();
        }
        else if (color == ForegroundColor.Light)
        {
            colorConfig = colorsConfig.getLight();
        }
        else if (color == ForegroundColor.Warning)
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
        if (viewGroup.getChildCount() <= 0)
        {
            //Do not add space to the first element of a viewgroup
            return;
        }
        int spacingSize = Util.dpToPixels(context, getSpacingSize(spacing, hostConfig.getSpacing()));
        int separatorThickness = Util.dpToPixels(context, hostConfig.getSeparator().getLineThickness());
        int separatorColor = android.graphics.Color.parseColor(hostConfig.getSeparator().getLineColor());

        View view = new ImageView(context);
        LinearLayout.LayoutParams params;
        if (separator && separatorThickness > 0)
        {
            view.setBackgroundColor(separatorColor);
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : separatorThickness,
                    horizontalLine ? separatorThickness : LinearLayout.LayoutParams.MATCH_PARENT);
            params.setMargins(
                    horizontalLine ? 0 : spacingSize / 2 /* left */,
                    horizontalLine ? spacingSize / 2 : 0 /* top */,
                    horizontalLine ? 0 : spacingSize / 2 /* right */,
                    horizontalLine ? spacingSize / 2 : 0 /* bottom */);
        }
        else
        {
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : spacingSize,
                    horizontalLine ? spacingSize : LinearLayout.LayoutParams.MATCH_PARENT);
        }
        view.setLayoutParams(params);
        viewGroup.addView(view);
    }
}
