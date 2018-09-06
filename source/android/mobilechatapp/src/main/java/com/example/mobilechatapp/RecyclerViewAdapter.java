package com.example.mobilechatapp;

import android.content.Context;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.RecyclerView.ViewHolder;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.LinearLayout;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by almedina on 8/16/2018.
 */

public class RecyclerViewAdapter extends RecyclerView.Adapter<RecyclerViewAdapter.ViewHolder>
{
    // parent activity will implement this method to respond to click events
    public interface ItemClickListener
    {
        void onItemClick(View view, int position);
    }

    // stores and recycles views as they are scrolled off screen
    public class ViewHolder extends RecyclerView.ViewHolder implements View.OnClickListener
    {
        ViewHolder(View itemView)
        {
            super(itemView);
            m_cardLayout = (LinearLayout) itemView.findViewById(R.id.cardLayout);
            m_jsonFileName = (TextView) itemView.findViewById(R.id.jsonFileName);
            itemView.setOnClickListener(this);
        }

        @Override
        public void onClick(View view) {
            if (m_clickListener != null)
            {
                m_clickListener.onItemClick(view, getAdapterPosition());
            }
        }

        LinearLayout m_cardLayout;
        TextView m_jsonFileName;
    }

    RecyclerViewAdapter(Context context)
    {
        m_inflater = LayoutInflater.from(context);
        m_fileNames = new ArrayList<>();
        m_renderedCards = new ArrayList<>();
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
        View renderedCard = m_renderedCards.get(position);

        ViewGroup parent = (ViewGroup)renderedCard.getParent();
        if(parent != null)
        {
            parent.removeView(renderedCard);
        }

        holder.m_jsonFileName.setText(m_fileNames.get(position));
        while(holder.m_cardLayout.getChildCount() > 1)
        {
            holder.m_cardLayout.removeViewAt(1);
        }
        holder.m_cardLayout.addView(renderedCard);
    }

    @Override
    public int getItemCount() {
        return m_renderedCards.size();
    }

    // convenience method for getting data at click position
    View getItem(int id)
    {
        return m_renderedCards.get(id);
    }

    // allows clicks events to be caught
    void setClickListener(ItemClickListener itemClickListener)
    {
        m_clickListener = itemClickListener;
    }

    void addItem(String fileName, View view)
    {
        m_fileNames.add(fileName);
        m_renderedCards.add(view);
        notifyDataSetChanged();
    }

    private List<String> m_fileNames;
    private List<View> m_renderedCards;
    private LayoutInflater m_inflater;
    private ItemClickListener m_clickListener;
}
