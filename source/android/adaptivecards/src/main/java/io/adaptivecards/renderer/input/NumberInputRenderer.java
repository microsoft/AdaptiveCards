// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.InputType;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.NumberInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.inputhandler.TextInputHandler;

import java.util.Vector;

public class NumberInputRenderer extends TextInputRenderer
{
    protected NumberInputRenderer()
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
            RenderArgs renderArgs)
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Number is not allowed"));
            return null;
        }

        NumberInput numberInput = null;
        if (baseCardElement instanceof NumberInput)
        {
            numberInput = (NumberInput) baseCardElement;
        }
        else if ((numberInput = NumberInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to NumberInput object model.");
        }
        View separator = setSpacingAndSeparator(context, viewGroup, numberInput.GetSpacing(), numberInput.GetSeparator(), hostConfig, true /* horizontal line */);

        TextInputHandler numberInputHandler = new TextInputHandler(numberInput);
        TagContent tagContent = new TagContent(numberInput, numberInputHandler, separator, viewGroup);
        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                numberInput,
                String.valueOf(numberInput.GetValue()),
                String.valueOf(numberInput.GetPlaceholder()),
                numberInputHandler,
                hostConfig,
                tagContent);
        editText.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL);

        editText.setTag(tagContent);
        setVisibility(baseCardElement.GetIsVisible(), editText);

        return editText;
    }

    private static NumberInputRenderer s_instance = null;
}
