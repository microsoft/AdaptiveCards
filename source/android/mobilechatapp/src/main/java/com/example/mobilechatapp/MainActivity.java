// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.mobilechatapp;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.ProgressBar;
import android.widget.TextView;
import android.widget.Toast;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.concurrent.atomic.AtomicInteger;

import com.example.mobilechatapp.ShowCardFragment;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ElementParserRegistration;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.OpenUrlAction;
import io.adaptivecards.objectmodel.ShowCardAction;
import io.adaptivecards.objectmodel.SubmitAction;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class MainActivity extends AppCompatActivity implements ICardActionHandler, RecyclerViewAdapter.ItemClickListener
{

    // Used to load the 'adaptivecards-native-lib' library on application startup.
    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Override
    public void onItemClick(View view, int position) {
        Log.d("ASDF", "Not clicking, matey!");
    }

    private class ButtonListener implements View.OnClickListener
    {

        @Override
        public void onClick(View view)
        {
            try
            {
                List<Card> retrievedCards = null;
                if (view == m_sendButton)
                {
                    String requestedCards = m_cardRequestEdit.getText().toString();
                    retrievedCards = CardRetriever.getInstance().searchCards(requestedCards);
                }
                else
                {
                    Button elementTypeButton = (Button)view;
                    String query = m_cardRequestEdit.getText().toString() + " " + elementTypeButton.getText().toString();
                    retrievedCards = CardRetriever.getInstance().searchCards(query);
                }

                if(retrievedCards != null)
                {
                    for (Card card : retrievedCards)
                    {
                        try
                        {
                            if(card.getParsedCard() != null)
                            {
                                m_adapter.addItem(card.getFileName(), card.getParsedCard(), MainActivity.this, getSupportFragmentManager(), MainActivity.this, m_hostConfig);
                            }
                            else
                            {
                                LinearLayout errorMessageLayout = new LinearLayout(MainActivity.this);
                                errorMessageLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
                                errorMessageLayout.setBackgroundColor(getResources().getColor(R.color.ParsedErrorBackground));

                                TextView errorMessage = new TextView(MainActivity.this);
                                errorMessage.setPadding(20, 15, 20, 15);
                                errorMessage.setText("This card failed to render due to: \n" + card.getExceptionDetailMessage());
                                errorMessage.setTextColor(getResources().getColor(R.color.ErrorMessageColor));
                                errorMessage.setTextSize(15);
                                errorMessageLayout.addView(errorMessage);
                                m_adapter.addItem(card.getFileName(), errorMessageLayout);
                            }
                        }
                        catch (Exception e)
                        {
                            e.printStackTrace();
                        }
                    }
                }
            }
            catch(Exception e)
            {
                e.printStackTrace();
            }
        }
    }

    private class ProgressBarUpdateListener implements IFilesReadListener
    {
        @Override
        public void setFilesCount(int totalFiles)
        {
            m_filesCount = totalFiles;
            m_progressBar.setMax(m_filesCount);
        }

        @Override
        public void updateFilesCompletion()
        {
            int filesCompleted = m_filesCompleted.incrementAndGet();
            m_progressBar.setProgress(filesCompleted);

            if(filesCompleted == m_filesCount)
            {
                m_progressBarLayout.setVisibility(View.GONE);

                Set<String> cardElements = CardRetriever.getInstance().getCardElements();

                for(String cardElementType : cardElements)
                {
                    Button button = new Button(MainActivity.this);
                    button.setText(cardElementType);
                    button.setBackgroundColor(MainActivity.this.getResources().getColor(R.color.textEditColor));
                    button.setOnClickListener(new ButtonListener());

                    button.setPadding(10, 0, 10, 0);
                    ViewGroup.MarginLayoutParams mlp =  new LinearLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.MATCH_PARENT);
                    mlp.setMargins(5, 5, 5, 5);
                    button.setLayoutParams(mlp);
                    m_elementTypesButttonsLayout.addView(button);
                }
            }
        }

        private int m_filesCount = 0;
        private AtomicInteger m_filesCompleted = new AtomicInteger(0);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        View contentLayout = findViewById(R.id.contentLayout);

        m_sendButton = (ImageButton) contentLayout.findViewById(R.id.sendButton);
        m_sendButton.setOnClickListener(new ButtonListener());

        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this, android.R.layout.simple_dropdown_item_1line, s_keywords);
        m_cardRequestEdit = (AutoCompleteTextView) contentLayout.findViewById(R.id.cardNumberEditText);
        m_cardRequestEdit.setAdapter(adapter);

        m_elementTypesButttonsLayout = (LinearLayout) contentLayout.findViewById(R.id.existingElementTypesButtonLayout);

        m_recyclerView = (RecyclerView) contentLayout.findViewById(R.id.cardsView);
        m_recyclerView.setLayoutManager(new LinearLayoutManager(this));
        m_adapter = new RecyclerViewAdapter(this);
        m_recyclerView.setAdapter(m_adapter);

        m_progressBar = (ProgressBar) contentLayout.findViewById(R.id.readCardsProgressBar);
        m_progressBarLayout = (LinearLayout) contentLayout.findViewById(R.id.loadingBarLayout);

        m_hostConfig = new HostConfig();
        m_elementParserRegistration = new ElementParserRegistration();
        CardRetriever.getInstance().setFilesReadListener(new ProgressBarUpdateListener());
        CardRetriever.getInstance().populateCardJsons(this);
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_help) {

            LayoutInflater inflater = (LayoutInflater)getSystemService(LAYOUT_INFLATER_SERVICE);
            View popupView = inflater.inflate(R.layout.help_popup, null);

            // create the popup window
            final PopupWindow popupWindow = new PopupWindow(popupView, LinearLayout.LayoutParams.WRAP_CONTENT, LinearLayout.LayoutParams.WRAP_CONTENT, true);

            // show the popup window
            // which view you pass in doesn't matter, it is only used for the window token
            popupWindow.showAtLocation(m_elementTypesButttonsLayout, Gravity.CENTER, 0, 0);

            // dismiss the popup window when touched
            popupView.setOnTouchListener(new View.OnTouchListener() {
                @Override
                public boolean onTouch(View v, MotionEvent event) {
                    popupWindow.dismiss();
                    return true;
                }
            });

            return true;
        }

        return super.onOptionsItemSelected(item);
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

    private void onSubmit(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard)
    {
        SubmitAction submitAction = null;
        if (actionElement instanceof SubmitAction)
        {
            submitAction = (SubmitAction) actionElement;
        }
        else if ((submitAction = SubmitAction.dynamic_cast(actionElement)) == null)
        {
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
            catch (JSONException e) {
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
        HostConfig hostConfig = new HostConfig();

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
    public void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard)
    {
        ActionType actionType = actionElement.GetElementType();
        if (actionType == ActionType.Submit)
        {
            onSubmit(actionElement, renderedAdaptiveCard);
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
    public void onMediaPlay(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard) {

    }

    @Override
    public void onMediaStop(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard) {

    }

    private ImageButton m_sendButton;
    private AutoCompleteTextView m_cardRequestEdit;
    private RecyclerViewAdapter m_adapter;
    private RecyclerView m_recyclerView;
    private LinearLayout m_progressBarLayout, m_elementTypesButttonsLayout;
    private ProgressBar m_progressBar;
    private ElementParserRegistration m_elementParserRegistration;
    private HostConfig m_hostConfig;

    private static final String[] s_keywords = {"all", "random"};
}
