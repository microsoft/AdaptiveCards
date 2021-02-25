package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.widget.Button;

import com.google.android.flexbox.FlexboxLayout;

/**
 * Extension of the FlexboxLayout class whose only purpose is to overrride the getAccessibilityClassName
 * to be able to set an accessible role
 */
public class SelectableFlexboxLayout extends FlexboxLayout
{
    public SelectableFlexboxLayout(Context context)
    {
        super(context);
        setClipChildren(false);
        setClipToPadding(false);
    }

    @Override
    public CharSequence getAccessibilityClassName()
    {
        if (isClickable())
        {
            return Button.class.getName();
        }
        return super.getAccessibilityClassName();
    }
}
