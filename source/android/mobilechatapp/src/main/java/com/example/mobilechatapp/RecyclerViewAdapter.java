// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import androidx.fragment.app.FragmentManager;
import android.content.Context;
import androidx.recyclerview.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.ProgressBar;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ParseResult;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>
{
    // parent activity will implement this method to respond to click events
    public interface ItemClickListener
    {
        void onItemClick(View view, int position);
    }

    public interface ICardRenderedListener
    {
        void onCardFinishedRendering();
    }

    // stores and recycles views as they are scrolled off screen
    public class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener, ICardRenderedListener
    {
        ViewHolder(View itemView)
        {
            super(itemView);
            m_cardLayout = (LinearLayout) itemView.findViewById(R.id.cardLayout);
            m_jsonFileName = (TextView) itemView.findViewById(R.id.jsonFileName);
            m_progressBar = (ProgressBar) itemView.findViewById(R.id.recyclerViewProgressBar);
            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View view)
        {
            if (m_clickListener != null)
            {
                m_clickListener.onItemClick(view, getAdapterPosition());
            }
        }

        @Override
        public void onCardFinishedRendering()
        {
            m_progressBar.setVisibility(View.GONE);
            if(m_recyclerViewContent != null)
            {
                m_cardLayout.addView(m_recyclerViewContent.getRenderedCard());
            }
        }

        public void registerListener(RecyclerViewContent recyclerViewContent)
        {
            m_recyclerViewContent = recyclerViewContent;
        }

        public void unregisterPreviousListener()
        {
            if(m_recyclerViewContent != null)
            {
                m_recyclerViewContent.unregisterCardRenderedListener();
            }
        }

        ProgressBar m_progressBar;
        LinearLayout m_cardLayout;
        TextView m_jsonFileName;
        RecyclerViewContent m_recyclerViewContent = null;
    }

    RecyclerViewAdapter(Context context)
    {
        m_inflater = LayoutInflater.from(context);
        m_cards = new ArrayList<>();
    }

    @Override
    public ViewHolder onCreateViewHolder(ViewGroup parent, int viewType)
    {
        View view = m_inflater.inflate(R.layout.recyclerview_row, parent, false);
        return new ViewHolder(view);
    }

    @Override
    public void onBindViewHolder(ViewHolder holder, int position)
    {
        RecyclerViewContent viewContent = m_cards.get(position);

        holder.m_jsonFileName.setText(viewContent.getFileName());

        // Clean the layout to make it as original
        while (holder.m_cardLayout.getChildCount() > 2)
        {
            holder.m_cardLayout.removeViewAt(2);
        }
        holder.m_progressBar.setVisibility(View.VISIBLE);

        if(viewContent.hasRenderedCard())
        {
            View renderedCard = viewContent.getRenderedCard();
            ViewGroup parent = (ViewGroup) renderedCard.getParent();
            if (parent != null)
            {
                parent.removeView(renderedCard);
            }

            holder.m_progressBar.setVisibility(View.GONE);
            holder.m_cardLayout.addView(renderedCard);
        }
        else
        {
            holder.unregisterPreviousListener();
            holder.registerListener(viewContent);
            viewContent.registerCardRenderedListener(holder);
        }
    }

    @Override
    public int getItemCount()
    {
        return m_cards.size();
    }

    // allows clicks events to be caught
    void setClickListener(ItemClickListener itemClickListener)
    {
        m_clickListener = itemClickListener;
    }

    void addItem(String filename, ParseResult parseResult, Context context, FragmentManager fragmentManager, ICardActionHandler cardActionHandler, HostConfig hostConfig)
    {
        m_cards.add(new RecyclerViewContent(filename, parseResult, context, fragmentManager, cardActionHandler, hostConfig));
        notifyDataSetChanged();
    }

    void addItem(String fileName, View view)
    {
        m_cards.add(new RecyclerViewContent(fileName, view));
        notifyDataSetChanged();
    }

    private List<RecyclerViewContent> m_cards;
    private LayoutInflater m_inflater;
    private ItemClickListener m_clickListener;
}
