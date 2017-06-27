package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

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

    public ViewGroup render(Context context, AdaptiveCard adaptiveCard)
    {
        return render(context, adaptiveCard, defaultHostConfig);
    }

    // AdaptiveCard ObjectModel is binded to the UI and Action
    public ViewGroup render(Context context, AdaptiveCard adaptiveCard, HostConfig hostConfig)
    {
        if (hostConfig == null)
        {
            throw new IllegalArgumentException("hostConfig is null");
        }

        LinearLayout layout = new LinearLayout(context);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        layout.setOrientation(LinearLayout.VERTICAL);

        BaseCardElementVector baseCardElementList = adaptiveCard.GetBody();

        if (baseCardElementList == null)
        {
            throw new IllegalArgumentException("Adaptive Card does not contain a body.");
        }

        ViewGroup viewGroup = CardRendererRegistration.getInstance().render(context, layout, adaptiveCard, baseCardElementList, hostConfig);
        return viewGroup;
    }

    private static AdaptiveCardRenderer s_instance = null;

    private HostConfig defaultHostConfig = new HostConfig();
}
