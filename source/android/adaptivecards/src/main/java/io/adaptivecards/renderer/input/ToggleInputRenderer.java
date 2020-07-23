// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;

import androidx.fragment.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;

import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ToggleInput;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.inputhandler.ToggleInputHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class ToggleInputRenderer extends BaseCardElementRenderer
{
    protected ToggleInputRenderer()
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
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Toggle is not allowed"));
            return null;
        }

        ToggleInput toggleInput = Util.castTo(baseCardElement, ToggleInput.class);

        final ToggleInputHandler toggleInputHandler = new ToggleInputHandler(toggleInput);
        CheckBox checkBox = new CheckBox(context);
        if(!toggleInput.GetWrap())
        {
            checkBox.setLines(1);
            checkBox.setEllipsize(TextUtils.TruncateAt.END);
        }

        toggleInputHandler.setView(checkBox);

        TagContent tagContent = new TagContent(toggleInput, toggleInputHandler);

        checkBox.setText(toggleInput.GetTitle());
        renderedCard.registerInputHandler(toggleInputHandler, renderArgs.getContainerCardId());

        if (TextUtils.isEmpty(toggleInput.GetValueOn()))
        {
            throw new IllegalArgumentException("Toggle Input, " + toggleInput.GetId() + ", cannot contain empty/null 'On' value");
        }

        if (TextUtils.isEmpty(toggleInput.GetValueOff()))
        {
            throw new IllegalArgumentException("Toggle Input, " + toggleInput.GetId() + ", cannot contain empty/null 'Off' value");
        }

        if (!TextUtils.isEmpty(toggleInput.GetValue()) && toggleInput.GetValue().equals(toggleInput.GetValueOn()))
        {
            checkBox.setChecked(true);
        }

        checkBox.setOnTouchListener(new ChoiceSetInputRenderer.FocusableChoiceListener<CheckBox>(checkBox));

        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
            {
                CardRendererRegistration.getInstance().notifyInputChange(toggleInputHandler.getId(), toggleInputHandler.getInput());
            }
        });

        viewGroup.addView(checkBox);
        checkBox.setTag(tagContent);

        setVisibility(baseCardElement.GetIsVisible(), checkBox);

        return checkBox;
    }

    private static ToggleInputRenderer s_instance = null;
}
