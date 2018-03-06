package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Color;
import android.graphics.drawable.BitmapDrawable;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElementVector;
import io.adaptivecards.objectmodel.BaseCardElementVector;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;
import io.adaptivecards.renderer.inputhandler.IInputHandler;
import io.adaptivecards.renderer.registration.ActionRendererRegistration;
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

        public BackgroundImageLoader(Context context, LinearLayout layout)
        {
            m_context = context;
            m_layout = layout;
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
        }
    }

    public View render(
            Context context,
            FragmentManager fragmentManager,
            AdaptiveCard adaptiveCard,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig)
    {
        return render(context, fragmentManager, adaptiveCard, cardActionHandler, hostConfig, new Vector<IInputHandler>(), false);
    }

    public View render(Context context, FragmentManager fragmentManager, AdaptiveCard adaptiveCard, ICardActionHandler cardActionHandler)
    {
        return render(context, fragmentManager, adaptiveCard, cardActionHandler, defaultHostConfig, new Vector<IInputHandler>(), false);
    }

    // AdaptiveCard ObjectModel is binded to the UI and Action
    public View render(
            Context context,
            FragmentManager fragmentManager,
            AdaptiveCard adaptiveCard,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            Vector<IInputHandler> inputHandlerList,
            boolean isInlineShowCard)
    {
        if (hostConfig == null)
        {
            throw new IllegalArgumentException("hostConfig is null");
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

        if (isInlineShowCard && hostConfig.getActions().getShowCard().getStyle().swigValue() != ContainerStyle.None.swigValue())
        {
            style = hostConfig.getActions().getShowCard().getStyle();
        }

        if (hostConfig.getAdaptiveCard().getAllowCustomStyle() && adaptiveCard.GetStyle().swigValue() != ContainerStyle.None.swigValue())
        {
            style = adaptiveCard.GetStyle();
        }

        String color;
        if (style.swigValue() == ContainerStyle.Default.swigValue())
        {
            color = hostConfig.getContainerStyles().getDefaultPalette().getBackgroundColor();
        }
        else
        {
            color = hostConfig.getContainerStyles().getEmphasisPalette().getBackgroundColor();
        }

        layout.setBackgroundColor(Color.parseColor(color));

        CardRendererRegistration.getInstance().render(context, fragmentManager, layout, adaptiveCard, baseCardElementList, inputHandlerList, cardActionHandler, hostConfig, style);

        // Actions are optional
        BaseActionElementVector baseActionElementList = adaptiveCard.GetActions();
        if (baseActionElementList != null && baseActionElementList.size() > 0)
        {
            LinearLayout showCardsLayout = new LinearLayout(context);
            showCardsLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
            rootLayout.addView(showCardsLayout);

            ActionRendererRegistration.getInstance().render(context, fragmentManager, layout, adaptiveCard, baseActionElementList, inputHandlerList, cardActionHandler, hostConfig);
        }

        String imageUrl = adaptiveCard.GetBackgroundImage();
        if (!imageUrl.isEmpty())
        {
            BackgroundImageLoader loaderAsync = new BackgroundImageLoader(context, layout);
            loaderAsync.execute(imageUrl);
        }

        return rootLayout;
    }

    private static AdaptiveCardRenderer s_instance = null;

    private HostConfig defaultHostConfig = new HostConfig();
}
