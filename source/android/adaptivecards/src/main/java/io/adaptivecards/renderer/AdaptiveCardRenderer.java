package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import java.io.IOException;
import java.util.Vector;

public class AdaptiveCardRenderer
{
    public static final double VERSION = 1.0;

    private AdaptiveCardRenderer()
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

    private class BackgroundImageLoader extends AsyncTask<String, Void, HttpRequestResult<Bitmap>>
    {
        private Context m_context;
        private LinearLayout m_layout;
        private RenderedAdaptiveCard m_renderedCard;

        public BackgroundImageLoader(RenderedAdaptiveCard renderedCard, Context context, LinearLayout layout)
        {
            m_context = context;
            m_layout = layout;
            m_renderedCard = renderedCard;
        }

        @Override
        protected HttpRequestResult<Bitmap> doInBackground(String... args)
        {
            try
            {
                Bitmap bitmap;
                byte[] bytes = HttpRequestHelper.get(args[0]);
                if (bytes == null)
                {
                    throw new IOException("Failed to retrieve content from " + args[0]);
                }

                bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

                if (bitmap == null)
                {
                    throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
                }

                return new HttpRequestResult<>(bitmap);
            }
            catch (Exception excep)
            {
                return new HttpRequestResult<>(excep);
            }
        }

        @Override
        protected void onPostExecute(HttpRequestResult<Bitmap> result)
        {
            if(result.isSuccessful())
            {
                BitmapDrawable background = new BitmapDrawable(m_context.getResources(), result.getResult());
                m_layout.setBackground(background);
                m_layout.bringChildToFront(m_layout.getChildAt(0));
            }
            else
            {
                m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
            }
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

        LinearLayout layout = new LinearLayout(context);
        layout.setTag(adaptiveCard);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
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

                renderActions(renderedCard, context, fragmentManager, layout, baseActionElementList, cardActionHandler, hostConfig);
            }
        }
        else
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.INTERACTIVITY_DISALLOWED, "Interactivity is not allowed. Actions not rendered."));
        }

        String imageUrl = adaptiveCard.GetBackgroundImage();
        if (!imageUrl.isEmpty())
        {
            BackgroundImageLoader loaderAsync = new BackgroundImageLoader(renderedCard, context, layout);
            loaderAsync.execute(imageUrl);
        }

        return rootLayout;
    }

    private void renderActions(RenderedAdaptiveCard renderedCard, Context context, FragmentManager fragmentManager, ViewGroup viewGroup, BaseActionElementVector baseActionElementList, ICardActionHandler cardActionHandler, HostConfig hostConfig) {
        long size;
        if (baseActionElementList == null || (size = baseActionElementList.size()) <= 0)
        {
            return;
        }

        LinearLayout actionButtonsLayout = new LinearLayout(context);
        actionButtonsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        int alignment = hostConfig.getActions().getActionAlignment().swigValue();
        if (alignment == ActionAlignment.Right.swigValue())
        {
            actionButtonsLayout.setGravity(Gravity.RIGHT);
        }
        else if (alignment == ActionAlignment.Center.swigValue())
        {
            actionButtonsLayout.setGravity(Gravity.CENTER_HORIZONTAL);
        }

        if (hostConfig.getActions().getActionsOrientation().swigValue() == ActionsOrientation.Vertical.swigValue())
        {
            actionButtonsLayout.setOrientation(LinearLayout.VERTICAL);
        }
        else
        {
            actionButtonsLayout.setOrientation(LinearLayout.HORIZONTAL);
        }

        if (viewGroup != null)
        {
            viewGroup.addView(actionButtonsLayout);
        }

        int i = 0;
        long maxActions = hostConfig.getActions().getMaxActions();
        for (; i < size && i < maxActions; i++)
        {
            BaseActionElement actionElement = baseActionElementList.get(i);
            ActionElementRenderer.getInstance().render(renderedCard, context, fragmentManager, actionButtonsLayout, actionElement, cardActionHandler, hostConfig);
        }

        if (i >= maxActions && size != maxActions)
        {
            renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.MAX_ACTIONS_EXCEEDED, "A maximum of " + maxActions + " actions are allowed"));
        }
    }

    private static AdaptiveCardRenderer s_instance = null;

    private HostConfig defaultHostConfig = new HostConfig();
}
