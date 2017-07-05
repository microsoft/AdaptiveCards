package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.ToggleInput;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.Vector;

/**
 * Created by bekao on 6/25/2017.
 */

public class ToggleInputRenderer extends BaseCardElementRenderer
{
    private ToggleInputRenderer()
    {
    }

    public static ToggleInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ToggleInputRenderer();
        }

        return s_instance;
    }

    @Override
    public ViewGroup render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        ToggleInput toggleInput = null;
        if (baseCardElement instanceof ToggleInput)
        {
            toggleInput = (ToggleInput) baseCardElement;
        }
        else if ((toggleInput = ToggleInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ToggleInput object model.");
        }

        return viewGroup;
    }

    private static ToggleInputRenderer s_instance = null;
}
