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
import android.support.v4.app.FragmentManager;
import android.util.TypedValue;
import android.view.ContextThemeWrapper;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.HorizontalScrollView;
import android.widget.LinearLayout;

import io.adaptivecards.R;
import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.ColorsConfig;
import io.adaptivecards.objectmodel.ForegroundColor;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ActionsConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.Sentiment;
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

        private Activity getActivity(Context context)
        {
            while (context instanceof ContextWrapper)
            {
                if (context instanceof Activity)
                {
                    return (Activity)context;
                }
                context = ((ContextWrapper)context).getBaseContext();
            }
            return null;
        }

        @Override
        public void onClick(View v)
        {
            Activity hostingActivity = getActivity(v.getContext());
            if(hostingActivity != null)
            {
                View currentFocusedView = hostingActivity.getCurrentFocus();
                if (currentFocusedView != null)
                {
                    currentFocusedView.clearFocus();
                }
            }

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
                m_invisibleCard.requestFocus();
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
        private long m_iconSize;

        protected ActionElementRendererIconImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String imageBaseUrl, IconPlacement iconPlacement, long iconSize)
        {
            super(renderedCard, containerView, imageBaseUrl);
            m_iconPlacement = iconPlacement;
            m_iconSize = iconSize;
        }

        @Override
        protected Bitmap styleBitmap(Bitmap bitmap)
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

            return Bitmap.createScaledBitmap(bitmap, (int)(imageWidth * 2), (int)(imageHeight * 2), false);
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
                button.setCompoundDrawablesWithIntrinsicBounds(drawableIcon, null, null, null);
                button.requestLayout();
            }
        }
    }

    private int getColor(ForegroundColor color, ColorsConfig colorsConfig)
    {
        io.adaptivecards.objectmodel.ColorConfig colorConfig;
        if (color == ForegroundColor.Accent)
        {
            colorConfig = colorsConfig.getAccent();
        }
        else if (color == ForegroundColor.Attention)
        {
            colorConfig = colorsConfig.getAttention();
        }
        else
        {
            throw new IllegalArgumentException("Unknown color: " + color.toString());
        }

        return android.graphics.Color.parseColor(colorConfig.getDefaultColor());
    }

    private Button createButtonWithTheme(Context context, int theme)
    {
        Context themedContext = new ContextThemeWrapper(context, theme);
        return new Button(themedContext);
    }

    private Button createButton(Context context, String sentiment, HostConfig hostConfig)
    {
        boolean isPositiveSentiment = sentiment.equalsIgnoreCase("Positive");
        boolean isDestructiveSentiment = sentiment.equalsIgnoreCase("Destructive");

        if(isPositiveSentiment || isDestructiveSentiment)
        {
            Resources.Theme theme = context.getTheme();
            TypedValue buttonStyle = new TypedValue();

            if(isPositiveSentiment)
            {
                if(theme.resolveAttribute(R.attr.adaptiveActionPositive, buttonStyle, true))
                {
                    return createButtonWithTheme(context, buttonStyle.data);
                }
                else
                {
                    Button button = new Button(context);
                    button.getBackground().setColorFilter(getColor(ForegroundColor.Accent, hostConfig.GetContainerStyles().getDefaultPalette().getForegroundColors()), PorterDuff.Mode.MULTIPLY);
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
                    button.setTextColor(getColor(ForegroundColor.Attention, hostConfig.GetContainerStyles().getDefaultPalette().getForegroundColors()));
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
            RenderedAdaptiveCard renderedCard)
    {
        Button button = createButton(context, baseActionElement.GetSentiment(), hostConfig);

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
            ActionElementRendererIconImageLoaderAsync imageLoader = new ActionElementRendererIconImageLoaderAsync(
                    renderedCard,
                    button,
                    hostConfig.GetImageBaseUrl(),
                    hostConfig.GetActions().getIconPlacement(),
                    hostConfig.GetActions().getIconSize()
            );
            imageLoader.execute(baseActionElement.GetIconUrl());

            // Only when the icon must be placed to the left of the title, we have to do this
            if (hostConfig.GetActions().getIconPlacement() == IconPlacement.LeftOfTitle) {
                int padding = (int) hostConfig.GetSpacing().getDefaultSpacing();
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
                && hostConfig.GetActions().getShowCard().getActionMode() == ActionMode.Inline)
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
            layoutParams.setMargins(0, Util.dpToPixels(context, hostConfig.GetActions().getShowCard().getInlineTopMargin()), 0, 0);
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
