// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package com.example.androiddriver;

import android.content.Context;
import android.content.res.AssetManager;
import android.util.Log;

import androidx.test.platform.app.InstrumentationRegistry;
import androidx.test.rule.ActivityTestRule;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.*;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import junitparams.JUnitParamsRunner;

import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static androidx.test.espresso.matcher.ViewMatchers.withText;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

import junitparams.*;

@RunWith(JUnitParamsRunner.class)
public class InstrumentedTests {
    @Rule
    public ActivityTestRule<MainActivity> activityRule =
            new ActivityTestRule<>(MainActivity.class);

    @Test
    public void useAppContext() {
        // Context of the app under test.
        Context appContext = InstrumentationRegistry.getInstrumentation().getTargetContext();
        assertEquals("com.example.androiddriver", appContext.getPackageName());
    }

    @Test
    public void checkMainText() {
        onView(withId(R.id.textView)).check(matches(withText("Android Driver App")));
    }

    @Test
    @Parameters(method="getVersionZeroFiles")
    public void testVersionZeroFiles(String cardPayload) throws IOException, JSONException {
        sendSinglePayLoad(cardPayload);
    }
    private List<String> getVersionZeroFiles() throws IOException {
        List<String> cards = getData("samples/v1.0/Scenarios/");
        cards.addAll(getData("samples/v1.0/Tests/"));
        return cards;
    }

    @Test
    @Parameters(method="getVersionOneFiles")
    public void testVersionOneFiles(String cardPayload) throws IOException, JSONException {
        sendSinglePayLoad(cardPayload);
    }
    private List<String> getVersionOneFiles() throws IOException {
        List<String> cards = getData("samples/v1.1/Scenarios/");
        cards.addAll(getData("samples/v1.1/Tests/"));
        return cards;
    }

    @Test
    @Parameters(method="getVersionTwoFiles")
    public void testVersionTwoFiles(String cardPayload) throws IOException, JSONException {
        sendSinglePayLoad(cardPayload);
    }
    private List<String> getVersionTwoFiles() throws IOException {
        List<String> cards = getData("samples/v1.2/Scenarios/");
        cards.addAll(getData("samples/v1.2/Tests/"));
        return cards;
    }

    @Test
    @Parameters(method="getVersionThreeFiles")
    public void testVersionThreeFiles(String cardPayload) throws IOException, JSONException {
        sendSinglePayLoad(cardPayload);
    }
    private List<String> getVersionThreeFiles() throws IOException {
        List<String> cards = getData("samples/v1.3/Scenarios/");
        cards.addAll(getData("samples/v1.3/Tests/"));
        return cards;
    }


    public void sendSinglePayLoad(String path) throws IOException, JSONException {
        onView(withId(R.id.textView)).check(matches(withText("Android Driver App")));
        StringBuffer fileData = new StringBuffer();
        Context appContext = InstrumentationRegistry.getInstrumentation().getContext();
        AssetManager am = appContext.getAssets();
        InputStream is = am.open(path);
        String[] rs = appContext.getAssets().list("");
        ByteArrayOutputStream result = new ByteArrayOutputStream();
        byte[] buffer = new byte[1024];
        int length;
        while ((length = is.read(buffer)) != -1) {
            result.write(buffer, 0, length);
        }
        String jsonString = result.toString("UTF-8");
        Map<String,Object> params = new LinkedHashMap<>();
        params.put("cardPayload", jsonString);
        StringBuilder postData = new StringBuilder();
        for (Map.Entry<String,Object> param : params.entrySet()) {
            if (postData.length() != 0) postData.append('&');
            postData.append(URLEncoder.encode(param.getKey(), "UTF-8"));
            postData.append('=');
            postData.append(URLEncoder.encode(String.valueOf(param.getValue()), "UTF-8"));
        }
        byte[] postDataBytes = postData.toString().getBytes("UTF-8");
        URL url = new URL("http://localhost:8080/");
        HttpURLConnection conn = (HttpURLConnection)url.openConnection();
        conn.setRequestMethod("POST");
        conn.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
        conn.setRequestProperty("Content-Length", String.valueOf(postDataBytes.length));
        conn.setDoOutput(true);
        conn.getOutputStream().write(postDataBytes);

        Reader in = new BufferedReader(new InputStreamReader(conn.getInputStream(), "UTF-8"));

        StringBuilder sb = new StringBuilder();
        for (int c; (c = in.read()) >= 0;)
            sb.append((char)c);
        String response = sb.toString();


        int responseCode = conn.getResponseCode();
        assertEquals(responseCode, 200);
        Log.w("Response Code", Integer.toString(responseCode));
        Log.w("Result", response);
        JSONObject resJson = new JSONObject(response);
        if(renderedSuccessfully(resJson))
            assertTrue(isValidBase64(resJson));
        else
            assertTrue(nonEmptyErrorsAndWarnings(resJson));
    }

    public List<String> getData(String path) throws IOException {
        Context appContext = InstrumentationRegistry.getInstrumentation().getContext();
        String[] files = appContext.getAssets().list(path);
        List<String> cardPayLoads = new ArrayList<>();
        for(String file: files){
            String newPath = path + file;
            cardPayLoads.add(newPath);
        }
        return cardPayLoads;
    }
    public boolean renderedSuccessfully(JSONObject result) {
        try {
            String imageString = result.getString("imageData");
            return imageString.length() > 0;
        }
        catch(Exception e){
            return false;
        }
    }

    public boolean isValidBase64(JSONObject result){
        try {

            String imgString = result.getString("imageData");
            byte[] byteBuffer = java.util.Base64.getDecoder().decode(imgString);
            String copyOfImg = java.util.Base64.getEncoder().encodeToString(byteBuffer);
            return imgString.equals(copyOfImg);
        }
        catch(Exception e){
            return false;
        }
    }

    public boolean nonEmptyErrorsAndWarnings(JSONObject result){
        try{
            JSONArray errors = result.getJSONArray("errors");
            JSONArray warnings = result.getJSONArray("warnings");
            return (errors.length() > 0 || warnings.length() > 0);

        }
        catch(Exception e){
            return false;
        }
    }

}