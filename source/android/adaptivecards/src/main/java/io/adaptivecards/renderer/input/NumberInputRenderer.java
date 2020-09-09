// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import androidx.fragment.app.FragmentManager;
import android.text.InputType;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;

import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.NumberInput;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.inputhandler.NumberInputHandler;

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
            RenderArgs renderArgs) throws Exception
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Number is not allowed"));
            return null;
        }

        NumberInput numberInput = Util.castTo(baseCardElement, NumberInput.class);

        NumberInputHandler numberInputHandler = new NumberInputHandler(numberInput);
        TagContent tagContent = new TagContent(numberInput, numberInputHandler);

        EditText editText = renderInternal(
                renderedCard,
                context,
                viewGroup,
                numberInput,
                numberInput.GetValue() != null ? String.valueOf(numberInput.GetValue()) : "",
                String.valueOf(numberInput.GetPlaceholder()),
                numberInputHandler,
                hostConfig,
                tagContent,
                renderArgs,
                ((numberInput.GetMin() != null) || (numberInput.GetMax() != null)));

        editText.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_NUMBER_FLAG_DECIMAL | InputType.TYPE_NUMBER_FLAG_SIGNED);

        editText.setTag(tagContent);

        return editText;
    }

    private static NumberInputRenderer s_instance = null;
}
