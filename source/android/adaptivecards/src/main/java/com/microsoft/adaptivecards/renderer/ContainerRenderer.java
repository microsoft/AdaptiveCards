package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Container;
import com.microsoft.adaptivecards.objectmodel.HostOptions;

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
    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
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

        //setSeparationOptions(context, viewGroup, container.GetSeparationStyle(), hostOptions.getContainer().getSeparation(), hostOptions.getStrongSeparation(), true /* horizontal line */);
        return CardRendererRegistration.getInstance().render(context, viewGroup, container.GetItems(), hostOptions);
    }

    private static ContainerRenderer s_instance = null;
}
