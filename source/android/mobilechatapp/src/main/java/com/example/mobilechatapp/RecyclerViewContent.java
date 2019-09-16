// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import android.support.v4.app.FragmentManager;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.view.View;

import java.util.List;

import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ParseResult;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class RecyclerViewContent
{

    private class CardRendererTask extends AsyncTask<ParseResult, Void, View>
    {

        public CardRendererTask(Context context, FragmentManager fragmentManager, ICardActionHandler cardActionHandler, HostConfig hostConfig, String filename)
        {
            m_context = context;
            m_fragmentManager = fragmentManager;
            m_cardActionHandler = cardActionHandler;
            m_hostConfig = hostConfig;
            m_filename = filename;
        }

        @Override
        protected View doInBackground(ParseResult... objects) {
            try
            {
                RenderedAdaptiveCard renderedCard = AdaptiveCardRenderer.getInstance().render(m_context, m_fragmentManager, objects[0].GetAdaptiveCard(), m_cardActionHandler, m_hostConfig);
                return renderedCard.getView();
            }
            catch (Exception e)
            {
                Log.e(m_fileName, e.getMessage());
                e.printStackTrace();
                return null;
            }
        }

        @Override
        protected void onPostExecute(View view)
        {
            m_renderedCard = view;
            m_cardHasRendered = true;

            if(m_cardRenderedListener != null)
            {
                m_cardRenderedListener.onCardFinishedRendering();
            }
        }

        public void registerCardRenderedListener(RecyclerViewAdapter.ICardRenderedListener cardRenderedListener)
        {
            m_cardRenderedListener = cardRenderedListener;
        }

        public void unregisterCardRenderedListener()
        {
            m_cardRenderedListener = null;
        }

        private Context m_context;
        private FragmentManager m_fragmentManager;
        private ICardActionHandler m_cardActionHandler;
        private HostConfig m_hostConfig;
        private RecyclerViewAdapter.ICardRenderedListener m_cardRenderedListener = null;
        private String m_filename;
    }


    public RecyclerViewContent(String fileName, ParseResult parseResult, Context context, FragmentManager fragmentManager, ICardActionHandler cardActionHandler, HostConfig hostConfig)
    {
        m_fileName = fileName;
        m_cardHasRendered = false;
        m_renderedCard = null;

        m_cardRendererTask = new CardRendererTask(context, fragmentManager, cardActionHandler, hostConfig, m_fileName);
        m_cardRendererTask.execute(parseResult);
    }

    public RecyclerViewContent(String filename, View view)
    {
        m_fileName = filename;
        m_renderedCard = view;
        m_cardHasRendered = true;
    }

    public String getFileName()
    {
        return m_fileName;
    }

    public View getRenderedCard()
    {
        return m_renderedCard;
    }

    public boolean hasRenderedCard()
    {
        return m_cardHasRendered;
    }

    public void registerCardRenderedListener(RecyclerViewAdapter.ICardRenderedListener cardRenderedListener)
    {
        if( m_cardRendererTask != null )
        {
            m_cardRendererTask.registerCardRenderedListener(cardRenderedListener);
        }
    }

    public void unregisterCardRenderedListener()
    {
        if(m_cardRendererTask != null)
        {
            m_cardRendererTask.unregisterCardRenderedListener();
        }
    }

    private String m_fileName;
    private View m_renderedCard;
    private boolean m_cardHasRendered;
    private CardRendererTask m_cardRendererTask;
}
