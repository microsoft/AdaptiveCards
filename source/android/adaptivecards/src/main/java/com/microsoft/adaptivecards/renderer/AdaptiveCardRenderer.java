package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.AdaptiveCard;
import com.microsoft.adaptivecards.objectmodel.BaseActionElementVector;
import com.microsoft.adaptivecards.objectmodel.BaseCardElementVector;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;
import com.microsoft.adaptivecards.renderer.http.HttpRequestHelper;
import com.microsoft.adaptivecards.renderer.http.HttpRequestResult;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.renderer.registration.ActionRendererRegistration;
import com.microsoft.adaptivecards.renderer.registration.CardRendererRegistration;

import java.io.IOException;
import java.util.Vector;

public class AdaptiveCardRenderer
{
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

    public View render(Context context, FragmentManager fragmentManager, AdaptiveCard adaptiveCard, IShowCardActionHandler showCardActionHandler, ISubmitActionHandler submitActionHandler)
    {
        return render(context, fragmentManager, adaptiveCard, showCardActionHandler, submitActionHandler, defaultHostConfig);
    }

    // AdaptiveCard ObjectModel is binded to the UI and Action
    public View render(
            Context context,
            FragmentManager fragmentManager,
            AdaptiveCard adaptiveCard,
            IShowCardActionHandler showCardActionHandler,
            ISubmitActionHandler submitActionHandler,
            HostConfig hostConfig)
    {
        if (hostConfig == null)
        {
            throw new IllegalArgumentException("hostConfig is null");
        }

        LinearLayout layout = new LinearLayout(context);
        layout.setTag(adaptiveCard);
        layout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        layout.setOrientation(LinearLayout.VERTICAL);
        Vector<IInputHandler> inputHandlerList = new Vector<IInputHandler>();

        BaseCardElementVector baseCardElementList = adaptiveCard.GetBody();
        if (baseCardElementList == null || baseCardElementList.size() <= 0)
        {
            throw new IllegalArgumentException("Adaptive Card does not contain a body.");
        }
        View view = CardRendererRegistration.getInstance().render(context, fragmentManager, layout, adaptiveCard, baseCardElementList, inputHandlerList, hostConfig);

        // Actions are optional
        BaseActionElementVector baseActionElementList = adaptiveCard.GetActions();
        if (baseActionElementList != null && baseActionElementList.size() > 0)
        {
            ActionRendererRegistration.getInstance().render(context, layout, adaptiveCard, baseActionElementList, inputHandlerList, showCardActionHandler, submitActionHandler, hostConfig);
        }

        String imageUrl = adaptiveCard.GetBackgroundImage();
        if (!imageUrl.isEmpty())
        {
            BackgroundImageLoader loaderAsync = new BackgroundImageLoader(context, layout);
            loaderAsync.execute(imageUrl);
        }

        return layout;
    }

    private static AdaptiveCardRenderer s_instance = null;

    private HostConfig defaultHostConfig = new HostConfig();
}
