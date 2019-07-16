// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.http;

import android.text.TextUtils;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;
import java.net.URLDecoder;
import java.util.Map;

import static java.net.HttpURLConnection.HTTP_MOVED_PERM;
import static java.net.HttpURLConnection.HTTP_MOVED_TEMP;
import static java.net.HttpURLConnection.HTTP_SEE_OTHER;

public abstract class HttpRequestHelper
{
    private static HttpURLConnection connect(String url, String method, Map<String, String> requestProperty, boolean doOutput /* for post/puts */, boolean useCaches)
            throws MalformedURLException, URISyntaxException, IOException
    {
        //Decode the url since the url in the card may already be encoded
        URL netURL = new URL(URLDecoder.decode(url, "UTF-8"));
        URI uri = new URI(netURL.getProtocol(), netURL.getUserInfo(), netURL.getHost(), netURL.getPort(), netURL.getPath(), netURL.getQuery(), netURL.getRef());
        netURL = uri.toURL();

        HttpURLConnection conn = (HttpURLConnection) netURL.openConnection();
        conn.setRequestMethod(method);
        conn.setInstanceFollowRedirects(true);
        conn.setDoOutput(doOutput);
        conn.setUseCaches(useCaches);

        if (requestProperty != null)
        {
            // Set HTTP header
            for (Map.Entry<String, String> entry : requestProperty.entrySet())
            {
                conn.setRequestProperty(entry.getKey(), entry.getValue());
            }
        }

        return conn;
    }

    private static byte[] copyInputStreamToByteArray(InputStream inputStream)
            throws IOException
    {
        ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();

        final int bufferSize = 4096;
        byte[] buffer = new byte[bufferSize];
        int size;
        while ((size = inputStream.read(buffer)) != -1)
        {
            byteArrayOutputStream.write(buffer, 0, size);
        }

        return byteArrayOutputStream.toByteArray();
    }

    public static byte[] get(String url, Map<String, String> requestProperty)
            throws MalformedURLException, URISyntaxException, IOException
    {
        HttpURLConnection conn = connect(url, HTTP_METHOD_GET, requestProperty, false, true);
        conn.connect();
        int code = conn.getResponseCode();
        boolean redirected = code == HTTP_MOVED_PERM || code == HTTP_MOVED_TEMP || code == HTTP_SEE_OTHER;
        String location = conn.getHeaderField("Location");
        if (!redirected || TextUtils.isEmpty(location))
        {
            BufferedInputStream inputStream = new BufferedInputStream(conn.getInputStream());
            byte[] bytes = copyInputStreamToByteArray(inputStream);
            inputStream.close();
            return bytes;
        }

        return get(location, requestProperty);
    }

    public static byte[] get(String url)
            throws MalformedURLException, URISyntaxException, IOException
    {
        return get(url, null);
    }

    public static void query(String url, Map<String, String> requestProperty)
            throws MalformedURLException, URISyntaxException, IOException
    {
        HttpURLConnection conn = connect(url, HTTP_METHOD_GET, requestProperty, false, true);
        conn.connect();
        int code = conn.getResponseCode();
        boolean redirected = code == HTTP_MOVED_PERM || code == HTTP_MOVED_TEMP || code == HTTP_SEE_OTHER;
        String location = conn.getHeaderField("Location");
        if (!redirected || TextUtils.isEmpty(location))
        {
            return;
        }

        query(location, requestProperty);
    }

    public static void query(String url)
            throws MalformedURLException, URISyntaxException, IOException
    {
        query(url, null);
    }

    private static  byte[] requestBody(String url, String method, Map<String, String> requestProperty, String body)
            throws MalformedURLException, URISyntaxException, IOException
    {
        byte[] bodyBytes = body.getBytes("UTF-8");
        requestProperty.put("Content-Length", String.valueOf(bodyBytes.length));
        HttpURLConnection conn = connect(url, method, requestProperty, true, false);

        OutputStream outputStream = conn.getOutputStream();
        outputStream.write(bodyBytes);

        BufferedInputStream inputStream = new BufferedInputStream(conn.getInputStream());
        byte[] bytes = copyInputStreamToByteArray(inputStream);

        outputStream.close();
        inputStream.close();

        return bytes;
    }

    public static byte[] post(String url, Map<String, String> requestProperty, String body)
            throws MalformedURLException, URISyntaxException, IOException
    {
        return requestBody(url, HTTP_METHOD_POST, requestProperty, body);
    }

    public static byte[] put(String url, Map<String, String> requestProperty, String body)
            throws MalformedURLException, URISyntaxException, IOException
    {
        return requestBody(url, HTTP_METHOD_PUT, requestProperty, body);
    }

    public static final String HTTP_METHOD_GET = "GET";
    public static final String HTTP_METHOD_POST = "POST";
    public static final String HTTP_METHOD_PUT = "PUT";
}
