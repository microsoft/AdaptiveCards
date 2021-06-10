// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp;

import android.content.Context;
import android.content.Intent;
import android.drm.DrmStore;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.ActionBar;
import androidx.appcompat.widget.Toolbar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.fragment.app.FragmentActivity;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

public class MainActivityUITestApp extends AppCompatActivity
{

    // Used to load the 'adaptivecards-native-lib' library on application startup.
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private List<String> items;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_ui_test_app);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        ActionBar actionBar = getSupportActionBar();
        if (actionBar != null)
        {
            actionBar.setDisplayHomeAsUpEnabled(true);
        }

        items = new ArrayList<String>();
        for(int i = 0; i < 5; ++i)
        {
            items.add("" + i);
        }

        // ArrayAdapter<String> itemsAdapter = new ArrayAdapter<String>(this, android.R.layout.test_list_item, items);

        TestCasesAdapter<String> itemsAdapter = new TestCasesAdapter(this, android.R.layout.test_list_item, items);

        ListView listView = findViewById(R.id.test_cases_list_view);
        listView.setAdapter(itemsAdapter);
    }



    public boolean onOptionsItemSelected(MenuItem item)
    {
        return super.onOptionsItemSelected(item);
    }

    private class TestCasesAdapter<T> extends ArrayAdapter
    {
        private List<T> m_testCaseList = null;

        public TestCasesAdapter(@NonNull Context context, int resource, List<T> itemsList)
        {
            super(context, resource, itemsList);
            m_testCaseList = itemsList;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent)
        {
            if (convertView == null)
            {
                convertView = getLayoutInflater().inflate(R.layout.test_case_list_item, parent, false);
            }

            Button testCaseButton = convertView.findViewById(R.id.list_item_button);
            String testCaseButtonContent = getItem(position).toString();
            testCaseButton.setText(testCaseButtonContent);
            testCaseButton.setOnClickListener(new TestCaseButtonClickListener(testCaseButtonContent));

            return convertView;
        }

        private class TestCaseButtonClickListener implements View.OnClickListener
        {
            String m_content;

            public TestCaseButtonClickListener(String content)
            {
                m_content = content;
            }

            @Override
            public void onClick(View v)
            {
                Intent renderedCardIntent = new Intent(MainActivityUITestApp.this, RenderCardUiTestAppActivity.class);
                renderedCardIntent.putExtra("key", m_content);
                startActivity(renderedCardIntent);
            }
        }
    }

}
