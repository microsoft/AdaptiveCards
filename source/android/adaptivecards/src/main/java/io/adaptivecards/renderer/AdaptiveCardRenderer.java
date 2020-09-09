// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Color;
import android.os.AsyncTask;
import androidx.fragment.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.InternalId;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.layout.StretchableElementLayout;
import io.adaptivecards.renderer.readonly.ContainerRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class AdaptiveCardRenderer
{
    public static final String VERSION = "1.3";

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
        View cardView = internalRender(result, context, fragmentManager, adaptiveCard, cardActionHandler, hostConfig, false, new InternalId());
        result.setView(cardView);
        return result;
    }

    private ViewGroup renderCardElements(RenderedAdaptiveCard renderedCard,
                                         Context context,
                                         FragmentManager fragmentManager,
                                         AdaptiveCard adaptiveCard,
                                         ICardActionHandler cardActionHandler,
                                         HostConfig hostConfig,
                                         ViewGroup cardLayout,
                                         RenderArgs renderArgs)
    {
        LinearLayout layout = new LinearLayout(context);
        layout.setTag(adaptiveCard);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        layout.setOrientation(LinearLayout.VERTICAL);

        // Add this two for allowing children to bleed
        layout.setClipChildren(false);
        layout.setClipToPadding(false);

        ContainerRenderer.setVerticalContentAlignment(layout, adaptiveCard.GetVerticalContentAlignment());

        try
        {
            CardRendererRegistration.getInstance().renderElements(renderedCard, context, fragmentManager, cardLayout, adaptiveCard.GetBody(), cardActionHandler, hostConfig, renderArgs);
        }
        // Catches the exception as the method throws it for performing fallback with elements inside the card,
        // no fallback should be performed here so we just catch the exception
        catch (AdaptiveFallbackException e){}
        catch (Exception e)
        {
            e.printStackTrace();
        }

        return layout;
    }

    public View internalRender(RenderedAdaptiveCard renderedCard,
                               Context context,
                               FragmentManager fragmentManager,
                               AdaptiveCard adaptiveCard,
                               ICardActionHandler cardActionHandler,
                               HostConfig hostConfig,
                               boolean isInlineShowCard,
                               InternalId containerCardId)
    {
        if (hostConfig == null)
        {
            throw new IllegalArgumentException("hostConfig is null");
        }

        if (renderedCard == null)
        {
            throw new IllegalArgumentException("renderedCard is null");
        }

        // rootLayout is the layout that contains the rendered card (elements + actions) and the show cards
        LinearLayout rootLayout = new LinearLayout(context);
        rootLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        rootLayout.setOrientation(LinearLayout.VERTICAL);
        rootLayout.setFocusable(true);
        rootLayout.setFocusableInTouchMode(true);

        // Add this two for allowing children to bleed
        rootLayout.setClipChildren(false);
        rootLayout.setClipToPadding(false);

        // cardLayout only contains the rendered card composed of elements and actions
        long cardMinHeight = adaptiveCard.GetMinHeight();
        LinearLayout cardLayout = new StretchableElementLayout(context, (adaptiveCard.GetHeight() == HeightType.Stretch) || (cardMinHeight != 0));
        cardLayout.setTag(adaptiveCard);

        // Add this two for allowing children to bleed
        cardLayout.setClipChildren(false);
        cardLayout.setClipToPadding(false);

        ContainerRenderer.setMinHeight(cardMinHeight, rootLayout, context);
        ContainerRenderer.setVerticalContentAlignment(cardLayout, adaptiveCard.GetVerticalContentAlignment());

        cardLayout.setOrientation(LinearLayout.VERTICAL);
        int padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
        cardLayout.setPadding(padding, padding, padding, padding);

        rootLayout.addView(cardLayout);

        ContainerStyle style = ContainerStyle.Default;

        if (isInlineShowCard && hostConfig.GetActions().getShowCard().getStyle() != ContainerStyle.None)
        {
            style = hostConfig.GetActions().getShowCard().getStyle();
        }

        if (hostConfig.GetAdaptiveCard().getAllowCustomStyle() && adaptiveCard.GetStyle() != ContainerStyle.None)
        {
            style = adaptiveCard.GetStyle();
        }

        RenderArgs renderArgs = new RenderArgs();
        renderArgs.setContainerStyle(style);
        renderArgs.setContainerCardId(adaptiveCard.GetInternalId());
        renderedCard.setParentToCard(adaptiveCard.GetInternalId(), containerCardId);

        // Render the body section of the Adaptive Card
        String color = hostConfig.GetBackgroundColor(style);
        cardLayout.setBackgroundColor(Color.parseColor(color));
        cardLayout.addView(renderCardElements(renderedCard, context, fragmentManager, adaptiveCard, cardActionHandler, hostConfig, cardLayout, renderArgs));

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
                        actionLayoutRenderer.renderActions(renderedCard, context, fragmentManager, cardLayout, baseActionElementList, cardActionHandler, hostConfig, renderArgs);
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

        ContainerRenderer.setBackgroundImage(renderedCard, context, adaptiveCard.GetBackgroundImage(), hostConfig, cardLayout);

        BaseActionElement selectAction = renderedCard.getAdaptiveCard().GetSelectAction();
        if (selectAction != null)
        {
            rootLayout.setClickable(true);
            rootLayout.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard,selectAction, cardActionHandler));
        }

        return rootLayout;
    }

    private static AdaptiveCardRenderer s_instance = null;
    private HostConfig defaultHostConfig = new HostConfig();
}
