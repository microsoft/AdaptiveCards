package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.ContainerStyle;
import com.microsoft.adaptivecards.renderer.Util;
import com.microsoft.adaptivecards.renderer.action.ActionElementRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.Container;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.Vector;

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
    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
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

        setSpacingAndSeparator(context, viewGroup, container.GetSpacing(),container.GetSeparator(), hostConfig, true /* horizontal line */);
        ContainerStyle styleForThis = container.GetStyle().swigValue() == ContainerStyle.None.swigValue() ? containerStyle : container.GetStyle();
        View containerView = CardRendererRegistration.getInstance().render(context, fragmentManager, viewGroup, container, container.GetItems(), inputActionHandlerList, cardActionHandler, hostConfig, styleForThis);
        if (styleForThis.swigValue() != containerStyle.swigValue())
        {
            int padding = Util.dpToPixels(context, hostConfig.getSpacing().getPaddingSpacing());
            containerView.setPadding(padding, padding, padding, padding);
            String color = styleForThis.swigValue() == containerStyle.Emphasis.swigValue() ?
                    hostConfig.getContainerStyles().getEmphasisPalette().getBackgroundColor() :
                    hostConfig.getContainerStyles().getDefaultPalette().getBackgroundColor();
            containerView.setBackgroundColor(Color.parseColor(color));
        }

        if (container.GetSelectAction() != null)
        {
            containerView.setClickable(true);
            containerView.setOnClickListener(new ActionElementRenderer.ButtonOnClickListener(container.GetSelectAction(),inputActionHandlerList, cardActionHandler));
        }

        return containerView;
    }

    private static ContainerRenderer s_instance = null;
}
