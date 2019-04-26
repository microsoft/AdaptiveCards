// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import android.app.ListActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.ArrayAdapter;

import java.util.ArrayList;

/**
 * Created by almedina on 8/16/2018.
 */

public class CardListActivity extends ListActivity
{

    public void onCreate(Bundle icicle)
    {
        super.onCreate(icicle);

        setContentView(R.layout.content_main);
        m_adapter = new ArrayAdapter<>(this, android.R.layout.activity_list_item, m_renderedCards);
        setListAdapter(m_adapter);
    }

    public void addCard(View v)
    {
        m_renderedCards.add(v);
        m_adapter.notifyDataSetChanged();
    }

    private ArrayAdapter<View> m_adapter;
    private ArrayList<View> m_renderedCards = new ArrayList<>();
}
