package io.adaptivecards.renderer.layout;

import android.content.Context;
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

        if (mustStretch)
        {
            setLayoutParams(new LayoutParams(LayoutParams.WRAP_CONTENT, LayoutParams.MATCH_PARENT, 1));
        }
    }

    public StretchableElementLayout(Context context, TagContent tag, boolean mustStretch) {
        this(context, mustStretch);
        setTag(tag);
    }

}
