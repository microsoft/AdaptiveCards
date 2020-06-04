// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.adaptivecardssample;

import android.os.Build;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentActivity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Switch;
import android.widget.TabHost;
import android.view.View;
import android.view.Menu;
import android.widget.TextView;
import android.widget.Toast;

import io.adaptivecards.objectmodel.*;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.inputhandler.IInputWatcher;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import io.adaptivecards.adaptivecardssample.CustomObjects.Actions.*;
import io.adaptivecards.adaptivecardssample.CustomObjects.CardElements.*;
import io.adaptivecards.adaptivecardssample.CustomObjects.Media.*;

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

import com.google.zxing.integration.android.IntentIntegrator;
import com.google.zxing.integration.android.IntentResult;

public class MainActivityAdaptiveCardsSample extends FragmentActivity
        implements ICardActionHandler, IInputWatcher
{

    // Used to load the 'adaptivecards-native-lib' library on application startup.
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private static String IS_CARD = "isCard";
    private RemoteClientConnection m_remoteClientConnection;
    private Button m_buttonScanQr;
    private Button m_buttonDisconnect;
    private View m_adaptiveCardPickerGroup;
    private View m_hostConfigPickerGroup;
    private EditText m_jsonEditText;
    private EditText m_configEditText;
    private Timer m_timer=new Timer();
    private final long DELAY = 1000; // milliseconds

    // Options for custom elements
    private Switch m_customActions;
    private Switch m_customElements;
    private Switch m_featureRegistration;
    private Switch m_svgSupport;
    private Switch m_customImageLoader;
    private Switch m_customMediaLoader;
    private Switch m_onlineImageLoader;
    private Switch m_httpResourceResolver;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_adaptive_cards_sample);

        m_buttonScanQr = (Button)findViewById(R.id.buttonScanQr);
        m_buttonDisconnect = (Button)findViewById(R.id.buttonDisconnect);
        m_adaptiveCardPickerGroup = findViewById(R.id.adaptiveCardPickerGroup);
        m_hostConfigPickerGroup = findViewById(R.id.hostConfigPickerGroup);

        setupTabs();
        setupOptions();

        // Add text change handler
        m_jsonEditText = (EditText) findViewById(R.id.jsonAdaptiveCard);
        m_configEditText = (EditText) findViewById(R.id.hostConfig);

        TextWatcher watcher = new TextWatcher()
        {
            @Override
            public void afterTextChanged(Editable editable)
            {
                renderAdaptiveCardAfterDelay(true);
            }

            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) { }

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) { }
        };

        m_jsonEditText.addTextChangedListener(watcher);
        m_configEditText.addTextChangedListener(watcher);
    }

    public class SwitchListener implements CompoundButton.OnCheckedChangeListener
    {
        public SwitchListener(TextView textView)
        {
            m_cards = textView;
        }

        @Override
        public void onCheckedChanged(CompoundButton buttonView, boolean isChecked)
        {
            if (isChecked)
            {
                m_cards.setVisibility(View.VISIBLE);
            }
            else
            {
                m_cards.setVisibility(View.GONE);
            }
        }

        private TextView m_cards;
    }

    protected void setupTabs()
    {
        TabHost tabHost = (TabHost) findViewById(R.id.tabHost);
        tabHost.setup();
        tabHost.addTab(tabHost.newTabSpec("tab_load").setIndicator("Load").setContent(R.id.load));
        tabHost.addTab(tabHost.newTabSpec("tab_visual").setIndicator("Visual").setContent(R.id.Visual));
        tabHost.addTab(tabHost.newTabSpec("tab_json").setIndicator("JSON").setContent(R.id.JSON));
        tabHost.addTab(tabHost.newTabSpec("tab_config").setIndicator("Config").setContent(R.id.config));
        tabHost.addTab(tabHost.newTabSpec("tab_optional").setIndicator("Options").setContent(R.id.options));
        tabHost.setCurrentTab(0);
    }

    protected void setupOptions()
    {
        m_customActions = (Switch) findViewById(R.id.customActions);
        m_customActions.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsCustomActions)));

        m_customElements = (Switch) findViewById(R.id.customElements);
        m_customElements.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsCustomElements)));

        m_featureRegistration = (Switch) findViewById(R.id.customFeatureReg);
        m_featureRegistration.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsCustomFeature)));

        m_svgSupport = (Switch) findViewById(R.id.svgSupport);
        m_svgSupport.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsSvgSupport)));

        m_customImageLoader = (Switch) findViewById(R.id.customImageLoader);
        m_customImageLoader.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsCustomImageLoader)));

        m_customMediaLoader = (Switch) findViewById(R.id.customMediaLoader);
        m_customMediaLoader.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsCustomMediaLoader)));

        m_onlineImageLoader = (Switch) findViewById(R.id.onlineImageLoader);
        m_onlineImageLoader.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsCustomOnlineImageLoader)));

        m_httpResourceResolver = (Switch) findViewById(R.id.httpResourceResolver);
        m_httpResourceResolver.setOnCheckedChangeListener(new SwitchListener(findViewById(R.id.cardsHttpResourceResolver)));
    }

    private void renderAdaptiveCardAfterDelay(boolean showErrorToast)
    {
        m_timer.cancel();
        m_timer = new Timer();
        m_timer.schedule(new TimerTask()
        {
            public void run()
            {
                m_jsonEditText.post(new Runnable()
                {
                    public void run()
                    {
                        renderAdaptiveCard(true);
                    }
                });
            }
        }, DELAY);
    }

    private ParseContext createParseContextForCustomElements()
    {
        ElementParserRegistration elementParserRegistration = null;
        ActionParserRegistration actionParserRegistration = null;

        if (m_customElements.isChecked())
        {
            elementParserRegistration = new ElementParserRegistration();
            elementParserRegistration.AddParser("blah", new CustomBlahParser());

            actionParserRegistration = new ActionParserRegistration();
            actionParserRegistration.AddParser(CustomRedActionElement.CustomActionId, new CustomRedActionParser());
            actionParserRegistration.AddParser(CustomGreenActionElement.CustomActionId, new CustomGreenActionParser());
        }

        return new ParseContext(elementParserRegistration, actionParserRegistration);
    }

    private void registerCustomImageLoaders()
    {
        LocalResourcesLoader localResourcesLoader = null;
        if (m_customImageLoader.isChecked())
        {
            localResourcesLoader = new LocalResourcesLoader(this);
        }
        CardRendererRegistration.getInstance().registerResourceResolver("package", localResourcesLoader);

        IOnlineImageLoader onlineImageLoader = null;
        if (m_onlineImageLoader.isChecked())
        {
            // Code to demonstrate how IOnlineImageLoader registration works, uncomment to test, you should see that all images rendered are all the same cat
            onlineImageLoader = new OnlineImageLoader();
        }
        CardRendererRegistration.getInstance().registerOnlineImageLoader(onlineImageLoader);

        SvgImageLoader svgImageLoader = null;
        if (m_svgSupport.isChecked())
        {
            svgImageLoader = new SvgImageLoader();
        }
        CardRendererRegistration.getInstance().registerResourceResolver("data", svgImageLoader);

        CustomImageLoaderForButtons httpResourceResolver = null;
        if (m_httpResourceResolver.isChecked())
        {
            httpResourceResolver = new CustomImageLoaderForButtons();
        }
        CardRendererRegistration.getInstance().registerResourceResolver("http", httpResourceResolver);
    }

    private void registerCustomMediaLoaders()
    {
        // Example on how a custom OnlineMediaLoader should be registered
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
        {
            IOnlineMediaLoader mediaLoader = null;

            if (m_customMediaLoader.isChecked())
            {
                mediaLoader = new OnlineMediaLoader();
            }

            CardRendererRegistration.getInstance().registerOnlineMediaLoader(mediaLoader);
        }
    }

    private void registerFeatureRegistration()
    {
        // Sample on how to register a feature registration object
        FeatureRegistration featureRegistration = null;
        if (m_featureRegistration.isChecked())
        {
            featureRegistration = new FeatureRegistration();
            featureRegistration.AddFeature("acTest", "1.0");
        }
        CardRendererRegistration.getInstance().registerFeatureRegistration(featureRegistration);
    }

    private void registerCustomElementRenderers()
    {
        if (m_customActions.isChecked())
        {
            CardRendererRegistration.getInstance().registerActionRenderer(CustomRedActionElement.CustomActionId, new CustomRedActionRenderer(this));
            CardRendererRegistration.getInstance().registerActionRenderer(CustomGreenActionElement.CustomActionId, new CustomGreenActionRenderer(this));

            // Example on how to override the showcard renderer
            CardRendererRegistration.getInstance().registerActionRenderer(AdaptiveCardObjectModel.ActionTypeToString(ActionType.ShowCard), new ShowCardOverrideRenderer(this));
        }

        if (m_customElements.isChecked())
        {
            CardRendererRegistration.getInstance().registerRenderer("blah", new CustomBlahRenderer());
        }
    }

    private void registerCustomFeatures()
    {
        registerCustomImageLoaders();
        registerCustomMediaLoaders();
        registerFeatureRegistration();
        registerCustomElementRenderers();
    }

    private void renderAdaptiveCard(boolean showErrorToast)
    {
        // Cancel any existing timer, in case we were rendered on-demand while a
        // delay render was still in the queue
        m_timer.cancel();

        try
        {
            String jsonText = m_jsonEditText.getText().toString();
            if (jsonText == null)
            {
                return;
            }

            String hostConfigText = m_configEditText.getText().toString();
            HostConfig hostConfig;
            if (hostConfigText.isEmpty())
            {
                hostConfig = new HostConfig();
            }
            else
            {
                hostConfig = HostConfig.DeserializeFromString(hostConfigText);
            }

            ParseContext context = createParseContextForCustomElements();
            ParseResult parseResult = AdaptiveCard.DeserializeFromString(jsonText, AdaptiveCardRenderer.VERSION, context);
            LinearLayout layout = (LinearLayout) findViewById(R.id.visualAdaptiveCardLayout);
            layout.removeAllViews();

            registerCustomFeatures();

            RenderedAdaptiveCard renderedCard = AdaptiveCardRenderer.getInstance().render(this, getSupportFragmentManager(), parseResult.GetAdaptiveCard(), this, hostConfig);
            layout.addView(renderedCard.getView());
        }
        catch (Exception ex)
        {
            if (showErrorToast)
            {
                Toast.makeText(this, ex.getMessage(), Toast.LENGTH_SHORT).show();
            }
        }
    }

    private void renderLoadCard(boolean showErrorToast) {
        try {
            ParseResult parseResult = AdaptiveCard.DeserializeFromString(readStream(getResources().openRawResource(R.raw.loadcard)), AdaptiveCardRenderer.VERSION);
            LinearLayout layout = (LinearLayout) findViewById(R.id.loadAdaptiveCardLayout);
            layout.removeAllViews();

            CardRendererRegistration.getInstance().setInputWatcher(this);

            RenderedAdaptiveCard loadCard = AdaptiveCardRenderer.getInstance().render(this, getSupportFragmentManager(), parseResult.GetAdaptiveCard(), this);
            layout.addView(loadCard.getView());
        } catch (Exception ex) {
            if (showErrorToast) {
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

    private String loadFile(Uri uri) {
        // Get the Uri of the selected file
        if (uri == null) {
            Toast.makeText(this, "File was not selected.", Toast.LENGTH_SHORT).show();
            return null;
        }

        try {
            return readStream(getContentResolver().openInputStream(uri));
        } catch (FileNotFoundException e) {
            Toast.makeText(this, "File " + uri.getPath() + " was not found.", Toast.LENGTH_SHORT).show();
        }

        return null;
    }

    private String readStream(InputStream inputStream) {
        try
        {
            BufferedReader r = new BufferedReader(new InputStreamReader(inputStream));
            StringBuilder total = new StringBuilder();
            String line;

            while ((line = r.readLine()) != null)
            {
                total.append(line + "\n");
            }

            return total.toString();
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
        loadAdaptiveCard(fullString);

        EditText fileEditText = (EditText) findViewById(R.id.fileEditText);
        List path = data.getData().getPathSegments();
        fileEditText.setText((String)path.get(path.size()-1));

    }

    private void loadAdaptiveCard(String payload)
    {
        m_jsonEditText.setText(payload);

        // Render it immediately
        renderAdaptiveCard(true);
    }


    private void loadHostConfig(Intent data)
    {
        String fullString = loadFile(data.getData());
        if (fullString.isEmpty())
        {
            return;
        }

        loadHostConfig(fullString);

        EditText fileEditText = (EditText) findViewById(R.id.hostConfigFileEditText);
        List path = data.getData().getPathSegments();
        fileEditText.setText((String)path.get(path.size()-1));

    }

    private void loadHostConfig(String hostConfigStr)
    {
        m_configEditText.setText(hostConfigStr);

        // Render it immediately
        renderAdaptiveCard(true);
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if (handleQrActivityResult(requestCode, resultCode, data)) {
            return;
        }

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

    private void onSubmit(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard) {
        SubmitAction submitAction = null;
        if (actionElement instanceof SubmitAction) {
            submitAction = (SubmitAction) actionElement;
        } else if ((submitAction = SubmitAction.dynamic_cast(actionElement)) == null) {
            throw new InternalError("Unable to convert BaseActionElement to ShowCardAction object model.");
        }

        String data = submitAction.GetDataJson();
        Map<String, String> keyValueMap = renderedAdaptiveCard.getInputs();
        if (!data.isEmpty())
        {
            try
            {
                JSONObject object = null;
                if (!data.equals("null\n"))
                {
                    object = new JSONObject(data);
                }
                else
                {
                    object = new JSONObject();
                }

                showToast("Submit data: " + object.toString() + "\nInput: " + keyValueMap.toString(), Toast.LENGTH_LONG);
            }
            catch (JSONException e)
            {
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
    public void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedCard)
    {
        ActionType actionType = actionElement.GetElementType();
        if (actionType == ActionType.Submit)
        {
            onSubmit(actionElement, renderedCard);
        }
        else if (actionType == ActionType.ShowCard)
        {
            onShowCard(actionElement);
        }
        else if (actionType == ActionType.OpenUrl)
        {
            onOpenUrl(actionElement);
        }
        else
        {
            showToast("Unknown Action!" , Toast.LENGTH_LONG);
        }
    }

    @Override
    public void onMediaPlay(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard)
    {
        showToast("Media started: " + mediaElement, Toast.LENGTH_LONG);
    }

    @Override
    public void onMediaStop(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard)
    {
        showToast("Media ended playing: " + mediaElement, Toast.LENGTH_LONG);
    }

    @Override
    public void onInputChange(String id, String value) {
        try {
            if(id.equals("sampleCardName")) {
                loadAdaptiveCard(readStream(getAssets().open(value)));
            } else if(id.equals("sampleHostConfigName")) {
                loadHostConfig(readStream(getAssets().open(value)));
            }
        } catch (IOException e) {
            Toast.makeText(this, "Failed to open " + value, Toast.LENGTH_SHORT).show();
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

    public void onScanQrClicked(View view)
    {
        goToConnectingState();

        // Docs here: https://github.com/journeyapps/zxing-android-embedded
        IntentIntegrator integrator = new IntentIntegrator(this);
        integrator.setPrompt("Scan QR code from the Designer");
        integrator.setBeepEnabled(false);
        integrator.setDesiredBarcodeFormats(IntentIntegrator.QR_CODE);
        integrator.setOrientationLocked(true);
        integrator.initiateScan();
    }

    private boolean handleQrActivityResult(int requestCode, int resultCode, Intent data)
    {
        IntentResult qrResult = IntentIntegrator.parseActivityResult(requestCode, resultCode, data);
        if (qrResult != null)
        {
            String contents = qrResult.getContents();
            if (contents != null)
            {
                m_remoteClientConnection = new RemoteClientConnection(this, new RemoteClientConnection.Observer()
                {
                    @Override
                    public void onConnecting(String status)
                    {
                        final String finalStatus = status;
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(getApplicationContext(), finalStatus, Toast.LENGTH_SHORT).show();
                            }
                        });
                    }

                    @Override
                    public void onStateChanged(RemoteClientConnection.State state)
                    {
                        final RemoteClientConnection.State s = state;
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                switch (s) {
                                    // Connecting omitted because that's never hit, it's already
                                    // connecting by the time we started observing
                                    case CONNECTED:
                                        goToConnectedState();
                                        break;

                                    case RECONNECTING:
                                        goToReconnectingState();
                                        break;

                                    case CLOSED:
                                        goToDisconnectedState();
                                        break;
                                }
                            }
                        });
                    }

                    @Override
                    public void onConnectFailed(String errorMessage)
                    {
                        m_remoteClientConnection = null;
                        final String finalErrorMessage = errorMessage;
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                Toast.makeText(getApplicationContext(), finalErrorMessage, Toast.LENGTH_SHORT).show();
                            }
                        });
                    }

                    @Override
                    public void onCardPayload(String cardPayload)
                    {
                        final String cPayload = cardPayload;
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                loadAdaptiveCard(cPayload);
                            }
                        });
                    }

                    @Override
                    public void onHostConfigPayload(String hostConfigPayload)
                    {
                        final String hPayload = hostConfigPayload;
                        runOnUiThread(new Runnable() {
                            @Override
                            public void run() {
                                loadHostConfig(hPayload);
                            }
                        });
                    }
                });

                m_remoteClientConnection.connect(contents);
            }

            else
            {
                goToDisconnectedState();
            }


            return true;
        }

        return false;
    }

    public void onDisconnectClicked(View view)
    {
        disconnect();
        goToDisconnectedState();
    }

    private void disconnect()
    {
        if (m_remoteClientConnection != null)
        {
            m_remoteClientConnection.disconnect();
            m_remoteClientConnection = null;
        }
    }

    private void goToConnectingState()
    {
        m_buttonScanQr.setText("Connecting...");
        m_buttonScanQr.setVisibility(View.VISIBLE);
        m_buttonScanQr.setEnabled(false);
        m_buttonDisconnect.setVisibility(View.GONE);
        goToReadOnlyState();
    }

    private void goToConnectedState()
    {
        m_buttonScanQr.setVisibility(View.GONE);
        m_buttonDisconnect.setVisibility(View.VISIBLE);
        m_buttonDisconnect.setText("Connected! Click to disconnect");
        goToReadOnlyState();
    }

    private void goToReconnectingState()
    {
        m_buttonScanQr.setVisibility(View.GONE);
        m_buttonDisconnect.setVisibility(View.VISIBLE);
        m_buttonDisconnect.setText("Reconnecting... Tap to disconnect");
        goToReadOnlyState();
    }

    private void goToDisconnectedState()
    {
        m_buttonScanQr.setText("Connect via QR Code");
        m_buttonScanQr.setVisibility(View.VISIBLE);
        m_buttonScanQr.setEnabled(true);
        m_buttonDisconnect.setVisibility(View.GONE);
        goToEditableState();
    }

    private void goToReadOnlyState()
    {
        m_adaptiveCardPickerGroup.setVisibility(View.GONE);
        m_hostConfigPickerGroup.setVisibility(View.GONE);
        m_jsonEditText.setEnabled(false);
        m_configEditText.setEnabled(false);
    }

    private void goToEditableState()
    {
        m_adaptiveCardPickerGroup.setVisibility(View.VISIBLE);
        m_hostConfigPickerGroup.setVisibility(View.VISIBLE);
        m_jsonEditText.setEnabled(true);
        m_configEditText.setEnabled(true);
    }
}
