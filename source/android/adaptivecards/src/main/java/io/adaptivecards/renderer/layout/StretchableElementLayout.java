package io.adaptivecards.renderer.layout;

import android.content.Context;
import android.graphics.drawable.GradientDrawable;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.renderer.TagContent;

/*
* The whole point of this class is to avoid repetition of setting the size of element layouts every time
* */
public class StretchableElementLayout extends LinearLayout
{
    public StretchableElementLayout(Context context, boolean mustStretch) {
        super(context);

        setOrientation(VERTICAL);
        if (mustStretch)
        {
            setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT));
        }
    }

    public StretchableElementLayout(Context context, TagContent tag, boolean mustStretch) {
        this(context, mustStretch);
        setTag(tag);
    }

}
