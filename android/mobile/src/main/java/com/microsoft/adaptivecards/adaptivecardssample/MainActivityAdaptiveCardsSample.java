package com.microsoft.adaptivecards.adaptivecardssample;

import android.graphics.Color;
import android.os.Bundle;
import android.os.Environment;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TextView;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.*;
import com.microsoft.adaptivecards.renderer.AdaptiveCardRenderer;

import java.io.File;
import java.io.FileInputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

public class MainActivityAdaptiveCardsSample extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_adaptive_cards_sample);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        populateSpinnerJSONFileList();
    }

    protected void populateSpinnerJSONFileList()
    {
        File location = getExternalFilesDir(null);
        List<String> list = new ArrayList<String>();
        m_jsonFileList.clear();
        for (File file : location.listFiles())
        {
            if (file.getName().toLowerCase().endsWith(".json"))
            {
                m_jsonFileList.add(file);
                list.add(file.getName());
            }
        }

        ArrayAdapter<String> adapter  = new ArrayAdapter<String>(getApplicationContext(), android.R.layout.simple_spinner_item, list);
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        Spinner spinnerJSONFileList = (Spinner) findViewById(R.id.spinnerJsonFileList);
        spinnerJSONFileList.setAdapter(adapter);
        spinnerJSONFileList.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener()
        {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id)
            {
                ((TextView) view).setTextColor(Color.BLACK);

                // Showing selected spinner item
                Toast.makeText(getApplicationContext(), parent.getItemAtPosition(position).toString(), Toast.LENGTH_LONG).show();

                renderAdaptiveCard(m_jsonFileList.get(position));
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent)
            {
            }
        });
    }

    private void renderAdaptiveCard(File jsonFile)
    {
        try
        {
            AdaptiveCard adaptiveCard = AdaptiveCard.DeserializeFromFile(jsonFile.getAbsolutePath());
            LinearLayout layout = (LinearLayout) findViewById(R.id.layoutAdaptiveCard);
            layout.removeAllViews();
            AdaptiveCardRenderer.getInstance().render(getApplicationContext(), layout, adaptiveCard);
        }
        catch (Exception ex)
        {
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main_activity_adaptive_cards_sample, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    private List<File> m_jsonFileList = new ArrayList<File>();
}
