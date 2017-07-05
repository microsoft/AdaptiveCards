package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;

import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.ChoiceSetInput;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

import java.util.Vector;

/**
 * Created by bekao on 6/25/2017.
 */

public class ChoiceSetInputRenderer extends BaseCardElementRenderer
{
    private ChoiceSetInputRenderer()
    {
    }

    public static ChoiceSetInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ChoiceSetInputRenderer();
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
            HostConfig hostConfig)
    {
        ChoiceSetInput choiceSetInput = null;
        if (baseCardElement instanceof ChoiceSetInput)
        {
            choiceSetInput = (ChoiceSetInput) baseCardElement;
        }
        else if ((choiceSetInput = ChoiceSetInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ChoiceSetInput object model.");
        }

        return viewGroup;
    }

    private static ChoiceSetInputRenderer s_instance = null;
}
