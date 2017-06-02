package com.microsoft.adaptivecards.adaptivecardssample;

import android.content.Intent;
import android.graphics.Color;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Spinner;
import android.widget.TabHost;
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

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

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

        //populateSpinnerJSONFileList();
        setupTabs();

        // Add text change handler
        final EditText jsonEditText = (EditText) findViewById(R.id.jsonAdaptiveCard);
        jsonEditText.addTextChangedListener(new TextWatcher()
        {
            @Override
            public void afterTextChanged(Editable editable)
            {
                m_timer.cancel();
                m_timer = new Timer();
                m_timer.schedule(new TimerTask()
                {
                    public void run()
                    {
                        jsonEditText.post(new Runnable()
                        {
                            public void run()
                            {
                                renderAdaptiveCard(jsonEditText.getText().toString(), false);
                            }
                        });
                    }
                }, DELAY);
            }

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) { }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) { }

            private Timer m_timer=new Timer();
            private final long DELAY = 500; // milliseconds
        });
    }

    protected void setupTabs()
    {
        TabHost tabHost = (TabHost) findViewById(R.id.tabHost);
        tabHost.setup();
        tabHost.addTab(tabHost.newTabSpec("tab_visual").setIndicator("Visual").setContent(R.id.Visual));
        tabHost.addTab(tabHost.newTabSpec("tab_json").setIndicator("JSON").setContent(R.id.JSON));
        tabHost.setCurrentTab(0);
    }

    private void renderAdaptiveCard(String jsonText, boolean showErrorToast)
    {
        try
        {
            AdaptiveCard adaptiveCard = AdaptiveCard.DeserializeFromString(jsonText);
            LinearLayout layout = (LinearLayout) findViewById(R.id.visualAdaptiveCardLayout);
            layout.removeAllViews();
            layout.addView(AdaptiveCardRenderer.getInstance().render(getApplicationContext(), adaptiveCard, new HostConfig()));
        }
        catch (java.io.IOException ex)
        {
            if (showErrorToast)
            {
                Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }
    }

    private static final int FILE_SELECT_CODE = 0;
    public void onClickFileBrowser(View view)
    {
        Intent fileBrowserIntent = new Intent(Intent.ACTION_GET_CONTENT);
        fileBrowserIntent.setType("*/*");
        fileBrowserIntent.addCategory(Intent.CATEGORY_OPENABLE);

        try {
            startActivityForResult(
                    Intent.createChooser(fileBrowserIntent, "Select a JSON File to Open"),
                    FILE_SELECT_CODE);
        } catch (android.content.ActivityNotFoundException ex) {
            // Potentially direct the user to the Market with a Dialog
            Toast.makeText(this, "Please install a File Manager.", Toast.LENGTH_SHORT).show();
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case FILE_SELECT_CODE:
                if (resultCode == RESULT_OK) {
                    // Get the Uri of the selected file
                    Uri uri = data.getData();
                    if (uri == null)
                    {
                        Toast.makeText(this, "File was not selected.", Toast.LENGTH_SHORT).show();
                        break;
                    }

                    // TODO: Move this outside of UI thread
                    InputStream inputStream = null;
                    try
                    {
                        inputStream = getContentResolver().openInputStream(uri);
                        BufferedReader r = new BufferedReader(new InputStreamReader(inputStream));
                        StringBuilder total = new StringBuilder();
                        String line;

                        while ((line = r.readLine()) != null)
                        {
                            total.append(line + "\n");
                        }

                        EditText jsonText = (EditText) findViewById(R.id.jsonAdaptiveCard);
                        String fullString = total.toString();
                        jsonText.setText(fullString);
                        renderAdaptiveCard(fullString, true);

                        EditText fileEditText = (EditText) findViewById(R.id.fileEditText);
                        List path = uri.getPathSegments();
                        fileEditText.setText((String)path.get(path.size()-1));
                    }
                    catch (FileNotFoundException e)
                    {
                        Toast.makeText(this, "File " + uri.getPath() + " was not found.", Toast.LENGTH_SHORT).show();
                    }
                    catch (IOException ioExcep)
                    {

                    }
                }
                break;
        }
        super.onActivityResult(requestCode, resultCode, data);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main_activity_adaptive_cards_sample, menu);
        return true;
    }

    /*@Override
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
    }*/

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    private List<File> m_jsonFileList = new ArrayList<File>();
}
