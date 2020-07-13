// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.action;

import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.util.TypedValue;
import android.view.ContextThemeWrapper;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import java.util.HashMap;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.IsVisible;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.objectmodel.ToggleInput;
import io.adaptivecards.objectmodel.ToggleVisibilityAction;
import io.adaptivecards.objectmodel.ToggleVisibilityTarget;
import io.adaptivecards.objectmodel.ToggleVisibilityTargetVector;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
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

    private class ActionElementRendererIconImageLoaderAsync extends InnerImageLoaderAsync
    {
        private IconPlacement m_iconPlacement;
        private long m_iconSize;
        private long m_padding;
        private Context m_context;

        protected ActionElementRendererIconImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String imageBaseUrl, IconPlacement iconPlacement, long iconSize, long padding, Context context)
        {
            super(renderedCard, containerView, imageBaseUrl, containerView.getResources().getDisplayMetrics().widthPixels);
            m_iconPlacement = iconPlacement;
            m_iconSize = iconSize;
            m_padding = padding;
            m_context = context;
        }

        @Override
        public Bitmap styleBitmap(Bitmap bitmap)
        {
            Button button = (Button) super.m_view;

            Drawable originalDrawableIcon = new BitmapDrawable(null, bitmap);

            double imageHeight;
            if (m_iconPlacement == IconPlacement.AboveTitle)
            {
                // If icon is above title, iconSize should be used as the height of the image
                imageHeight = m_iconSize;
            }
            else
            {
                // Otherwise, the height of the image should be the height of the action's text
                imageHeight = button.getTextSize();
            }

            double scaleRatio = imageHeight / originalDrawableIcon.getIntrinsicHeight();
            double imageWidth = scaleRatio * originalDrawableIcon.getIntrinsicWidth();

            return Bitmap.createScaledBitmap(bitmap, Util.dpToPixels(m_context, (int)imageWidth), Util.dpToPixels(m_context, (int)imageHeight), false);
        }

        @Override
        protected void renderBitmap(Bitmap bitmap) {
            Button button = (Button) super.m_view;
            Drawable drawableIcon = new BitmapDrawable(null, bitmap);

            if (m_iconPlacement == IconPlacement.AboveTitle)
            {
                button.setCompoundDrawablesWithIntrinsicBounds(null, drawableIcon, null, null);
            }
            else
            {
                button.setCompoundDrawablesRelativeWithIntrinsicBounds(drawableIcon, null, null, null);
                button.setCompoundDrawablePadding(Util.dpToPixels(m_context, (int) m_padding));
            }
        }
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

        button.setText(baseActionElement.GetTitle());
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

            ActionElementRendererIconImageLoaderAsync imageLoader = new ActionElementRendererIconImageLoaderAsync(
                    renderedCard,
                    button,
                    hostConfig.GetImageBaseUrl(),
                    iconPlacement,
                    hostConfig.GetActions().getIconSize(),
                    hostConfig.GetSpacing().getDefaultSpacing(),
                    context
            );
            imageLoader.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, baseActionElement.GetIconUrl());
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
        button.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig));

        return button;
    }

    private static ActionElementRenderer s_instance = null;
}
