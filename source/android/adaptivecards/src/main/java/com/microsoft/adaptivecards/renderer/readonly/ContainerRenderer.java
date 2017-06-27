package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Container;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.CardRendererRegistration;

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
            throw new InternalError("Unable to convert BaseCardElement to Container object model.");
        }

        //setSeparationConfig(context, viewGroup, container.GetSeparationStyle(), hostConfig.getContainer().getSeparation(), hostConfig.getStrongSeparation(), true /* horizontal line */);
        return CardRendererRegistration.getInstance().render(context, viewGroup, container, container.GetItems(), hostConfig);
    }

    private static ContainerRenderer s_instance = null;
}
