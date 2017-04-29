package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.FactSet;

/**
 * Created by bekao on 4/27/2017.
 */

public class FactSetRenderer implements BaseCardElementRenderer
{
    private FactSetRenderer()
    {
    }

    public static FactSetRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new FactSetRenderer();
        }

        return s_instance;
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
    {
        FactSet factSet = null;
        if (baseCardElement instanceof FactSet)
        {
            factSet = (FactSet) baseCardElement;
        }
        else if ((factSet = FactSet.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        return viewGroup;
    }

    private static FactSetRenderer s_instance = null;
}
