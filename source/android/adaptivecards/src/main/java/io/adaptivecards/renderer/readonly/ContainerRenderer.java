// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.nfc.Tag;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.objectmodel.CollectionTypeElement;
import io.adaptivecards.objectmodel.ContainerBleedDirection;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BackgroundImageLoaderAsync;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class ContainerRenderer extends BaseCardElementRenderer
{
    protected ContainerRenderer()
    {
    }

    public static ContainerRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ContainerRenderer();
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
            RenderArgs renderArgs) throws AdaptiveFallbackException
    {
        Container container = null;
        if (baseCardElement instanceof Container)
        {
            container = (Container) baseCardElement;
        }
        else if ((container = Container.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Container object model.");
        }

        View separator = setSpacingAndSeparator(context, viewGroup, container.GetSpacing(),container.GetSeparator(), hostConfig, true /* horizontal line */);
        LinearLayout containerView = new LinearLayout(context);
        containerView.setTag(new TagContent(container, separator, viewGroup));
        containerView.setOrientation(LinearLayout.VERTICAL);

        setVisibility(container.GetIsVisible(), containerView);
        setMinHeight(container.GetMinHeight(), containerView, context);

        // Add this two for allowing children to bleed
        containerView.setClipChildren(false);
        containerView.setClipToPadding(false);

        if (container.GetHeight() == HeightType.Stretch)
        {
            containerView.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            containerView.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        }

        VerticalContentAlignment contentAlignment = container.GetVerticalContentAlignment();
        switch (contentAlignment)
        {
            case Center:
                containerView.setGravity(Gravity.CENTER_VERTICAL);
                break;
            case Bottom:
                containerView.setGravity(Gravity.BOTTOM);
                break;
            case Top:
            default:
                containerView.setGravity(Gravity.TOP);
                break;
        }

        ContainerStyle containerStyle = renderArgs.getContainerStyle();
        ContainerStyle styleForThis = GetLocalContainerStyle(container, containerStyle);
        ApplyPadding(styleForThis, containerStyle, containerView, context, hostConfig);
        ApplyBleed(container, containerView, context, hostConfig);

        RenderArgs containerRenderArgs = new RenderArgs(renderArgs);
        containerRenderArgs.setContainerStyle(styleForThis);
        if (!container.GetItems().isEmpty())
        {
            try
            {
                CardRendererRegistration.getInstance().render(renderedCard,
                                                              context,
                                                              fragmentManager,
                                                              containerView,
                                                              container,
                                                              container.GetItems(),
                                                              cardActionHandler,
                                                              hostConfig,
                                                              containerRenderArgs);
            }
            catch (AdaptiveFallbackException e)
            {
                // If the container couldn't be rendered, the separator is removed
                viewGroup.removeView(separator);
                throw e;
            }
        }

        BackgroundImage backgroundImageProperties = container.GetBackgroundImage();
        if (backgroundImageProperties != null && !backgroundImageProperties.GetUrl().isEmpty())
        {
            BackgroundImageLoaderAsync loaderAsync = new BackgroundImageLoaderAsync(
                    renderedCard,
                    context,
                    containerView,
                    hostConfig.GetImageBaseUrl(),
                    context.getResources().getDisplayMetrics().widthPixels,
                    backgroundImageProperties);

            loaderAsync.execute(backgroundImageProperties.GetUrl());
        }

        if (container.GetSelectAction() != null)
        {
            containerView.setClickable(true);
            containerView.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, container.GetSelectAction(), cardActionHandler));
        }

        viewGroup.addView(containerView);
        return containerView;
    }

    public static void ApplyBleed(CollectionTypeElement collectionElement, LinearLayout collectionElementView, Context context, HostConfig hostConfig)
    {
        if (collectionElement.GetBleed() && collectionElement.GetCanBleed())
        {
            int padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
            LinearLayout.LayoutParams layoutParams = (LinearLayout.LayoutParams) collectionElementView.getLayoutParams();
            int marginLeft = layoutParams.leftMargin, marginRight = layoutParams.rightMargin, marginTop = layoutParams.topMargin, marginBottom = layoutParams.bottomMargin;

            ContainerBleedDirection bleedDirection = collectionElement.GetBleedDirection();

            if ((bleedDirection.swigValue() & ContainerBleedDirection.BleedLeft.swigValue()) != ContainerBleedDirection.BleedRestricted.swigValue())
            {
                marginLeft = -padding;
            }

            if ((bleedDirection.swigValue() & ContainerBleedDirection.BleedRight.swigValue()) != ContainerBleedDirection.BleedRestricted.swigValue())
            {
                marginRight = -padding;
            }

            if ((bleedDirection.swigValue() & ContainerBleedDirection.BleedUp.swigValue()) != ContainerBleedDirection.BleedRestricted.swigValue())
            {
                marginTop = -padding;
            }

            if ((bleedDirection.swigValue() & ContainerBleedDirection.BleedDown.swigValue()) != ContainerBleedDirection.BleedRestricted.swigValue())
            {
                marginBottom = -padding;
            }

            layoutParams.setMargins(marginLeft, marginTop, marginRight, marginBottom);
            collectionElementView.setLayoutParams(layoutParams);
        }
    }

    public static void ApplyPadding(ContainerStyle elementContainerStyle, ContainerStyle parentContainerStyle, LinearLayout collectionElementView, Context context, HostConfig hostConfig)
    {
        if (elementContainerStyle != parentContainerStyle)
        {
            int padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
            collectionElementView.setPadding(padding, padding, padding, padding);
            String color = hostConfig.GetBackgroundColor(elementContainerStyle);
            collectionElementView.setBackgroundColor(Color.parseColor(color));
        }
    }

    public static ContainerStyle GetLocalContainerStyle(CollectionTypeElement collectionElement, ContainerStyle parentContainerStyle)
    {
        return (collectionElement.GetStyle().swigValue() == ContainerStyle.None.swigValue() ? parentContainerStyle : collectionElement.GetStyle());
    }

    private static ContainerRenderer s_instance = null;
}
