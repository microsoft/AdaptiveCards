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
    public StretchableElementLayout(Context context) {
        super(context);
        setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
    }

    public StretchableElementLayout(Context context, TagContent tag) {
        this(context);
        setTag(tag);
    }

}
