// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Color;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class AdaptiveCardRenderer
{
    public static final String VERSION = "1.2";

    protected AdaptiveCardRenderer()
    {
    }

    public static AdaptiveCardRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new AdaptiveCardRenderer();
        }

        return s_instance;
    }

    public RenderedAdaptiveCard render(Context context, FragmentManager fragmentManager, AdaptiveCard adaptiveCard, ICardActionHandler cardActionHandler)
    {
        return render(context, fragmentManager, adaptiveCard, cardActionHandler, defaultHostConfig);
    }

    // AdaptiveCard ObjectModel is binded to the UI and Action
    public RenderedAdaptiveCard render(
            Context context,
            FragmentManager fragmentManager,
            AdaptiveCard adaptiveCard,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig)
    {
        RenderedAdaptiveCard result = new RenderedAdaptiveCard(adaptiveCard);
        View cardView = internalRender(result, context, fragmentManager, adaptiveCard, cardActionHandler, hostConfig, false);
        result.setView(cardView);
        return result;
    }

    public View internalRender(RenderedAdaptiveCard renderedCard,
                               Context context,
                               FragmentManager fragmentManager,
                               AdaptiveCard adaptiveCard,
                               ICardActionHandler cardActionHandler,
                               HostConfig hostConfig,
                               boolean isInlineShowCard)
    {
        if (hostConfig == null)
        {
            throw new IllegalArgumentException("hostConfig is null");
        }

        if (renderedCard == null)
        {
            throw new IllegalArgumentException("renderedCard is null");
        }

        LinearLayout rootLayout = new LinearLayout(context);
        rootLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        rootLayout.setOrientation(LinearLayout.VERTICAL);
        rootLayout.setFocusable(true);
        rootLayout.setFocusableInTouchMode(true);

        // Add this two for allowing children to bleed
        rootLayout.setClipChildren(false);
        rootLayout.setClipToPadding(false);

        LinearLayout layout = new LinearLayout(context);
        layout.setTag(adaptiveCard);

        // Add this two for allowing children to bleed
        layout.setClipChildren(false);
        layout.setClipToPadding(false);

        boolean cardHasMinHeightSet = (adaptiveCard.GetMinHeight() != 0);
        if ((adaptiveCard.GetHeight() == HeightType.Stretch) || cardHasMinHeightSet)
        {
            layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        }

        if (cardHasMinHeightSet)
        {
            rootLayout.setMinimumHeight(Util.dpToPixels(context, (int)adaptiveCard.GetMinHeight()));
        }

        VerticalContentAlignment contentAlignment = adaptiveCard.GetVerticalContentAlignment();
        switch (contentAlignment)
        {
            case Center:
                layout.setGravity(Gravity.CENTER_VERTICAL);
                break;
            case Bottom:
                layout.setGravity(Gravity.BOTTOM);
                break;
            case Top:
            default:
                layout.setGravity(Gravity.TOP);
                break;
        }

        layout.setOrientation(LinearLayout.VERTICAL);
        int padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
        layout.setPadding(padding, padding, padding, padding);

        rootLayout.addView(layout);

        BaseCardElementVector baseCardElementList = adaptiveCard.GetBody();

        ContainerStyle style = ContainerStyle.Default;

        if (isInlineShowCard && hostConfig.GetActions().getShowCard().getStyle() != ContainerStyle.None)
        {
            style = hostConfig.GetActions().getShowCard().getStyle();
        }

        if (hostConfig.GetAdaptiveCard().getAllowCustomStyle() && adaptiveCard.GetStyle() != ContainerStyle.None)
        {
            style = adaptiveCard.GetStyle();
        }

        String color = hostConfig.GetBackgroundColor(style);

        layout.setBackgroundColor(Color.parseColor(color));

        RenderArgs renderArgs = new RenderArgs();
        renderArgs.setContainerStyle(style);
        try
        {
            CardRendererRegistration.getInstance().render(renderedCard, context, fragmentManager, layout, adaptiveCard, baseCardElementList, cardActionHandler, hostConfig, renderArgs);
        }
        // Catches the exception as the method throws it for performing fallback with elements inside the card,
        // no fallback should be performed here so we just catch the exception
        catch (AdaptiveFallbackException e){}

        if (hostConfig.GetSupportsInteractivity())
        {
            // Actions are optional
            BaseActionElementVector baseActionElementList = adaptiveCard.GetActions();
            if (baseActionElementList != null && baseActionElementList.size() > 0)
            {
                LinearLayout showCardsLayout = new LinearLayout(context);
                showCardsLayout.setBackgroundColor(Color.parseColor(color));
                showCardsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
                rootLayout.addView(showCardsLayout);

                IActionLayoutRenderer actionLayoutRenderer = CardRendererRegistration.getInstance().getActionLayoutRenderer();
                if(actionLayoutRenderer != null)
                {
                    try
                    {
                        actionLayoutRenderer.renderActions(renderedCard, context, fragmentManager, layout, baseActionElementList, cardActionHandler, hostConfig, renderArgs);
                    }
                    // Catches the exception as the method throws it for performing fallback with elements inside the card,
                    // no fallback should be performed here so we just catch the exception
                    catch (AdaptiveFallbackException e) {}
                }
            }
        }
        else
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Interactivity is not allowed. Actions not rendered."));
        }

        BackgroundImage backgroundImageProperties = adaptiveCard.GetBackgroundImage();
        if (backgroundImageProperties != null && !backgroundImageProperties.GetUrl().isEmpty())
        {
            BackgroundImageLoaderAsync loaderAsync = new BackgroundImageLoaderAsync(
                    renderedCard,
                    context,
                    layout,
                    hostConfig.GetImageBaseUrl(),
                    context.getResources().getDisplayMetrics().widthPixels,
                    backgroundImageProperties);

            IOnlineImageLoader onlineImageLoader = CardRendererRegistration.getInstance().getOnlineImageLoader();
            if (onlineImageLoader != null)
            {
                loaderAsync.registerCustomOnlineImageLoader(onlineImageLoader);
            }

            loaderAsync.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, backgroundImageProperties.GetUrl());
        }

        BaseActionElement selectAction = renderedCard.getAdaptiveCard().GetSelectAction();
        if (selectAction != null)
        {
            rootLayout.setClickable(true);
            rootLayout.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard,selectAction, cardActionHandler));
        }

        return rootLayout;
    }

    private static AdaptiveCardRenderer s_instance = null;
    private IOnlineImageLoader m_onlineImageLoader = null;
    private HostConfig defaultHostConfig = new HostConfig();
}
