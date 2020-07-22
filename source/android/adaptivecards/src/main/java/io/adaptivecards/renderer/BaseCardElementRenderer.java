// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import java.util.Set;

import io.adaptivecards.objectmodel.ColorsConfig;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerStyle;
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

    protected static int getColor(String colorCode)
    {
        return android.graphics.Color.parseColor(colorCode);
    }

    public static View setSpacingAndSeparator(Context context,
                                               ViewGroup viewGroup,
                                               Spacing spacing,
                                               boolean separator,
                                               HostConfig hostConfig,
                                               boolean horizontalLine,
                                               boolean isImageSet)
    {
        if (viewGroup.getChildCount() <= 0)
        {
            //Do not add space to the first element of a viewgroup
            return null;
        }
        int spacingSize = Util.dpToPixels(context, getSpacingSize(spacing, hostConfig.GetSpacing()));
        int separatorThickness = Util.dpToPixels(context, hostConfig.GetSeparator().getLineThickness());
        int separatorColor = android.graphics.Color.parseColor(hostConfig.GetSeparator().getLineColor());

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
            // As ImageSets use HorizontalFlowLayout, assigning the spacing between images as MatchParent will make them
            // use more space than needed (making a second row of images to render below the space for the imageSet)
            params = new LinearLayout.LayoutParams(
                    horizontalLine ? LinearLayout.LayoutParams.MATCH_PARENT : spacingSize,
                    horizontalLine ? spacingSize : (isImageSet ? 0 : LinearLayout.LayoutParams.MATCH_PARENT));
        }
        view.setLayoutParams(params);

        // If the element has no tag, then we know it's a separator
        view.setTag(new TagContent(true /* isSeparator */));

        viewGroup.addView(view);
        return view;
    }

    public static View setSpacingAndSeparator(
            Context context,
            ViewGroup viewGroup,
            Spacing spacing,
            boolean separator,
            HostConfig hostConfig,
            boolean horizontalLine)
    {
        return setSpacingAndSeparator(context, viewGroup, spacing, separator, hostConfig, horizontalLine, false /* isImageSet */);
    }

    /**
     * This method retrieves and parses the TagContent object associated to a rendered element
     * @param view defines the rendered element to grab the TagContent from
     * @return TagContent form view
     */
    public static TagContent getTagContent(View view)
    {
        if (view != null)
        {
            Object tag = view.getTag();

            if (tag != null && tag instanceof TagContent)
            {
                return (TagContent) tag;
            }
        }

        return null;
    }

    /**
     *  This method sets the visibility for a rendered element view and its separator. It must be called after setting the view tag as it contains the separator view
     * @param isVisible defines whether the view should be visible or not
     * @param elementView defines the element view (layout, editText, button, etc)
     * @param viewGroupsToUpdate defines the list of viewGroups to update once all the elements have changed visibility
     */
    protected static void setVisibility(boolean isVisible, View elementView, Set<ViewGroup> viewGroupsToUpdate)
    {
        View separator = null;
        TagContent tagContent = getTagContent(elementView);

        if (tagContent != null)
        {
            separator = tagContent.GetSeparator();

            ViewGroup viewGroup = tagContent.GetViewContainer();
            if (viewGroupsToUpdate != null && viewGroup != null)
            {
                viewGroupsToUpdate.add(viewGroup);
            }
        }

        int visibility = isVisible ? View.VISIBLE : View.GONE;

        if (separator != null)
        {
            separator.setVisibility(visibility);
        }

        View stretchContainer = tagContent.GetStretchContainer();
        if (stretchContainer != null)
        {
            stretchContainer.setVisibility(visibility);
        }

        elementView.setVisibility(visibility);
    }

    /**
     *  This method sets the visibility for a rendered element view and its separator. It must be called after setting the view tag as it contains the separator view
     * @param isVisible defines whether the view should be visible or not
     * @param elementView defines the element view (layout, editText, button, etc)
     */
    public static void setVisibility(boolean isVisible, View elementView)
    {
        setVisibility(isVisible, elementView, null);
    }

    /**
     * Sets the minimum height for Collection elements
     * @param minHeight minimum height in pixels. Retrieved from minHeight property
     * @param view Collection element view to apply minimum height to
     * @param context Context for calculating actual height to render
     */
    protected static void setMinHeight(long minHeight, View view, Context context)
    {
        if (minHeight != 0)
        {
            view.setMinimumHeight(Util.dpToPixels(context, (int)minHeight));
        }
    }
}
