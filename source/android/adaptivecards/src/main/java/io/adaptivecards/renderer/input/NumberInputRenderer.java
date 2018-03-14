package io.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.InputType;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.NumberInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.inputhandler.TextInputHandler;

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
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
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

        TextInputHandler numberInputHandler = new TextInputHandler(numberInput);
        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                numberInput,
                String.valueOf(numberInput.GetValue()),
                String.valueOf(numberInput.GetPlaceholder()),
                numberInputHandler,
                hostConfig);
        editText.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL);

        return editText;
    }
    
    private static NumberInputRenderer s_instance = null;
}
