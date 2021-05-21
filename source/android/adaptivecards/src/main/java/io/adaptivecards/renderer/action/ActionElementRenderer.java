// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.action;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.PorterDuff;
import android.text.TextUtils;
import android.util.TypedValue;
import android.view.ContextThemeWrapper;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

import androidx.appcompat.widget.TooltipCompat;
import androidx.fragment.app.FragmentManager;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ExecuteAction;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class ActionElementRenderer extends BaseActionElementRenderer
{
    protected ActionElementRenderer()
    {
    }

    public static ActionElementRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ActionElementRenderer();
        }

        return s_instance;
    }

    private static Button createButtonWithTheme(Context context, int theme)
    {
        Context themedContext = new ContextThemeWrapper(context, theme);
        return new Button(themedContext);
    }

    protected static Button getButtonForStyle(Context context, String style, HostConfig hostConfig)
    {
        boolean isPositiveStyle = style.equalsIgnoreCase("Positive");
        boolean isDestructiveStyle = style.equalsIgnoreCase("Destructive");

        if(isPositiveStyle || isDestructiveStyle)
        {
            Resources.Theme theme = context.getTheme();
            TypedValue buttonStyle = new TypedValue();

            if(isPositiveStyle)
            {
                if(theme.resolveAttribute(R.attr.adaptiveActionPositive, buttonStyle, true))
                {
                    return createButtonWithTheme(context, buttonStyle.data);
                }
                else
                {
                    Button button = new Button(context);
                    button.getBackground().setColorFilter(getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Accent, false)), PorterDuff.Mode.MULTIPLY);
                    return button;
                }
            }
            else
            {
                if(theme.resolveAttribute(R.attr.adaptiveActionDestructive, buttonStyle, true))
                {
                    return createButtonWithTheme(context, buttonStyle.data);
                }
                else
                {
                    Button button = new Button(context);
                    button.setTextColor(getColor(hostConfig.GetForegroundColor(ContainerStyle.Default, ForegroundColor.Attention, false)));
                    return button;
                }
            }
        }

        return new Button(context);
    }

    public Button renderButton(
        Context context,
        ViewGroup viewGroup,
        BaseActionElement baseActionElement,
        HostConfig hostConfig,
        RenderedAdaptiveCard renderedCard,
        RenderArgs renderArgs)
    {
        TypedValue buttonStyle = new TypedValue();
        if (baseActionElement.GetElementType() == ActionType.ShowCard && context.getTheme().resolveAttribute(R.attr.adaptiveShowCardAction, buttonStyle, true)) {
            context = new ContextThemeWrapper(context, buttonStyle.data);
        }

        Button button = getButtonForStyle(context, baseActionElement.GetStyle(), hostConfig);
        button.setEnabled(baseActionElement.GetIsEnabled());

        if (Util.isOfType(baseActionElement, ExecuteAction.class) || Util.isOfType(baseActionElement, SubmitAction.class))
        {
            long actionId = Util.getViewId(button);
            renderedCard.setCardForSubmitAction(actionId, renderArgs.getContainerCardId());
        }

        button.setText(baseActionElement.GetTitle());
        if (!TextUtils.isEmpty(baseActionElement.GetTooltip()))
        {
            TooltipCompat.setTooltipText(button, baseActionElement.GetTooltip());
        }
        ActionAlignment alignment = hostConfig.GetActions().getActionAlignment();
        ActionsOrientation orientation = hostConfig.GetActions().getActionsOrientation();
        LinearLayout.LayoutParams layoutParams;
        if (orientation == ActionsOrientation.Horizontal)
        {
            layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT);
            long spacing = hostConfig.GetActions().getButtonSpacing();
            layoutParams.rightMargin = Util.dpToPixels(context, spacing);
        }
        else
        {
            layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
        }

        if (alignment == ActionAlignment.Stretch)
        {
            layoutParams.weight = 1f;
        }

        button.setLayoutParams(layoutParams);

        String iconUrl = baseActionElement.GetIconUrl();
        if (!iconUrl.isEmpty())
        {
            IconPlacement iconPlacement = hostConfig.GetActions().getIconPlacement();
            if (!renderArgs.getAllowAboveTitleIconPlacement())
            {
                iconPlacement = IconPlacement.LeftOfTitle;
            }

            Util.loadIcon(context, button, iconUrl, hostConfig, renderedCard, iconPlacement);
        }

        viewGroup.addView(button);

        return button;
    }

    @Override
    public Button render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) {
        if (cardActionHandler == null)
        {
            throw new IllegalArgumentException("Action Handler is null.");
        }

        Button button = renderButton(context, viewGroup, baseActionElement, hostConfig, renderedCard, renderArgs);
        button.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig, renderArgs));

        return button;
    }

    private static ActionElementRenderer s_instance = null;
}
