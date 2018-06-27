package io.adaptivecards.renderer.action;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class ActionElementRenderer implements IBaseActionElementRenderer
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

    public static class ButtonOnClickListener implements View.OnClickListener
    {

        public ButtonOnClickListener(RenderedAdaptiveCard renderedCard, BaseActionElement action, ICardActionHandler cardActionHandler)
        {
            m_action = action;
            m_renderedAdaptiveCard = renderedCard;
            m_cardActionHandler = cardActionHandler;
        }

        @Override
        public void onClick(View v)
        {
            m_cardActionHandler.onAction(m_action, m_renderedAdaptiveCard);
        }

        private BaseActionElement m_action;
        private RenderedAdaptiveCard m_renderedAdaptiveCard;
        private ICardActionHandler m_cardActionHandler;
    }

    public static class ButtonOnLayoutChangedListener implements View.OnLayoutChangeListener
    {
        @Override
        public void onLayoutChange(View v, int left, int top, int right, int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom)
        {
            Button button = (Button)v;

            double textHeight = button.getTextSize();

            Rect bounds = new Rect();
            String text = button.getText().toString().toUpperCase();

            Paint paint = button.getPaint();
            paint.setTextSize((float) textHeight);
            paint.getTextBounds(text, 0, text.length(), bounds);

            Drawable[] icons = button.getCompoundDrawables();
            if(icons[0] != null) {
                double iconWidth = icons[0].getIntrinsicWidth();
                double buttonWidth = button.getWidth();
                double boundsWidth = bounds.width();
                double iconStartPosition = (buttonWidth - (iconWidth + mPadding + boundsWidth)) / 2;

                button.setCompoundDrawablePadding((int) (-iconStartPosition + mPadding));
                button.setPadding((int) iconStartPosition, 0, 0, 0);
            }
        }

        void setPadding(int padding){
            mPadding = padding;
        }

        private int mPadding;
    }

    protected class ShowCardInlineClickListener implements View.OnClickListener
    {
        public ShowCardInlineClickListener(View invisibleCard, ViewGroup hiddenCardsLayout)
        {
            m_invisibleCard = invisibleCard;
            m_hiddenCardsLayout = hiddenCardsLayout;
        }

        @Override
        public void onClick(View v)
        {
            v.setPressed(m_invisibleCard.getVisibility() != View.VISIBLE);
            for(int i = 0; i < m_hiddenCardsLayout.getChildCount(); ++i)
            {
                View child = m_hiddenCardsLayout.getChildAt(i);
                if (child != m_invisibleCard)
                {
                    child.setVisibility(View.GONE);
                }
            }

            m_invisibleCard.setVisibility(m_invisibleCard.getVisibility() == View.VISIBLE ? View.GONE : View.VISIBLE);

            View mainCardView = ((ViewGroup) m_hiddenCardsLayout.getParent()).getChildAt(0);
            int padding = mainCardView.getPaddingTop();

            //remove bottom padding from top linear layout
            if (m_invisibleCard.getVisibility() == View.VISIBLE)
            {
                mainCardView.setPadding(padding, padding, padding, 0);
            }
            else
            {
                mainCardView.setPadding(padding, padding, padding, padding);
            }
        }
        private View m_invisibleCard;
        private ViewGroup m_hiddenCardsLayout;
    }

    private class ActionElementRendererIconImageLoaderAsync extends InnerImageLoaderAsync
    {
        private IconPlacement m_iconPlacement;

        protected ActionElementRendererIconImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String imageBaseUrl, IconPlacement iconPlacement)
        {
            super(renderedCard, containerView, imageBaseUrl);
            m_iconPlacement = iconPlacement;
        }

        @Override
        protected Bitmap styleBitmap(Bitmap bitmap)
        {
            Button button = (Button) super.m_view;

            Drawable originalDrawableIcon = new BitmapDrawable(null, bitmap);
            double imageHeight = button.getTextSize();
            double scaleRatio = imageHeight / originalDrawableIcon.getIntrinsicHeight();
            double imageWidth = scaleRatio * originalDrawableIcon.getIntrinsicWidth();

            return Bitmap.createScaledBitmap(bitmap, (int)(imageWidth * 2), (int)(imageHeight * 2), false);
        }

        @Override
        protected void renderBitmap(Bitmap bitmap) {
            Button button = (Button) super.m_view;
            Drawable drawableIcon = new BitmapDrawable(null, bitmap);

            if( m_iconPlacement == IconPlacement.AboveTitle ) {
                button.setCompoundDrawablesWithIntrinsicBounds(null, drawableIcon, null, null);
            } else {
                button.setCompoundDrawablesWithIntrinsicBounds(drawableIcon, null, null, null);
                button.requestLayout();
            }
        }
    }

    public Button renderButton(
            Context context,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            HostConfig hostConfig,
            RenderedAdaptiveCard renderedCard)
    {
        Button button = new Button(context);
        button.setText(baseActionElement.GetTitle());
        ActionAlignment alignment = hostConfig.getActions().getActionAlignment();
        ActionsOrientation orientation = hostConfig.getActions().getActionsOrientation();
        LinearLayout.LayoutParams layoutParams;
        if (orientation == ActionsOrientation.Horizontal)
        {
            layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.MATCH_PARENT);
            long spacing = hostConfig.getActions().getButtonSpacing();
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
        if( !iconUrl.isEmpty() ) {
            ActionElementRendererIconImageLoaderAsync imageLoader = new ActionElementRendererIconImageLoaderAsync(renderedCard, button, hostConfig.getImageBaseUrl(), hostConfig.getActions().getIconPlacement());
            imageLoader.execute(baseActionElement.GetIconUrl());

            // Only when the icon must be placed to the left of the title, we have to do this
            if (hostConfig.getActions().getIconPlacement() == IconPlacement.LeftOfTitle) {
                int padding = (int) hostConfig.getSpacing().getDefaultSpacing();
                ButtonOnLayoutChangedListener layoutChangedListener = new ButtonOnLayoutChangedListener();
                layoutChangedListener.setPadding(padding);
                button.addOnLayoutChangeListener(layoutChangedListener);
            }
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
            HostConfig hostConfig) {
        if (cardActionHandler == null)
        {
            throw new IllegalArgumentException("Action Handler is null.");
        }

        Button button = renderButton(context, viewGroup, baseActionElement, hostConfig, renderedCard);

        if (baseActionElement.GetElementType() == ActionType.ShowCard
                && hostConfig.getActions().getShowCard().getActionMode() == ActionMode.Inline)
        {

            ShowCardAction showCardAction = null;
            if (baseActionElement instanceof ShowCardAction)
            {
                showCardAction = (ShowCardAction) baseActionElement;
            }
            else if ((showCardAction = ShowCardAction.dynamic_cast(baseActionElement)) == null)
            {
                throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
            }

            View invisibleCard = AdaptiveCardRenderer.getInstance().internalRender(renderedCard, context, fragmentManager, showCardAction.GetCard(), cardActionHandler, hostConfig, true);
            invisibleCard.setVisibility(View.GONE);
            LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
            layoutParams.setMargins(0, Util.dpToPixels(context, hostConfig.getActions().getShowCard().getInlineTopMargin()), 0, 0);
            invisibleCard.setLayoutParams(layoutParams);

            ViewGroup parent = (ViewGroup) viewGroup.getParent();
            if(parent instanceof HorizontalScrollView) // Required when the actions are set in horizontal
            {
                parent = (ViewGroup) parent.getParent().getParent();
            }
            else
            {
                parent = (ViewGroup) parent.getParent();
            }

            ViewGroup hiddenCards = (ViewGroup) parent.getChildAt(1);
            hiddenCards.addView(invisibleCard);

            button.setOnClickListener(new ShowCardInlineClickListener(invisibleCard, hiddenCards));
        }
        else
        {
            button.setOnClickListener(new ButtonOnClickListener(renderedCard, baseActionElement, cardActionHandler));
        }
        return button;
    }

    private static ActionElementRenderer s_instance = null;
}
