// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.adaptivecardssample;

import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.drawable.Drawable;
import android.os.AsyncTask;
import android.os.Build;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentActivity;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TabHost;
import android.view.View;
import android.view.Menu;
import android.widget.TextView;
import android.widget.Toast;

import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.GenericImageLoaderAsync;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.IResourceResolver;
import io.adaptivecards.renderer.IMediaDataSourceOnPreparedListener;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.*;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

import org.json.JSONException;
import org.json.JSONObject;
import org.liquidplayer.javascript.JSContext;
import org.liquidplayer.javascript.JSValue;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLDecoder;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import android.media.MediaDataSource;
import android.support.annotation.RequiresApi;

import com.google.zxing.integration.android.IntentIntegrator;
import com.google.zxing.integration.android.IntentResult;
import com.pixplicity.sharp.Sharp;

public class MainActivityAdaptiveCardsSample extends FragmentActivity
        implements ICardActionHandler
{

    // Used to load the 'adaptivecards-native-lib' library on application startup.
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    private static String IS_CARD = "isCard";
    private RemoteClientConnection m_remoteClientConnection;
    private JSContext m_scriptContext;
    private Button m_buttonScanQr;
    private Button m_buttonTypeCode;
    private Button m_buttonDisconnect;
    private EditText m_jsonEditText;
    private EditText m_configEditText;
    private EditText m_dataEditText;
    private Timer m_timer=new Timer();
    private final long DELAY = 1000; // milliseconds

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_adaptive_cards_sample);

        m_buttonScanQr = (Button)findViewById(R.id.buttonScanQr);
        m_buttonTypeCode = (Button)findViewById(R.id.buttonTypeCode);
        m_buttonDisconnect = (Button)findViewById(R.id.buttonDisconnect);
        m_dataEditText = (EditText)findViewById(R.id.editTextData);

        setupTabs();
        setupImageLoader();
        setupData();
        setupTemplatingScript();

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

        SharedPreferences pref = this.getPreferences(Context.MODE_PRIVATE);
        String connCode = pref.getString("ConnectionCode", null);
        if (connCode != null || connCode.length() > 0)
        {
            goToConnectingState();
            connectToCode(connCode);
        }
    }

    public class CustomCardElement extends BaseCardElement
    {

        public CustomCardElement(CardElementType type) {
            super(type);
        }

        public String getSecretString()
        {
            return secretString;
        }

        public void setSecretString(String secret)
        {
            secretString = secret;
        }

        private String secretString;

    }

    protected void setupTabs()
    {
        TabHost tabHost = (TabHost) findViewById(R.id.tabHost);
        tabHost.setup();
        tabHost.addTab(tabHost.newTabSpec("tab_visual").setIndicator("Visual").setContent(R.id.Visual));
        tabHost.addTab(tabHost.newTabSpec("tab_json").setIndicator("JSON").setContent(R.id.JSON));
        tabHost.addTab(tabHost.newTabSpec("tab_data").setIndicator("DATA").setContent(R.id.data));
        tabHost.addTab(tabHost.newTabSpec("tab_config").setIndicator("Config").setContent(R.id.config));
        tabHost.setCurrentTab(0);
    }

    private String getRawAsString(int id)
    {
        InputStream stream = getResources().openRawResource(id);
        java.util.Scanner s = new java.util.Scanner(stream).useDelimiter("\\A");
        String scriptStr = s.hasNext() ? s.next() : "";
        return scriptStr;
    }

    private void setupTemplatingScript()
    {
        try {
            JSContext context = new JSContext();
            context.evaluateScript(getRawAsString(R.raw.templateengine));
            m_scriptContext = context;
        } catch (Exception ex) {
            Toast.makeText(this, ex.getMessage(), Toast.LENGTH_LONG).show();
        }
    }

    private void setupData()
    {
        JSONObject data = new JSONObject();
        try {
            data.put("platform", "Android");
            data.put("manufacturer", Build.MANUFACTURER);
            data.put("model", Build.MODEL);
            data.put("osVersion", Build.VERSION.RELEASE);
            m_dataEditText.setText(data.toString(2));
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public class CustomRedActionElement extends BaseActionElement
    {

        public CustomRedActionElement(ActionType type) {
            super(type);
        }

        public String getBackwardString()
        {
            return m_backwardsString;
        }

        public void setBackwardString(String s)
        {
            m_backwardsString = new String();
            for(int i = s.length() - 1; i >= 0; i--)
            {
                m_backwardsString += s.charAt(i);
            }
        }

        private String m_backwardsString;
        public static final String CustomActionId = "redAction";
    }

    public class CustomRedActionParser extends ActionElementParser
    {
        @Override
        public BaseActionElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomRedActionElement element = new CustomRedActionElement(ActionType.Custom);
            element.SetElementTypeString(CustomRedActionElement.CustomActionId);
            element.SetId("backwardActionDeserialize");
            String val = value.getString();
            try {
                JSONObject obj = new JSONObject(val);
                element.setBackwardString(obj.getString("backwardString"));
            } catch (JSONException e) {
                e.printStackTrace();
                element.setBackwardString("deliaF");
            }
            return element;
        }

        @Override
        public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
        {
            CustomRedActionElement element = new CustomRedActionElement(ActionType.Custom);
            element.SetElementTypeString(CustomRedActionElement.CustomActionId);
            element.SetId("backwardActionDeserialize");
            try {
                JSONObject obj = new JSONObject(jsonString);
                element.setBackwardString(obj.getString("backwardString"));
            } catch (JSONException e) {
                e.printStackTrace();
                element.setBackwardString("deliaF");
            }
            return element;
        }
    }

    public class CustomRedActionRenderer extends BaseActionElementRenderer
    {
        @Override
        public Button render(RenderedAdaptiveCard renderedCard,
                             Context context,
                             FragmentManager fragmentManager,
                             ViewGroup viewGroup,
                             BaseActionElement baseActionElement,
                             ICardActionHandler cardActionHandler,
                             HostConfig hostConfig,
                             RenderArgs renderArgs)
        {
            Button backwardActionButton = new Button(context);

            CustomRedActionElement customAction = (CustomRedActionElement) baseActionElement.findImplObj();

            backwardActionButton.setBackgroundColor(getResources().getColor(R.color.redActionColor));
            backwardActionButton.setText(customAction.getBackwardString());
            backwardActionButton.setAllCaps(false);
            backwardActionButton.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, baseActionElement, cardActionHandler));

            viewGroup.addView(backwardActionButton);

            return backwardActionButton;
        }
    }

    public class CustomGreenActionElement extends BaseActionElement
    {

        public CustomGreenActionElement(ActionType type) {
            super(type);
        }

        public String getMessage()
        {
            return m_message;
        }

        private final String m_message = "Smell you later!";
        public static final String CustomActionId = "greenAction";
    }

    public class CustomGreenActionParser extends ActionElementParser
    {
        @Override
        public BaseActionElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomGreenActionElement element = new CustomGreenActionElement(ActionType.Custom);
            element.SetElementTypeString(CustomGreenActionElement.CustomActionId);
            element.SetId("greenActionDeserialize");
            return element;
        }

        @Override
        public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
        {
            CustomGreenActionElement element = new CustomGreenActionElement(ActionType.Custom);
            element.SetElementTypeString(CustomGreenActionElement.CustomActionId);
            element.SetId("greenActionDeserialize");
            return element;
        }
    }

    public class CustomGreenActionRenderer extends BaseActionElementRenderer
    {
        @Override
        public Button render(RenderedAdaptiveCard renderedCard,
                             Context context,
                             FragmentManager fragmentManager,
                             ViewGroup viewGroup,
                             BaseActionElement baseActionElement,
                             ICardActionHandler cardActionHandler,
                             HostConfig hostConfig,
                             RenderArgs renderArgs)
        {
            Button greenActionButton = new Button(context);

            CustomGreenActionElement customAction = (CustomGreenActionElement) baseActionElement.findImplObj();

            greenActionButton.setBackgroundColor(getResources().getColor(R.color.greenActionColor));
            greenActionButton.setText(customAction.getMessage());
            greenActionButton.setAllCaps(false);
            greenActionButton.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, baseActionElement, cardActionHandler));

            viewGroup.addView(greenActionButton);

            return greenActionButton;
        }
    }

    public class CustomBlahParser extends BaseCardElementParser
    {
        @Override
        public BaseCardElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomCardElement element = new CustomCardElement(CardElementType.Custom);
            element.SetElementTypeString("blah");
            element.SetId("BlahDeserialize");
            String val = value.getString();
            try {
                JSONObject obj = new JSONObject(val);
                element.setSecretString(obj.getString("secret"));
            } catch (JSONException e) {
                e.printStackTrace();
                element.setSecretString("Failed");
            }
            return element;
        }

        @Override
        public BaseCardElement DeserializeFromString(ParseContext context, String jsonString)
        {
            CustomCardElement element = new CustomCardElement(CardElementType.Custom);
            element.SetElementTypeString("blah");
            element.SetId("BlahDeserialize");
            try {
                JSONObject obj = new JSONObject(jsonString);
                element.setSecretString(obj.getString("secret"));
            } catch (JSONException e) {
                e.printStackTrace();
                element.setSecretString("Failed");
            }
            return element;
        }
    }

    public class CustomBlahRenderer extends BaseCardElementRenderer
    {
        @Override
        public View render(RenderedAdaptiveCard renderedAdaptiveCard, Context context, FragmentManager fragmentManager, ViewGroup viewGroup, BaseCardElement baseCardElement, ICardActionHandler cardActionHandler, HostConfig hostConfig, RenderArgs renderArgs) {
            TextView textView = new TextView(context);

            CustomCardElement element = (CustomCardElement) baseCardElement.findImplObj();

            textView.setText(element.getSecretString());

            textView.setAllCaps(true);

            viewGroup.addView(textView);

            return textView;
        }
    }

    public class ShowCardOverrideRenderer extends BaseActionElementRenderer
    {

        @Override
        public Button render(RenderedAdaptiveCard renderedCard,
                             Context context,
                             FragmentManager fragmentManager,
                             ViewGroup viewGroup,
                             BaseActionElement baseActionElement,
                             ICardActionHandler cardActionHandler,
                             HostConfig hostConfig,
                             RenderArgs renderArgs)
        {
            Button button = new Button(context);

            button.setBackgroundColor(getResources().getColor(R.color.yellowActionColor));
            button.setText(baseActionElement.GetTitle() +"(ShowCard)");

            button.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig));

            viewGroup.addView(button);
            return button;
        }
    }

    /*
    * MediaDataSource implementation taken from https://github.com/jacks205/MediaDataSourceExample
    * */
    @RequiresApi(api = Build.VERSION_CODES.M)
    public class MediaDataSourceImpl extends MediaDataSource
    {
        MediaDataSourceImpl(String uri, IMediaDataSourceOnPreparedListener mediaDataSourceOnPreparedListener)
        {
            m_mediaUri = uri;
            m_mediaDataSourceListener = mediaDataSourceOnPreparedListener;
            Thread mediaDownloadThread = new Thread(m_downloadMediaRunnable);
            mediaDownloadThread.start();
        }

        Runnable m_downloadMediaRunnable = new Runnable() {
            @Override
            public void run() {
                try
                {
                    URL url = new URL(m_mediaUri);
                    InputStream inputStream = url.openStream();
                    ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                    int read = 0;
                    while(read != -1)
                    {
                        read = inputStream.read();
                        byteArrayOutputStream.write(read);
                    }
                    inputStream.close();

                    byteArrayOutputStream.flush();
                    m_mediaBuffer = byteArrayOutputStream.toByteArray();

                    byteArrayOutputStream.close();

                    // Call this function to signalize that the mediaPlayer is able to prepare with the current state for DataMediaSource
                    m_mediaDataSourceListener.prepareMediaPlayer();
                }
                catch (MalformedURLException urlException)
                {
                    urlException.printStackTrace();
                    Log.d("Error on video download", urlException.toString());
                }
                catch (IOException e)
                {
                    e.printStackTrace();
                    Log.d("Error on video download", e.toString());
                }
            }
        };

        @Override
        public int readAt(long position, byte[] buffer, int offset, int size) throws IOException
        {
            synchronized (m_mediaBuffer)
            {
                int length = m_mediaBuffer.length;
                if(position >= length)
                {
                    return -1;
                }

                if(position + size > length)
                {
                    size -= (position + size) - length;
                    // size = length - position;
                }
                System.arraycopy(m_mediaBuffer, (int)position, buffer, offset, size);
                return size;
            }
        }

        @Override
        public long getSize() throws IOException
        {
            synchronized (m_mediaBuffer)
            {
                return m_mediaBuffer.length;
            }
        }

        @Override
        public void close() throws IOException
        {
        }

        private volatile IMediaDataSourceOnPreparedListener m_mediaDataSourceListener;

        private volatile String m_mediaUri;
        private volatile byte[] m_mediaBuffer;
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    public class OnlineMediaLoader implements IOnlineMediaLoader
    {
        public class OnlineFileAvailableChecker extends AsyncTask<String, Void, Boolean>
        {
            public OnlineFileAvailableChecker(String uri)
            {
                m_uri = uri;
            }

            @Override
            protected Boolean doInBackground(String... strings) {
                // if the provided uri is a valid uri or is valid with the resource resolver, then use that
                // otherwise, try to get the media from a local file
                try
                {
                    HttpRequestHelper.query(m_uri);
                    return true;
                }
                catch (Exception e)
                {
                    // Do nothing if the media was not found at all
                    e.printStackTrace();
                    return false;
                }
            }

            private String m_uri;
        }


        @Override
        public MediaDataSource loadOnlineMedia(MediaSourceVector mediaSources, IMediaDataSourceOnPreparedListener mediaDataSourceOnPreparedListener)
        {
            final long mediaSourcesSize = mediaSources.size();
            for(int i = 0; i < mediaSourcesSize; i++)
            {
                String mediaUri = mediaSources.get(i).GetUrl();

                OnlineFileAvailableChecker checker = new OnlineFileAvailableChecker(mediaUri);
                try
                {
                    Boolean fileExists = checker.execute("").get();
                    if(fileExists)
                    {
                        return new MediaDataSourceImpl(mediaUri, mediaDataSourceOnPreparedListener);
                    }
                }
                catch (Exception e)
                {
                }
            }
            return null;
        }
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

    private String getTransformedAdaptiveCard()
    {
        String jsonText = m_jsonEditText.getText().toString();
        if (jsonText == null)
        {
            return null;
        }

        String dataJson = m_dataEditText.getText().toString();
        if (dataJson == null)
        {
            return jsonText;
        }

        m_scriptContext.property("cardJson", jsonText);
        m_scriptContext.property("dataJson", dataJson);
        JSValue result = m_scriptContext.evaluateScript("TemplateEngine.transform(cardJson, dataJson)");
        if (result.isString()) {
            return result.toString();
        } else {
            return jsonText;
        }
    }

    private void renderAdaptiveCard(boolean showErrorToast)
    {
        // Cancel any existing timer, in case we were rendered on-demand while a
        // delay render was still in the queue
        m_timer.cancel();

        try
        {
            String jsonText = getTransformedAdaptiveCard();
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

            ElementParserRegistration elementParserRegistration = new ElementParserRegistration();
            elementParserRegistration.AddParser("blah", new CustomBlahParser());

            ActionParserRegistration actionParserRegistration = new ActionParserRegistration();
            actionParserRegistration.AddParser(CustomRedActionElement.CustomActionId, new CustomRedActionParser());
            actionParserRegistration.AddParser(CustomGreenActionElement.CustomActionId, new CustomGreenActionParser());

            CardRendererRegistration.getInstance().registerRenderer("blah", new CustomBlahRenderer());
            CardRendererRegistration.getInstance().registerActionRenderer(CustomRedActionElement.CustomActionId, new CustomRedActionRenderer());
            CardRendererRegistration.getInstance().registerActionRenderer(CustomGreenActionElement.CustomActionId, new CustomGreenActionRenderer());
            // Example on how to override the showcard renderer
            // CardRendererRegistration.getInstance().registerActionRenderer(AdaptiveCardObjectModel.ActionTypeToString(ActionType.ShowCard), new ShowCardOverrideRenderer());

            // Example on how a custom OnlineMediaLoader should be registered
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
                CardRendererRegistration.getInstance().registerOnlineMediaLoader(new OnlineMediaLoader());
            }

            // Sample on how to register a feature registration object
            FeatureRegistration myFeatureRegistration = new FeatureRegistration();
            myFeatureRegistration.AddFeature("acTest", "1.0");
            CardRendererRegistration.getInstance().registerFeatureRegistration(myFeatureRegistration);

            ParseContext context = new ParseContext(elementParserRegistration, actionParserRegistration);

            ParseResult parseResult = AdaptiveCard.DeserializeFromString(jsonText, AdaptiveCardRenderer.VERSION, context);
            LinearLayout layout = (LinearLayout) findViewById(R.id.visualAdaptiveCardLayout);
            layout.removeAllViews();
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

    private void loadAdaptiveCard(String payload)
    {
        m_jsonEditText.setText(payload);

        // Render it immediately
        renderAdaptiveCard(true);
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
            try {
                JSONObject object = new JSONObject(data);
                showToast("Submit data: " + object.toString() + "\nInput: " + keyValueMap.toString(), Toast.LENGTH_LONG);
            } catch (JSONException e) {
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

    private void setupImageLoader()
    {
        CardRendererRegistration.getInstance().registerResourceResolver("package", new IResourceResolver()
        {
            @Override
            public HttpRequestResult<Bitmap> resolveImageResource(String url, GenericImageLoaderAsync loader) throws IOException, URISyntaxException
            {
                // Get image identifier
                String authority = getPackageName();
                Resources resources = getResources();

                // For host app only provides image file name as url, host app can pass "package:[IMAGE NAME]" as replacement for
                // meeting the valid URL format checking. Here we will remove this prefix to get file name.
                if (url.startsWith("package:"))
                {
                    url = url.replace("package:", "drawable/");
                }

                int identifier = resources.getIdentifier(url, "", authority);
                if (identifier == 0)
                {
                    throw new IOException("Image not found: " + url);
                }

                InputStream ins = resources.openRawResource(identifier);
                Bitmap bitmap = BitmapFactory.decodeStream(ins);
                if (bitmap == null)
                {
                    throw new IOException("Failed to convert local content to bitmap: " + url);
                }

                return new HttpRequestResult<>(bitmap);
            }

            @Override
            public HttpRequestResult<Bitmap> resolveImageResource(String url, GenericImageLoaderAsync loader, int maxWidth) throws IOException, URISyntaxException
            {
                return resolveImageResource(url, loader);
            }
        });

        CardRendererRegistration.getInstance().registerResourceResolver("data", new IResourceResolver()
        {
            @Override
            public HttpRequestResult<Bitmap> resolveImageResource(String uri, GenericImageLoaderAsync genericImageLoaderAsync) throws IOException, URISyntaxException
            {
                Bitmap bitmap;
                String dataUri = AdaptiveBase64Util.ExtractDataFromUri(uri);
                CharVector decodedDataUri = AdaptiveBase64Util.Decode(dataUri);
                byte[] decodedByteArray = Util.getBytes(decodedDataUri);
                bitmap = BitmapFactory.decodeByteArray(decodedByteArray, 0, decodedByteArray.length);

                return new HttpRequestResult<>(bitmap);
            }

            @Override
            public HttpRequestResult<Bitmap> resolveImageResource(String uri, GenericImageLoaderAsync genericImageLoaderAsync, int maxWidth) throws IOException, URISyntaxException
            {
                Bitmap bitmap;
                String dataUri = AdaptiveBase64Util.ExtractDataFromUri(uri);
                CharVector decodedDataUri = AdaptiveBase64Util.Decode(dataUri);

                if (uri.startsWith("data:image/svg")) {
                    String svgString = AdaptiveBase64Util.ExtractDataFromUri(uri);
                    String decodedSvgString = URLDecoder.decode(svgString, "UTF-8");
                    Sharp sharp = Sharp.loadString(decodedSvgString);
                    Drawable drawable = sharp.getDrawable();
                    bitmap = ImageUtil.drawableToBitmap(drawable, maxWidth);
                }
                else
                {
                    try
                    {
                        return genericImageLoaderAsync.loadDataUriImage(uri);
                    }
                    catch (Exception e)
                    {
                        return new HttpRequestResult<>(e);
                    }
                }

                return new HttpRequestResult<>(bitmap);
            }
        });

        // Code to demonstrate how IOnlineImageLoader registration works, uncomment to test, you should see that all images rendered are all the same cat
        /*
        CardRendererRegistration.getInstance().registerOnlineImageLoader(new IOnlineImageLoader() {
            @Override
            public HttpRequestResult<Bitmap> loadOnlineImage(String url, GenericImageLoaderAsync loader) throws IOException, URISyntaxException
            {
                String catImnageUri = "http://adaptivecards.io/content/cats/1.png";
                byte[] bytes = HttpRequestHelper.get(catImnageUri);
                if (bytes == null)
                {
                    throw new IOException("Failed to retrieve content from " + catImnageUri);
                }

                Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);

                if (bitmap == null)
                {
                    throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
                }

                return new HttpRequestResult<>(bitmap);
            }
        });
        */
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

    public void onTypeCodeClicked(View view)
    {
        AlertDialog.Builder alertDialog = new AlertDialog.Builder(this);
        alertDialog.setTitle("CONNECT");
        alertDialog.setMessage("Enter connect code");

        final EditText input = new EditText(this);
        LinearLayout.LayoutParams lp = new LinearLayout.LayoutParams(
            LinearLayout.LayoutParams.MATCH_PARENT,
            LinearLayout.LayoutParams.MATCH_PARENT);
        input.setLayoutParams(lp);
        alertDialog.setView(input);

        alertDialog.setPositiveButton("Connect",
            new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    goToConnectingState();
                    connectToCode(input.getText().toString());
                }
            });

        alertDialog.setNegativeButton("Cancel",
            new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int which) {
                    dialog.cancel();
                }
            });

        alertDialog.show();
    }

    private boolean handleQrActivityResult(int requestCode, int resultCode, Intent data)
    {
        IntentResult qrResult = IntentIntegrator.parseActivityResult(requestCode, resultCode, data);
        if (qrResult != null)
        {
            String contents = qrResult.getContents();
            if (contents != null)
            {
                connectToCode(contents);
            }

            else
            {
                goToDisconnectedState();
            }


            return true;
        }

        return false;
    }

    private void connectToCode(String code)
    {
        SharedPreferences.Editor pref = this.getPreferences(Context.MODE_PRIVATE).edit();
        pref.putString("ConnectionCode", code);
        pref.commit();

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
                        Toast.makeText(getApplicationContext(), finalErrorMessage, Toast.LENGTH_LONG).show();
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

        m_remoteClientConnection.connect(code);
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
        m_buttonTypeCode.setVisibility(View.GONE);
        m_buttonDisconnect.setVisibility(View.GONE);
    }

    private void goToConnectedState()
    {
        m_buttonScanQr.setVisibility(View.GONE);
        m_buttonTypeCode.setVisibility(View.GONE);
        m_buttonDisconnect.setVisibility(View.VISIBLE);
        m_buttonDisconnect.setText("Connected! Click to disconnect");
    }

    private void goToReconnectingState()
    {
        m_buttonScanQr.setVisibility(View.GONE);
        m_buttonTypeCode.setVisibility(View.GONE);
        m_buttonDisconnect.setVisibility(View.VISIBLE);
        m_buttonDisconnect.setText("Reconnecting... Tap to disconnect");
    }

    private void goToDisconnectedState()
    {
        m_buttonScanQr.setText("Connect via QR Code");
        m_buttonScanQr.setVisibility(View.VISIBLE);
        m_buttonScanQr.setEnabled(true);
        m_buttonTypeCode.setVisibility(View.VISIBLE);
        m_buttonDisconnect.setVisibility(View.GONE);
    }
}
