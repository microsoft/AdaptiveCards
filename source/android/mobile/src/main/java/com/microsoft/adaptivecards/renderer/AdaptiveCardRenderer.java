package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;

/**
 * Created by bekao on 2/11/2017.
 */

public class AdaptiveCardRenderer
{
    private AdaptiveCardRenderer()
    {
    }

    public static AdaptiveCardRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new AdaptiveCardRenderer();
        }

        return s_instance;
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, AdaptiveCard adaptiveCard)
    {
        BaseCardElementVector baseCardElementList = adaptiveCard.GetBody();
        return (baseCardElementList == null ? null : ContainerRenderer.getInstance().render(context, viewGroup, baseCardElementList));
    }

    private static AdaptiveCardRenderer s_instance = null;
}
