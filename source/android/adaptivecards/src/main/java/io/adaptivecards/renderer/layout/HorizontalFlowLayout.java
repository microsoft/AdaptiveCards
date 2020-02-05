// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.util.AttributeSet;
import android.view.View;
import android.widget.RelativeLayout;

/**
 * (c) 2016-18 Henrik Gustafsson
 *
 * Contains code snippets licensed under Creative Commons Attribution-Share Alike 4.0
 * International License available at https://creativecommons.org/licenses/by-sa/4.0/.
 *
 * Portions Copyright Microsoft Corporation
 *
 * A custom view that extends {@link android.view.ViewGroup}
 * and which places its children horizontally,
 * flowing over to a new line whenever it runs out of width.
 * <p>
 * Add children to this view like you would for any other {@link android.view.ViewGroup}
 * by either declaring the view and its children in an xml layout file
 * or by calling the {@link #addView} method on the view.
 * <p>
 * This view is a modification of Nishant Nair's Blog post here:
 * <a href="https://nishantvnair.wordpress.com/2010/09/28/flowlayout-in-android">https://nishantvnair.wordpress.com/2010/09/28/flowlayout-in-android</a>
 * <p>
 * TODO: modify this class to allow for right-to-left placement of sub-views as well as left-to-right placement of sub-views.
 */
public class HorizontalFlowLayout extends RelativeLayout {

    /**
     * Constructor to use when creating the view from code.
     */
    public HorizontalFlowLayout(Context context) {
        super(context);
    }

    /**
     * Constructor that is called when inflating the view from XML.
     */
    public HorizontalFlowLayout(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    /**
     * Perform inflation from XML and apply a class-specific base style from a theme attribute.
     */
    public HorizontalFlowLayout(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
    }

//    /**
//     * Perform inflation from XML and apply a class-specific base style from a theme attribute or style resource.
//     *
//     * TODO: uncomment this constructor once the minimum API level of this project is changed to 21 (Lollipop).
//     */
//    public HorizontalFlowLayout(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
//        super(context, attrs, defStyleAttr, defStyleRes);
//    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        // need to call super.onMeasure(...) otherwise we'll get some funny behaviour
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        final int width = MeasureSpec.getSize(widthMeasureSpec);
        int height = MeasureSpec.getSize(heightMeasureSpec);

        final int requiredHeight = measureRequiredHeight(
                width,
                getPaddingTop(),
                getPaddingBottom(),
                getPaddingLeft(),
                getPaddingRight());

        if (MeasureSpec.getMode(heightMeasureSpec) == MeasureSpec.UNSPECIFIED) {
            // set height as required since there's no height restrictions
            height = requiredHeight;
        } else if (MeasureSpec.getMode(heightMeasureSpec) == MeasureSpec.AT_MOST
                && requiredHeight < height) {
            // set height as required since it's less than the maximum allowed
            height = requiredHeight;
        }

        setMeasuredDimension(width, height);
    }

    @Override
    protected void onLayout(boolean changed, int l, int t, int r, int b) {
        // increment the x position as we progress through a line
        int xpos = getPaddingLeft();
        // increment the y position as we progress through the lines
        int ypos = getPaddingTop();
        // the height of the current line
        int line_height = 0;

        View child;
        MarginLayoutParams childMarginLayoutParams;
        int childWidth, childHeight, childMarginLeft, childMarginRight, childMarginTop, childMarginBottom;

        // note: considering "margins" here...
        // ... but don't need to consider "translations" as translations are done post-layout

        for (int i = 0; i < getChildCount(); i++) {
            child = getChildAt(i);

            if (child.getVisibility() != GONE) {
                childWidth = child.getMeasuredWidth();
                childHeight = child.getMeasuredHeight();

                if (child.getLayoutParams() != null
                        && child.getLayoutParams() instanceof MarginLayoutParams) {
                    childMarginLayoutParams = (MarginLayoutParams) child.getLayoutParams();

                    childMarginLeft = childMarginLayoutParams.leftMargin;
                    childMarginRight = childMarginLayoutParams.rightMargin;
                    childMarginTop = childMarginLayoutParams.topMargin;
                    childMarginBottom = childMarginLayoutParams.bottomMargin;
                } else {
                    childMarginLeft = 0;
                    childMarginRight = 0;
                    childMarginTop = 0;
                    childMarginBottom = 0;
                }

                if (xpos + childMarginLeft + childWidth + childMarginRight + getPaddingRight() > r - l) {
                    // this child will need to go on a new line

                    xpos = getPaddingLeft();
                    ypos += line_height;

                    line_height = childHeight + childMarginTop + childMarginBottom;
                } else {
                    // enough space for this child on the current line
                    line_height = Math.max(
                            line_height,
                            childMarginTop + childHeight + childMarginBottom);
                }

                child.layout(
                        xpos + childMarginLeft,
                        ypos + childMarginTop,
                        xpos + childMarginLeft + childWidth,
                        ypos + childMarginTop + childHeight);

                xpos += childMarginLeft + childWidth + childMarginRight;
            }
        }
    }

    /**
     * Measures the height required by this view
     * to fit all its children within the available width,
     * wrapping its children over multiple lines if necessary.
     * <p>
     * (Package-private visibility for uint tests access.)
     *
     * @param width the width available to this view.
     * @return the height required by this view.
     */
    int measureRequiredHeight(int width,
                              int paddingTop,
                              int paddingBottom,
                              int paddingLeft,
                              int paddingRight) {
        // increment the x position as we progress through a line
        int xpos = paddingLeft;
        // increment the y position as we progress through the lines
        int ypos = paddingTop;
        // the height of the current line
        int line_height = 0;

        // go through children
        // to work out the height required for this view

        // call to measure size of children not needed I think?!
        // getting child's measured height/width seems to work okay without it
        //measureChildren(widthMeasureSpec, heightMeasureSpec);

        View child;
        MarginLayoutParams childMarginLayoutParams;
        int childWidth, childHeight, childMarginLeft, childMarginRight, childMarginTop, childMarginBottom;

        for (int i = 0; i < getChildCount(); i++) {
            child = getChildAt(i);

            if (child.getVisibility() != GONE) {
                childWidth = child.getMeasuredWidth();
                childHeight = child.getMeasuredHeight();

                if (child.getLayoutParams() != null
                        && child.getLayoutParams() instanceof MarginLayoutParams) {
                    childMarginLayoutParams = (MarginLayoutParams) child.getLayoutParams();

                    childMarginLeft = childMarginLayoutParams.leftMargin;
                    childMarginRight = childMarginLayoutParams.rightMargin;
                    childMarginTop = childMarginLayoutParams.topMargin;
                    childMarginBottom = childMarginLayoutParams.bottomMargin;
                } else {
                    childMarginLeft = 0;
                    childMarginRight = 0;
                    childMarginTop = 0;
                    childMarginBottom = 0;
                }

                if (xpos + childMarginLeft + childWidth + childMarginRight + paddingRight > width) {
                    // this child will need to go on a new line

                    xpos = paddingLeft;
                    ypos += line_height;

                    line_height = childMarginTop + childHeight + childMarginBottom;
                } else {
                    // enough space for this child on the current line
                    line_height = Math.max(
                            line_height,
                            childMarginTop + childHeight + childMarginBottom);
                }

                xpos += childMarginLeft + childWidth + childMarginRight;
            }
        }

        ypos += line_height + paddingBottom;

        return ypos;
    }
}
