package com.microsoft.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.InputType;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.NumberInput;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.inputhandler.NumberInputHandler;

import java.util.Vector;

public class NumberInputRenderer extends TextInputRenderer
{
    private NumberInputRenderer()
    {
    }

    public static NumberInputRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new NumberInputRenderer();
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
            HostConfig hostConfig)
    {
        NumberInput numberInput = null;
        if (baseCardElement instanceof NumberInput)
        {
            numberInput = (NumberInput) baseCardElement;
        }
        else if ((numberInput = NumberInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to NumberInput object model.");
        }
        setSpacingAndSeparator(context, viewGroup, numberInput.GetSpacing(), numberInput.GetSeparator(), hostConfig, true /* horizontal line */);

        NumberInputHandler numberInputHandler = new NumberInputHandler(numberInput);
        EditText editText = renderInternal(
                context,
                viewGroup,
                numberInput,
                String.valueOf(numberInput.GetValue()),
                String.valueOf(numberInput.GetPlaceholder()),
                numberInputHandler,
                inputActionHandlerList,
                hostConfig);
        editText.setRawInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_SIGNED);

        return editText;
    }
    
    private static NumberInputRenderer s_instance = null;
}
