// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.adaptivecardssample;

import android.content.Context;
import android.support.annotation.Nullable;

import com.android.volley.NetworkResponse;
import com.android.volley.Request;
import com.android.volley.RequestQueue;
import com.android.volley.Response;
import com.android.volley.VolleyError;
import com.android.volley.toolbox.HttpHeaderParser;
import com.android.volley.toolbox.JsonObjectRequest;
import com.android.volley.toolbox.Volley;

import org.json.JSONObject;

import com.tylerjroach.eventsource.EventSource;
import com.tylerjroach.eventsource.EventSourceHandler;
import com.tylerjroach.eventsource.MessageEvent;

public class RemoteClientConnection
{
    public enum State {
        // Working on connecting for the first time.
        // Next states: Connected or Closed.
        CONNECTING,

        // Connected! Everything's good!
        // Next states: Reconnecting or Closed.
        CONNECTED,

        // Attempting to re-connect after being disconnected (might be network issues).
        // Next states: Connected or Closed.
        RECONNECTING,

        // Connection closed. End of the line, please disembark the train.
        // Next states: N/A
        CLOSED
    }

    private static final String LOG_TAG = "RemoteClientConnection";
    private static final String BASE_URL = "https://cardhub.azurewebsites.net/api/";
    private Observer m_observer;
    private Context m_context;
    private String m_hostId;
    private State m_state = State.CONNECTING;
    private EventSource m_eventSource;
    private boolean m_isDisconnected = false;

    private void changeState(State newState)
    {
        // If we're already closed, don't allow any other changes
        if (m_state == State.CLOSED)
        {
            return;
        }

        // We can't enter the connecting state, it's the first state, that's a programming error
        if (newState == State.CONNECTING)
        {
            return;
        }

        if (m_state != newState)
        {
            m_state = newState;
            m_observer.onStateChanged(newState);
        }
    }

    private void changeStateToClosed()
    {
        changeState(State.CLOSED);
    }

    public RemoteClientConnection(Context context, Observer observer)
    {
        this.m_context = context;
        this.m_observer = observer;
    }

    public interface Observer
    {
        void onConnecting(String status);

        void onConnectFailed(String errorMessage);

        void onCardPayload(String cardPayload);

        void onHostConfigPayload(String hostConfigPayload);

        void onStateChanged(State state);
    }

    public void connect(String hostId)
    {
        m_hostId = hostId;

        m_observer.onConnecting("Connecting to event source");

        // Need to connect via server sent events
        // https://stackoverflow.com/questions/18903760/server-sent-events-in-android
        // https://github.com/tylerjroach/eventsource-android
        m_eventSource = new EventSource.Builder(BASE_URL + "card/" + hostId + "/subscribe").eventHandler(new EventSourceHandler() {
            @Override
            public void onConnect() throws Exception {
                // This doesn't trigger until first message received, which won't happen till changes occur
            }

            @Override
            public void onMessage(String event, MessageEvent message) throws Exception {
                getCard();
            }

            @Override
            public void onComment(String comment) throws Exception {

            }

            @Override
            public void onError(Throwable t) {
                m_observer.onConnectFailed(t.getMessage());
                m_eventSource.close();
            }

            @Override
            public void onClosed(boolean willReconnect) {
                changeStateToClosed();
            }
        }).build();

        m_eventSource.connect();

        getCard();
    }

    private void onCardDataReceived(JSONObject cardData)
    {
        try {
            m_observer.onCardPayload(cardData.getString("CardJson"));
        }
        catch (org.json.JSONException ex) {
        }
    }

    private boolean m_isGettingCard = false;
    private boolean m_needsAnotherCard = false;

    private void getCard()
    {
        if (m_isGettingCard)
        {
            m_needsAnotherCard = true;
            return;
        }

        RequestQueue queue = Volley.newRequestQueue(m_context);
        String url = BASE_URL + "card/" + m_hostId;

        // Request the offer info
        JsonObjectRequest stringRequest = new JsonObjectRequest(Request.Method.GET, url, null, new Response.Listener<JSONObject>()
        {
            @Override
            public void onResponse(JSONObject response)
            {
                if (m_isDisconnected)
                {
                    return;
                }

                if (m_state == State.CONNECTING)
                {
                    changeState(State.CONNECTED);
                }
                onCardDataReceived(response);
                finishGetCard();
            }
        }, new Response.ErrorListener()
        {
            @Override
            public void onErrorResponse(VolleyError error)
            {
                if (m_isDisconnected)
                {
                    return;
                }

                m_observer.onConnectFailed("Is your internet working? Failed to request offer info.");
                finishGetCard();
            }
        });

        queue.add(stringRequest);
    }

    private void finishGetCard()
    {
        m_isGettingCard = false;
        if (m_needsAnotherCard && !m_isDisconnected)
        {
            m_needsAnotherCard = false;
            getCard();
        }
    }

    public void disconnect()
    {
        if (m_eventSource != null)
        {
            m_eventSource.close();
        }

        m_isDisconnected = true;
        m_eventSource = null;
    }

    // https://stackoverflow.com/a/48834515/1454643
    private class JsonObjectRequestWithEmptyResponse extends JsonObjectRequest {
        public JsonObjectRequestWithEmptyResponse(int method, String url, @Nullable JSONObject jsonRequest, Response.Listener<JSONObject> listener, @Nullable Response.ErrorListener errorListener) {
            super(method, url, jsonRequest, listener, errorListener);
        }

        @Override
        public Response<JSONObject> parseNetworkResponse(NetworkResponse response)
        {
            if (response.data.length == 0)
            {
                return Response.success(null, HttpHeaderParser.parseCacheHeaders(response));
            }
            else
            {
                return Response.error(new VolleyError("Unexpected data in response body, expected empty response."));
            }
        }
    }
}
