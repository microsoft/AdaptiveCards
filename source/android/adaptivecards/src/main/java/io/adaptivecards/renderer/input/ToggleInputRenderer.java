package io.adaptivecards.renderer.input;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.CheckBox;

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ToggleInput;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.inputhandler.ToggleInputHandler;

import java.util.Vector;

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
        if (!hostConfig.getSupportsInteractivity())
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

        setSpacingAndSeparator(context, viewGroup, toggleInput.GetSpacing(), toggleInput.GetSeparator(), hostConfig, true /* horizontal line */);

        ToggleInputHandler toggleInputHandler = new ToggleInputHandler(toggleInput);
        CheckBox checkBox = new CheckBox(context);
        toggleInputHandler.setView(checkBox);
        checkBox.setTag(toggleInputHandler);
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

        viewGroup.addView(checkBox);
        return checkBox;
    }

    private static ToggleInputRenderer s_instance = null;
}
