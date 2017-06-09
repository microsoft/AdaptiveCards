package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Container;
import com.microsoft.adaptivecards.objectmodel.HostConfig;

/**
 * Created by bekao on 2/11/2017.
 */

public class ContainerRenderer extends BaseCardElementRenderer
{
    private ContainerRenderer()
    {
    }

    public static ContainerRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ContainerRenderer();
        }

        return s_instance;
    }

    @Override
    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostConfig hostConfig)
    {
        Container container = null;
        if (baseCardElement instanceof Container)
        {
            container = (Container) baseCardElement;
        }
        else if ((container = Container.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        //setSeparationConfig(context, viewGroup, container.GetSeparationStyle(), hostConfig.getContainer().getSeparation(), hostConfig.getStrongSeparation(), true /* horizontal line */);
        return CardRendererRegistration.getInstance().render(context, viewGroup, container.GetItems(), hostConfig);
    }

    private static ContainerRenderer s_instance = null;
}
