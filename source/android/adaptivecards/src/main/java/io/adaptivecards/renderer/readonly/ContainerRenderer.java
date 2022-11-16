// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.GradientDrawable;
import android.os.AsyncTask;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import androidx.appcompat.widget.TooltipCompat;
import androidx.fragment.app.FragmentManager;

import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.Container;
import io.adaptivecards.objectmodel.ContainerBleedDirection;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ExecuteAction;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.objectmodel.StyledCollectionElement;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BackgroundImageLoaderAsync;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.layout.StretchableElementLayout;
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
            RenderArgs renderArgs) throws Exception
    {
        Container container = Util.castTo(baseCardElement, Container.class);

        StretchableElementLayout containerView = new StretchableElementLayout(context, container.GetHeight() == HeightType.Stretch);
        containerView.setTag(new TagContent(container));
        containerView.setOrientation(LinearLayout.VERTICAL);

        setMinHeight(container.GetMinHeight(), containerView, context);

        // Add this two for allowing children to bleed
        containerView.setClipChildren(false);
        containerView.setClipToPadding(false);

        applyVerticalContentAlignment(containerView, container.GetVerticalContentAlignment());

        ContainerStyle containerStyle = renderArgs.getContainerStyle();
        ContainerStyle styleForThis = getLocalContainerStyle(container, containerStyle);
        applyPadding(styleForThis, containerStyle, containerView, hostConfig);
        applyContainerStyle(styleForThis, containerStyle, containerView, hostConfig);
        applyBleed(container, containerView, context, hostConfig);
        BaseCardElementRenderer.applyRtl(container.GetRtl(), containerView);

        RenderArgs containerRenderArgs = new RenderArgs(renderArgs);
        containerRenderArgs.setContainerStyle(styleForThis);
        containerRenderArgs.setHorizontalAlignment(HorizontalAlignment.Left);
        containerRenderArgs.setAncestorHasSelectAction(renderArgs.getAncestorHasSelectAction() || (container.GetSelectAction() != null));
        if (!container.GetItems().isEmpty())
        {
            try
            {
                CardRendererRegistration.getInstance().renderElements(renderedCard,
                                                              context,
                                                              fragmentManager,
                                                              containerView,
                                                              container.GetItems(),
                                                              cardActionHandler,
                                                              hostConfig,
                                                              containerRenderArgs);
            }
            catch (AdaptiveFallbackException e)
            {
                throw e;
            }
        }

        ContainerRenderer.setBackgroundImage(renderedCard, context, container.GetBackgroundImage(), hostConfig, containerView);
        setSelectAction(renderedCard, container.GetSelectAction(), containerView, cardActionHandler, renderArgs);

        viewGroup.addView(containerView);
        return containerView;
    }

    /**
     * Vertically align content within the given container
     * @param container Layout whose children need to be vertically aligned
     * @param verticalContentAlignment Alignment attribute
     */
    public static void applyVerticalContentAlignment(LinearLayout container, VerticalContentAlignment verticalContentAlignment)
    {
        int gravity = Gravity.TOP;
        if(verticalContentAlignment == VerticalContentAlignment.Center)
        {
            gravity = Gravity.CENTER;
        }
        else if(verticalContentAlignment == VerticalContentAlignment.Bottom)
        {
            gravity = Gravity.BOTTOM;
        }
        container.setGravity(gravity);
    }

    /**
     * @deprecated renamed to {@link #applyBleed}
     */
    public static void ApplyBleed(StyledCollectionElement collectionElement, ViewGroup collectionElementView, Context context, HostConfig hostConfig)
    {
        applyBleed(collectionElement, collectionElementView, context, hostConfig);
    }

    public static void applyBleed(StyledCollectionElement collectionElement, ViewGroup collectionElementView, Context context, HostConfig hostConfig)
    {
        if (collectionElement.GetBleed() && collectionElement.GetCanBleed())
        {
            int padding = Util.dpToPixels(context, hostConfig.GetSpacing().getPaddingSpacing());
            ViewGroup.MarginLayoutParams layoutParams = (ViewGroup.MarginLayoutParams) collectionElementView.getLayoutParams();
            // TODO: Check RTL support
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

    /**
     * @deprecated Separated into specific {@link #applyPadding} and {@link #applyContainerStyle}.
     */
    public static void ApplyPadding(ContainerStyle computedContainerStyle, ContainerStyle parentContainerStyle, ViewGroup collectionElementView, HostConfig hostConfig)
    {
        applyPadding(computedContainerStyle, parentContainerStyle, collectionElementView, hostConfig);
        applyContainerStyle(computedContainerStyle, parentContainerStyle, collectionElementView, hostConfig);
    }

    public static void applyPadding(ContainerStyle computedContainerStyle, ContainerStyle parentContainerStyle, ViewGroup collectionElementView, HostConfig hostConfig)
    {
        applyPadding(computedContainerStyle, parentContainerStyle, collectionElementView, hostConfig, false);
    }

    public static void applyPadding(ContainerStyle computedContainerStyle, ContainerStyle parentContainerStyle, ViewGroup collectionElementView, HostConfig hostConfig, boolean hasBorder)
    {
        if (hasBorder || computedContainerStyle != parentContainerStyle)
        {
            int padding = Util.dpToPixels(collectionElementView.getContext(), hostConfig.GetSpacing().getPaddingSpacing());
            collectionElementView.setPadding(padding, padding, padding, padding);
        }
    }

    public static void applyContainerStyle(ContainerStyle computedContainerStyle, ContainerStyle parentContainerStyle, ViewGroup collectionElementView, HostConfig hostConfig)
    {
        if (computedContainerStyle != parentContainerStyle)
        {
            String backgroundColor = hostConfig.GetBackgroundColor(computedContainerStyle);
            int color = Color.parseColor(backgroundColor);
            if (collectionElementView.getBackground() instanceof GradientDrawable)
            {
                ((GradientDrawable) collectionElementView.getBackground()).setColor(color);
            }
            else
            {
                collectionElementView.setBackgroundColor(color);
            }
        }
    }

    /**
     * @deprecated renamed to {@link #getLocalContainerStyle}
     */
    public static ContainerStyle GetLocalContainerStyle(StyledCollectionElement collectionElement, ContainerStyle parentContainerStyle)
    {
        return getLocalContainerStyle(collectionElement, parentContainerStyle);
    }

    public static ContainerStyle getLocalContainerStyle(StyledCollectionElement collectionElement, ContainerStyle parentContainerStyle)
    {
        return computeContainerStyle(collectionElement.GetStyle(), parentContainerStyle);
    }

    /**
     * Compute the style to apply to a container given its declared and inherited styles.
     * @param declared the ContainerStyle declared on a container element
     * @param inherited the ContainerStyle inherited through RenderArgs provided by parent
     * @return the ContainerStyle to apply
     */
    public static ContainerStyle computeContainerStyle(ContainerStyle declared, ContainerStyle inherited)
    {
        return declared == ContainerStyle.None ? inherited : declared;
    }

    public static void setBackgroundImage(RenderedAdaptiveCard renderedCard,
                                          Context context,
                                          BackgroundImage backgroundImage,
                                          HostConfig hostConfig,
                                          ViewGroup containerView)
    {
        if (backgroundImage != null)
        {
            String backgroundImageUrl = backgroundImage.GetUrl();

            if (!backgroundImageUrl.isEmpty())
            {
                BackgroundImageLoaderAsync loaderAsync = new BackgroundImageLoaderAsync(
                    renderedCard,
                    context,
                    containerView,
                    hostConfig.GetImageBaseUrl(),
                    context.getResources().getDisplayMetrics().widthPixels,
                    backgroundImage);

                IOnlineImageLoader onlineImageLoader = CardRendererRegistration.getInstance().getOnlineImageLoader();
                if (onlineImageLoader != null)
                {
                    loaderAsync.registerCustomOnlineImageLoader(onlineImageLoader);
                }

                loaderAsync.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, backgroundImageUrl);
            }
        }
    }

    public static void applyTitleAndTooltip(BaseActionElement selectAction, View view)
    {
        String contentDescription = !TextUtils.isEmpty(selectAction.GetTitle()) ? selectAction.GetTitle() : selectAction.GetTooltip();
        String tooltip = !TextUtils.isEmpty(selectAction.GetTooltip()) ? selectAction.GetTooltip() : selectAction.GetTitle();
        if (!TextUtils.isEmpty(contentDescription))
        {
            view.setContentDescription(contentDescription);
        }
        if (!TextUtils.isEmpty(tooltip))
        {
            TooltipCompat.setTooltipText(view, tooltip);
        }
    }


    public static void setSelectAction(RenderedAdaptiveCard renderedCard, BaseActionElement selectAction, View view, ICardActionHandler cardActionHandler, RenderArgs renderArgs)
    {
        if (selectAction != null)
        {
            view.setFocusable(true);
            view.setClickable(true);
            view.setEnabled(selectAction.GetIsEnabled());
            if (Util.isOfType(selectAction, ExecuteAction.class) || Util.isOfType(selectAction, SubmitAction.class) || selectAction.GetElementType() == ActionType.Custom)
            {
                renderedCard.registerSubmitableAction(view, renderArgs);
            }

            view.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, selectAction, cardActionHandler));

            applyTitleAndTooltip(selectAction, view);
        }
    }

    private static ContainerRenderer s_instance = null;
}
