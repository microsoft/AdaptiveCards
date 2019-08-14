// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.input;

import android.content.Context;
import android.nfc.Tag;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ToggleInput;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.inputhandler.IInputWatcher;
import io.adaptivecards.renderer.inputhandler.ToggleInputHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import java.util.Vector;

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
            RenderArgs renderArgs)
    {
        if (!hostConfig.GetSupportsInteractivity())
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Input.Toggle is not allowed"));
            return null;
        }

        ToggleInput toggleInput = null;
        if (baseCardElement instanceof ToggleInput)
        {
            toggleInput = (ToggleInput) baseCardElement;
        }
        else if ((toggleInput = ToggleInput.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ToggleInput object model.");
        }

        View separator = setSpacingAndSeparator(context, viewGroup, toggleInput.GetSpacing(), toggleInput.GetSeparator(), hostConfig, true /* horizontal line */);

        final ToggleInputHandler toggleInputHandler = new ToggleInputHandler(toggleInput);
        CheckBox checkBox = new CheckBox(context);
        if(!toggleInput.GetWrap())
        {
            checkBox.setLines(1);
            checkBox.setEllipsize(TextUtils.TruncateAt.END);
        }
        toggleInputHandler.setView(checkBox);

        TagContent tagContent = new TagContent(toggleInput, toggleInputHandler, separator, viewGroup);

        checkBox.setText(toggleInput.GetTitle());
        renderedCard.registerInputHandler(toggleInputHandler);

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
        checkBox.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener()
        {
            @Override
            public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
            {
                CardRendererRegistration.getInstance().notifyInputChange(toggleInputHandler.getId(), toggleInputHandler.getInput());
            }
        });

        if (toggleInput.GetHeight() == HeightType.Stretch)
        {
            LinearLayout toggleInputContainer = new LinearLayout(context);

            if (toggleInput.GetHeight() == HeightType.Stretch)
            {
                toggleInputContainer.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
            }
            else
            {
                toggleInputContainer.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT));
            }

            tagContent.SetStretchContainer(toggleInputContainer);
            toggleInputContainer.addView(checkBox);
            viewGroup.addView(toggleInputContainer);
        }
        else
        {
            viewGroup.addView(checkBox);
        }

        checkBox.setTag(tagContent);
        setVisibility(baseCardElement.GetIsVisible(), checkBox);

        return checkBox;
    }

    private static ToggleInputRenderer s_instance = null;
}
