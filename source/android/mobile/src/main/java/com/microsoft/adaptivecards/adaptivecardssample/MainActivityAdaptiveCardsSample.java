package com.microsoft.adaptivecards.adaptivecardssample;

import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentActivity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TabHost;
import android.view.View;
import android.view.Menu;
import android.widget.Toast;

import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.objectmodel.*;
import com.microsoft.adaptivecards.renderer.AdaptiveCardRenderer;

import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivityAdaptiveCardsSample extends FragmentActivity
    implements ICardActionHandler
{

    // Used to load the 'adaptivecards-native-lib' library on application startup.
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private static String IS_CARD = "isCard";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_adaptive_cards_sample);
        setupTabs();

        // Add text change handler
        final EditText jsonEditText = (EditText) findViewById(R.id.jsonAdaptiveCard);
        final EditText configEditText = (EditText) findViewById(R.id.hostConfig);

        TextWatcher watcher = new TextWatcher()
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
                                renderAdaptiveCard(true);
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
            private final long DELAY = 1000; // milliseconds
        };

        jsonEditText.addTextChangedListener(watcher);
        configEditText.addTextChangedListener(watcher);
    }

    protected void setupTabs()
    {
        TabHost tabHost = (TabHost) findViewById(R.id.tabHost);
        tabHost.setup();
        tabHost.addTab(tabHost.newTabSpec("tab_visual").setIndicator("Visual").setContent(R.id.Visual));
        tabHost.addTab(tabHost.newTabSpec("tab_json").setIndicator("JSON").setContent(R.id.JSON));
        tabHost.addTab(tabHost.newTabSpec("tab_config").setIndicator("Config").setContent(R.id.config));
        tabHost.setCurrentTab(0);
    }

    private void renderAdaptiveCard(boolean showErrorToast)
    {
        try
        {
            String jsonText = ((EditText) findViewById(R.id.jsonAdaptiveCard)).getText().toString();
            if (jsonText == null)
            {
                return;
            }

            String hostConfigText = ((EditText) findViewById(R.id.hostConfig)).getText().toString();
            HostConfig hostConfig;
            if (hostConfigText.isEmpty())
            {
                hostConfig = new HostConfig();
            }
            else
            {
                hostConfig = HostConfig.DeserializeFromString(hostConfigText);
            }


            AdaptiveCard adaptiveCard = AdaptiveCard.DeserializeFromString(jsonText);
            LinearLayout layout = (LinearLayout) findViewById(R.id.visualAdaptiveCardLayout);
            layout.removeAllViews();
            layout.addView(AdaptiveCardRenderer.getInstance().render(this, getSupportFragmentManager(), adaptiveCard, this, hostConfig));
        }
        catch (Exception ex)
        {
            if (showErrorToast)
            {
                Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }
    }

    private static final int FILE_SELECT_CARD = 0;
    private static final int FILE_SELECT_CONFIG = 1;
    public void onClickFileBrowser(View view)
    {
        Intent fileBrowserIntent = new Intent(Intent.ACTION_GET_CONTENT);
        fileBrowserIntent.setType("*/*");
        fileBrowserIntent.addCategory(Intent.CATEGORY_OPENABLE);
        fileBrowserIntent.putExtra(IS_CARD, view.getId() == R.id.loadCardButton);

        try {
            startActivityForResult(
                    Intent.createChooser(fileBrowserIntent, "Select a JSON File to Open"),
                    view.getId() == R.id.loadCardButton ? FILE_SELECT_CARD : FILE_SELECT_CONFIG);
        } catch (android.content.ActivityNotFoundException ex) {
            // Potentially direct the user to the Market with a Dialog
            Toast.makeText(this, "Please install a File Manager.", Toast.LENGTH_SHORT).show();
        }
    }

    private String loadFile(Uri uri)
    {
        // Get the Uri of the selected file
        if (uri == null)
        {
            Toast.makeText(this, "File was not selected.", Toast.LENGTH_SHORT).show();
            return null;
        }

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

            return total.toString();
        }
        catch (FileNotFoundException e)
        {
            Toast.makeText(this, "File " + uri.getPath() + " was not found.", Toast.LENGTH_SHORT).show();
        }
        catch (IOException ioExcep)
        {

        }

        return null;
    }

    private void loadAdaptiveCard(Intent data)
    {

        String fullString = loadFile(data.getData());
        if (fullString.isEmpty())
        {
            return;
        }
        EditText jsonText = (EditText) findViewById(R.id.jsonAdaptiveCard);
        jsonText.setText(fullString);

        EditText fileEditText = (EditText) findViewById(R.id.fileEditText);
        List path = data.getData().getPathSegments();
        fileEditText.setText((String)path.get(path.size()-1));

    }

    private void loadHostConfig(Intent data)
    {
        String fullString = loadFile(data.getData());
        if (fullString.isEmpty())
        {
            return;
        }

        EditText configText = (EditText) findViewById(R.id.hostConfig);
        configText.setText(fullString);

        EditText fileEditText = (EditText) findViewById(R.id.hostConfigFileEditText);
        List path = data.getData().getPathSegments();
        fileEditText.setText((String)path.get(path.size()-1));

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        switch (requestCode) {
            case FILE_SELECT_CARD:
                if (resultCode == RESULT_OK)
                {
                    loadAdaptiveCard(data);
                }
                break;
            case FILE_SELECT_CONFIG:
                if (resultCode == RESULT_OK)
                {
                    loadHostConfig(data);
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

    private void onSubmit(BaseActionElement actionElement, Map<String, String> keyValueMap) {
        SubmitAction submitAction = null;
        if (actionElement instanceof SubmitAction) {
            submitAction = (SubmitAction) actionElement;
        } else if ((submitAction = SubmitAction.dynamic_cast(actionElement)) == null) {
            throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
        }

        String data = submitAction.GetDataJson();
        if (!data.isEmpty())
        {
            try {
                JSONObject object = new JSONObject(data);
                showToast("Submit data: " + object.toString() + "\nInput: " + keyValueMap.toString(), Toast.LENGTH_LONG);
            } catch (JSONException e) {
                //e.printStackTrace();
                showToast(e.toString(), Toast.LENGTH_LONG);
            }
        }
        else
        {
            showToast("Submit input: " + keyValueMap.toString(), Toast.LENGTH_LONG);
        }
    }

    private void onShowCard(BaseActionElement actionElement)
    {
        ShowCardAction showCardAction = null;
        if (actionElement instanceof ShowCardAction)
        {
            showCardAction = (ShowCardAction) actionElement;
        }
        else if ((showCardAction = ShowCardAction.dynamic_cast(actionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
        }

        ShowCardFragment showCardFragment = new ShowCardFragment();
        String hostConfigText = ((EditText) findViewById(R.id.hostConfig)).getText().toString();
        HostConfig hostConfig;
        if (hostConfigText.isEmpty())
        {
            hostConfig = new HostConfig();
        }
        else
        {
            hostConfig = HostConfig.DeserializeFromString(hostConfigText);
        }

        showCardFragment.initialize(this, getSupportFragmentManager(), showCardAction, this, hostConfig);
        Bundle args = new Bundle();
        args.putString("title", showCardAction.GetTitle());
        showCardFragment.setArguments(args);

        FragmentManager fm = getSupportFragmentManager();
        showCardFragment.show(fm, showCardAction.GetTitle());
    }

    private void onOpenUrl(BaseActionElement actionElement)
    {
        OpenUrlAction openUrlAction = null;
        if (actionElement instanceof ShowCardAction)
        {
            openUrlAction = (OpenUrlAction) actionElement;
        }
        else if ((openUrlAction = OpenUrlAction.dynamic_cast(actionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
        }

        Intent browserIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(openUrlAction.GetUrl()));
        this.startActivity(browserIntent);
    }

    @Override
    public void onAction(BaseActionElement actionElement, Map<String, String> inputData)
    {
        int actionType = actionElement.GetElementType().swigValue();
        if (actionType == ActionType.Submit.swigValue())
        {
            onSubmit(actionElement, inputData);
        }
        else if (actionType == ActionType.ShowCard.swigValue())
        {
            onShowCard(actionElement);
        }
        else if (actionType == ActionType.OpenUrl.swigValue())
        {
            onOpenUrl(actionElement);
        }
        else
        {
            showToast("Unknown Action!" , Toast.LENGTH_LONG);
        }
    }

    public void showToast(String text, int duration)
    {
        class RunnableExtended implements Runnable
        {
            public RunnableExtended(Context context, String text, int duration)
            {
                m_context = context;
                m_text = text;
                m_duration = duration;
            }

            @Override
            public void run()
            {
                Toast.makeText(m_context, m_text, m_duration).show();
            }

            private Context m_context;
            private String m_text;
            private int m_duration;
        }

        this.runOnUiThread(new RunnableExtended(this, text, duration));
    }

}
