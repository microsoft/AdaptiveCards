package io.adaptivecards.renderer.action;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapShader;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.Shader;
import android.graphics.Typeface;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.LinearLayout;

import java.io.IOException;

import io.adaptivecards.objectmodel.ActionAlignment;
import io.adaptivecards.objectmodel.ActionMode;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.ActionsOrientation;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.ImageStyle;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.IBaseActionElementRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;

public class ActionElementRenderer implements IBaseActionElementRenderer
{
    private ActionElementRenderer()
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

    private class ImageLoaderAsync2 extends AsyncTask<String, Void, HttpRequestResult<Bitmap>>
    {
        ImageLoaderAsync2(RenderedAdaptiveCard renderedCard, Context context, View containerView, ImageStyle imageStyle)
        {
            m_context = context;
            m_view = containerView;
            m_imageStyle = imageStyle;
            m_renderedCard = renderedCard;
        }

        @Override
        protected HttpRequestResult<Bitmap> doInBackground(String... args)
        {
            try
            {
                Bitmap bitmap = null;
                byte[] bytes = HttpRequestHelper.get(args[0]);
                if (bytes == null)
                {
                    throw new IOException("Failed to retrieve content from " + args[0]);
                }

                bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
                if (bitmap != null && m_imageStyle == ImageStyle.Person && (m_view instanceof ImageView))
                {
                    Bitmap circleBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
                    BitmapShader shader = new BitmapShader(bitmap,  Shader.TileMode.CLAMP, Shader.TileMode.CLAMP);
                    Paint paint = new Paint();
                    paint.setShader(shader);
                    Canvas c = new Canvas(circleBitmap);
                    c.drawCircle(bitmap.getWidth()/2, bitmap.getHeight()/2, bitmap.getWidth()/2, paint);
                    bitmap = circleBitmap;
                }

                if (bitmap == null)
                {
                    throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
                }

                return new HttpRequestResult<Bitmap>(bitmap);
            }
            catch (Exception excep)
            {
                return new HttpRequestResult<Bitmap>(excep);
            }
        }

        @Override
        protected void onPostExecute(HttpRequestResult<Bitmap> result)
        {
            if (result.isSuccessful())
            {
                if( m_view instanceof ImageView ) {
                    ImageView view = (ImageView) m_view ;
                    view.setImageBitmap(result.getResult());
                } else if(m_view instanceof Button){
                    Button button = (Button) m_view;
                    Drawable drawable = new BitmapDrawable(null, result.getResult());
                    double textHeight = button.getTextSize();
                    double scaleRatio = textHeight / drawable.getIntrinsicHeight();
                    double imageWidth = scaleRatio * drawable.getIntrinsicWidth();

                    Paint paint = button.getPaint();
                    Rect bounds = new Rect();
                    String text = button.getText().toString().toUpperCase();

                    // paint.setTypeface(Typeface.DEFAULT);
                    paint.setTextSize((float)textHeight);
                    paint.getTextBounds(text, 0, text.length(), bounds);
                    double buttonWidth = button.getWidth(); // <- this is getting 0 when card is hidden
                    double buttonPadding = button.getCompoundDrawablePadding();
                    double boundsWidth  =  bounds.width();
                    double startPosition = (buttonWidth - (imageWidth + buttonPadding + boundsWidth)) / 2;

                    button.setCompoundDrawablePadding((int)(-startPosition + buttonPadding));
                    button.setPadding((int)startPosition, 0, 0, 0);

                    drawable.setBounds(0, 0, (int) (imageWidth), (int)textHeight );
                    button.setCompoundDrawables(drawable, null, null, null);
                }
            }
            else
            {
                m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
            }
        }

        private Context m_context;
        private View m_view; // button and imageview inherit from this
        private ImageStyle m_imageStyle;
        private RenderedAdaptiveCard m_renderedCard;
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
        int padding = 8;
        if(hostConfig.getActions().getIconPlacement() == IconPlacement.LeftOfTitle){
            padding = (int)hostConfig.getSpacing().getDefaultSpacing();
        }
        button.setCompoundDrawablePadding(padding);

        ImageLoaderAsync2 imageLoader = new ImageLoaderAsync2(renderedCard, context, button, null);
        imageLoader.execute("https://img.ifcdn.com/images/86f8b2e76659c6be8c566f0f0d353aaa89b8b8f7e8db5b49678cf982728aaff0_1.jpg");
        // imageLoader.execute(baseActionElement.GetIconUrl());
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

            ViewGroup parent = (ViewGroup) viewGroup.getParent().getParent();

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
