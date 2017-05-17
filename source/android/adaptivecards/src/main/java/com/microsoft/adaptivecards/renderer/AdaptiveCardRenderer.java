package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.HostOptions;

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

    public ViewGroup render(Context context, AdaptiveCard adaptiveCard, HostOptions hostOptions)
    {
        try
        {
            LinearLayout layout = new LinearLayout(context);
            layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
            layout.setOrientation(LinearLayout.VERTICAL);

            BaseCardElementVector baseCardElementList = adaptiveCard.GetBody();
            return (baseCardElementList == null ? null : CardRendererRegistration.getInstance().render(context, layout, baseCardElementList, hostOptions));
        }
        catch (Exception ex)
        {
            ex.printStackTrace();
        }
        return null;
    }

    private static AdaptiveCardRenderer s_instance = null;
}
