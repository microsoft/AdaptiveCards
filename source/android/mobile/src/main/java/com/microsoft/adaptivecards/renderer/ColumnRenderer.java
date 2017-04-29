package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.Column;

/**
 * Created by bekao on 4/27/2017.
 */

public class ColumnRenderer implements BaseCardElementRenderer
{
    private ColumnRenderer()
    {
    }

    public static ColumnRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ColumnRenderer();
        }

        return s_instance;
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
    {
        Column column = null;
        if (baseCardElement instanceof Column)
        {
            column = (Column) baseCardElement;
        }
        else if ((column = Column.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        return viewGroup;
    }

    private static ColumnRenderer s_instance = null;
}
