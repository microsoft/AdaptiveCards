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

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.atomic.AtomicBoolean;

public class MainActivityAdaptiveCardsSample extends FragmentActivity
    implements ICardActionHandler
{

    // Used to load the 'adaptivecards-native-lib' library on application startup.
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private HostConfig m_hostConfig;
    private AtomicBoolean m_fileLoaded;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        m_fileLoaded = new AtomicBoolean(false);
        setContentView(R.layout.activity_main_adaptive_cards_sample);
        setupTabs();

        m_hostConfig = new HostConfig();

        m_hostConfig.getImageSizes().setLargeSize(150);
        m_hostConfig.getImageSizes().setMediumSize(90);
        m_hostConfig.getImageSizes().setSmallSize(60);

        m_hostConfig.getSpacing().setDefaultSpacing(6);
        m_hostConfig.getSpacing().setSmallSpacing(4);
        m_hostConfig.getSpacing().setMediumSpacing(8);
        m_hostConfig.getSpacing().setLargeSpacing(10);
        m_hostConfig.getSpacing().setExtraLargeSpacing(15);
        m_hostConfig.getSpacing().setPaddingSpacing(12);

        //m_hostConfig.getActions().setMaxActions(2);
        m_hostConfig.getActions().getShowCard().setInlineTopMargin(10);


        // Add text change handler
        final EditText jsonEditText = (EditText) findViewById(R.id.jsonAdaptiveCard);
        jsonEditText.addTextChangedListener(new TextWatcher()
        {
            @Override
            public void afterTextChanged(Editable editable)
            {
                if (m_fileLoaded.compareAndSet(true, false))
                {
                    return;
                }

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
            private final long DELAY = 1000; // milliseconds
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
            layout.addView(AdaptiveCardRenderer.getInstance().render(this, getSupportFragmentManager(), adaptiveCard, this, m_hostConfig));
        }
        catch (Exception ex)
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

                        m_fileLoaded.set(true);
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

    private void onSubmit(Map<String, String> keyValueMap)
    {
        showToast("Submit: " + keyValueMap.toString(), Toast.LENGTH_LONG);
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
        HostConfig config = new HostConfig();
        config.getFontSizes().setSmallFontSize(1);
        config.getFontSizes().setMediumFontSize(1);
        config.getFontSizes().setLargeFontSize(1);
        config.getFontSizes().setExtraLargeFontSize(1);

        showCardFragment.initialize(this, getSupportFragmentManager(), showCardAction, this, config);
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
            onSubmit(inputData);
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
