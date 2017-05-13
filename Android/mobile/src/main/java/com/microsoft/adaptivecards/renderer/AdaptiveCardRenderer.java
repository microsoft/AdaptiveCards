package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Container;

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
        Container container = adaptiveCard.GetRoot();
        return (container == null ? null : ContainerRenderer.getInstance().render(context, viewGroup, container));
    }

    private static AdaptiveCardRenderer s_instance = null;
}
