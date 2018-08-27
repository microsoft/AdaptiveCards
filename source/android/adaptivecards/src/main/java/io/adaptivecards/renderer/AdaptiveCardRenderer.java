package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.Spacing;
import io.adaptivecards.objectmodel.VerticalContentAlignment;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestResult;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class AdaptiveCardRenderer
{
    public static final double VERSION = 1.0;

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

    private class BackgroundImageLoaderAsync extends GenericImageLoaderAsync
    {
        private Context m_context;
        private LinearLayout m_layout;

        public BackgroundImageLoaderAsync(RenderedAdaptiveCard renderedCard, Context context, LinearLayout layout, String imageBaseUrl)
        {
            super(renderedCard, imageBaseUrl);

            m_context = context;
            m_layout = layout;
        }

        @Override
        protected HttpRequestResult<Bitmap> doInBackground(String... args)
        {
            if (args.length == 0)
            {
                return null;
            }
            return loadImage(args[0], m_context);
        }

        void onSuccessfulPostExecute(Bitmap bitmap)
        {
            BitmapDrawable background = new BitmapDrawable(m_context.getResources(), bitmap);
            m_layout.setBackground(background);
            m_layout.bringChildToFront(m_layout.getChildAt(0));
        }
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

        LinearLayout layout = new LinearLayout(context);
        layout.setTag(adaptiveCard);

        if( adaptiveCard.GetHeight() == HeightType.Stretch )
        {
            layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
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
        int padding = Util.dpToPixels(context, hostConfig.getSpacing().getPaddingSpacing());
        layout.setPadding(padding, padding, padding, padding);

        rootLayout.addView(layout);

        BaseCardElementVector baseCardElementList = adaptiveCard.GetBody();
        if (baseCardElementList == null || baseCardElementList.size() <= 0)
        {
            throw new IllegalArgumentException("Adaptive Card does not contain a body.");
        }

        ContainerStyle style = ContainerStyle.Default;

        if (isInlineShowCard && hostConfig.getActions().getShowCard().getStyle() != ContainerStyle.None)
        {
            style = hostConfig.getActions().getShowCard().getStyle();
        }

        if (hostConfig.getAdaptiveCard().getAllowCustomStyle() && adaptiveCard.GetStyle() != ContainerStyle.None)
        {
            style = adaptiveCard.GetStyle();
        }

        String color;
        if (style == ContainerStyle.Default)
        {
            color = hostConfig.getContainerStyles().getDefaultPalette().getBackgroundColor();
        }
        else
        {
            color = hostConfig.getContainerStyles().getEmphasisPalette().getBackgroundColor();
        }

        layout.setBackgroundColor(Color.parseColor(color));

        CardRendererRegistration.getInstance().render(renderedCard, context, fragmentManager, layout, adaptiveCard, baseCardElementList, cardActionHandler, hostConfig, style);

        if (hostConfig.getSupportsInteractivity())
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
                if(actionLayoutRenderer != null) {
                    actionLayoutRenderer.renderActions(renderedCard, context, fragmentManager, layout, baseActionElementList, cardActionHandler, hostConfig);
                }
            }
        }
        else
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Interactivity is not allowed. Actions not rendered."));
        }

        String imageUrl = adaptiveCard.GetBackgroundImage();
        if (!imageUrl.isEmpty())
        {
            BackgroundImageLoaderAsync loaderAsync = new BackgroundImageLoaderAsync(renderedCard, context, layout, hostConfig.getImageBaseUrl());

            IOnlineImageLoader onlineImageLoader = CardRendererRegistration.getInstance().getOnlineImageLoader();
            if(onlineImageLoader != null)
            {
                loaderAsync.registerCustomOnlineImageLoader(onlineImageLoader);
            }

            loaderAsync.execute(imageUrl);
        }

        BaseActionElement selectAction = renderedCard.getAdaptiveCard().GetSelectAction();
        if (selectAction != null)
        {
            rootLayout.setClickable(true);
            rootLayout.setOnClickListener(new ActionElementRenderer.ButtonOnClickListener(renderedCard, selectAction, cardActionHandler));
        }

        return rootLayout;
    }

    private static AdaptiveCardRenderer s_instance = null;

    private IOnlineImageLoader m_onlineImageLoader = null;

    private HostConfig defaultHostConfig = new HostConfig();
}
