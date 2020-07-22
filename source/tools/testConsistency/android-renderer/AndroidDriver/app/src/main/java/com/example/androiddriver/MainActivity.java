// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.androiddriver;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewTreeObserver;
import android.widget.FrameLayout;

import androidx.appcompat.app.AppCompatActivity;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.Base64;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Semaphore;

import fi.iki.elonen.NanoHTTPD;
import io.adaptivecards.objectmodel.AdaptiveCard;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.objectmodel.ParseResult;
import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class MainActivity extends AppCompatActivity {

    //This web server is started with the app and is capable of accepting post requests
    private WebServer server;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        server = new WebServer();
        try {
            server.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        if(server != null)
            server.stop();
    }

    /**
     * This class represents the web server. This web server runs on localhost on the android
     * emulator and it is capable of accepting get and post requests. It accepts the card data as a
     * POST request. It renders the adaptive card returns the results as a response.
     */
    private class WebServer extends NanoHTTPD{

        public WebServer(){
            super(8080);
        }

        /**
         * This method accepts an IHTTPSession which is basically a request. It currently only accepts
         * POST requests. It gets the card payload as an HTTP POST request(the card payload as form
         * parameter with key "cardPayload") and renders it on the UI. It then creates a bitmap of
         * the card and returns the result along with any errors.
         */
        @Override
        public Response serve(IHTTPSession session){
            if(session.getMethod() == Method.POST){
                Log.w("req", "Request for post");
                Map<String, String> defaultJsonKeys = new HashMap<>();
                defaultJsonKeys.put("imageData", "");
                defaultJsonKeys.put("errors", "");
                defaultJsonKeys.put("warnings", "");

                final JSONObject resJson = new JSONObject(defaultJsonKeys);

                final JSONArray errors = new JSONArray();
                final JSONArray warnings = new JSONArray();
                final StringBuilder imageData = new StringBuilder();

                //This semaphore ensures that the threads work in the order we require. The card
                // is rendered on a UI thread and it is necessary to wait for it to render
                // completely before creating a bitmap.
                final Semaphore signal = new Semaphore(0);

                try {
                    resJson.put("errors", errors);
                    resJson.put("warnings", warnings);

                    Map<String, String> bodyFiles = new HashMap<>();
                    session.parseBody(bodyFiles);

                    final Map<String, List<String>> paramters = session.getParameters();
                    final String cardJsonString = paramters.get("cardPayload").get(0);

                    // The card rendered and a bitmap of the card is taken on this UI thread
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            try {
                                ParseContext context = new ParseContext();
                                ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardJsonString, AdaptiveCardRenderer.VERSION, context);
                                AdaptiveCard adaptiveCard = parseResult.GetAdaptiveCard();

                                HostConfig hostConfig = new HostConfig();

                                // Since we are only concerned with the screenshot of the card, we
                                // have an empty action handler
                                ICardActionHandler iCardActionHandler = new ICardActionHandler() {
                                    @Override
                                    public void onAction(BaseActionElement baseActionElement, RenderedAdaptiveCard renderedAdaptiveCard) {

                                    }

                                    @Override
                                    public void onMediaPlay(BaseCardElement baseCardElement, RenderedAdaptiveCard renderedAdaptiveCard) {

                                    }

                                    @Override
                                    public void onMediaStop(BaseCardElement baseCardElement, RenderedAdaptiveCard renderedAdaptiveCard) {

                                    }
                                };

                                RenderedAdaptiveCard renderedAdaptiveCard = AdaptiveCardRenderer.getInstance().render(getBaseContext(), getSupportFragmentManager(), adaptiveCard, iCardActionHandler);
                                View card = renderedAdaptiveCard.getView();
                                card.setId(1234);

                                resJson.put("warnings", new JSONArray(renderedAdaptiveCard.getWarnings()));

                                FrameLayout layout = findViewById(R.id.cardHolder);
                                layout.addView(card);

                                // we want to pass a boolean as a reference to the bitmap creation method.
                                // therefore, we create a size 1 boolean array.
                                final boolean[] bitMapCreated = new boolean[1];
                                bitMapCreated[0] = false;

                                // this tree observer checks every time there has been a change in the layout.
                                // Since images are loaded asynchronously, we need to wait until
                                // there is no longer a change in the layout before attempting to
                                // get a bitmap of the card
                                layout.getViewTreeObserver().addOnGlobalLayoutListener(
                                        new ViewTreeObserver.OnGlobalLayoutListener() {
                                            // we use a timer to schedule the method that takes the
                                            // bitmap
                                            Timer timer;

                                            // This method is called every time there is a change in
                                            // the layout.
                                            @Override
                                            public void onGlobalLayout() {
                                                if (timer != null) {
                                                    timer.cancel();
                                                }
                                                timer = new Timer();
                                                timer.schedule(new CardBitMap(resJson, signal, bitMapCreated), 1000);
                                            }
                                        });
                            }
                            catch(Exception e){
                                e.printStackTrace();
                                errors.put(e.getMessage());
                                signal.release();
                            }
                        }
                    });
                }
                catch(Exception e){
                    e.printStackTrace();
                    errors.put(e.getMessage());
                }
                try {
                    signal.acquire();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                return newFixedLengthResponse(resJson.toString());
            }
            // This simple message is displayed in case a GET request is made to our route.
            return newFixedLengthResponse("This method accepts only POST requests");
        }
    }

    /**
     * This class gives us a TimerTask which allows us to get a bitmap of the card once we have
     * rendered it successfully
     */
    private class CardBitMap extends TimerTask {

        private JSONObject resJson;
        private Semaphore signal;
        private boolean[] bitmapCreated;

        public CardBitMap(JSONObject resJson, Semaphore signal, boolean[] bitmapCreated){
            this.resJson = resJson;
            this.signal = signal;
            this.bitmapCreated = bitmapCreated;
        }

        // This method allows us to create a bitmap of the rendered card and add the corresponding
        // base 64 encoded string to the results
        @Override
        public void run() {
            //check if a bitmap has already been created before
            if (!bitmapCreated[0]) {
                try {

                    final View card = findViewById(1234);
                    Bitmap largeBitmap = Bitmap.createBitmap(card.getMeasuredWidth(), card.getMeasuredHeight(), Bitmap.Config.ARGB_8888);
                    Canvas canvas = new Canvas(largeBitmap);

                    // The paint is used to draw a border around the bitmap to signify the android screen.
                    Paint paint = new Paint();
                    paint.setColor(Color.BLACK);
                    paint.setStrokeWidth(2);
                    paint.setStyle(Paint.Style.STROKE);

                    card.draw(canvas);
                    canvas.drawRect(0, 0, card.getWidth(), card.getHeight(), paint);

                    Bitmap bitmap = Bitmap.createScaledBitmap(largeBitmap, (int) (card.getMeasuredWidth() * 0.5), (int) (card.getMeasuredHeight() * 0.5), true);
                    ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                    bitmap.compress(Bitmap.CompressFormat.PNG, 100, byteArrayOutputStream);
                    byte[] byteArray = byteArrayOutputStream.toByteArray();
                    String imgString = Base64.getEncoder().encodeToString(byteArray);

                    resJson.put("imageData", imgString);

                    // Once we have created the bitmap and added the base 64 string to the results,
                    // we remove the card from the layout
                    runOnUiThread(new Runnable() {
                        @Override
                        public void run() {
                            ViewGroup parent = (ViewGroup) card.getParent();
                            if (parent != null)
                                parent.removeAllViews();
                        }
                    });
                } catch (Exception e) {
                    e.printStackTrace();
                }

                signal.release();
                bitmapCreated[0] = true;
            }
        }
    }
}