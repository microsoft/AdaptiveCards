// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.net.Uri;
import android.os.AsyncTask;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.MediaSource;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.layout.FullscreenVideoView;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class MediaLoaderAsync extends AsyncTask<String, Void, Void>
{
    public MediaLoaderAsync(FullscreenVideoView mediaPlayer, MediaSource mediaSource, HostConfig hostConfig, boolean isAudio, Context context)
    {
        m_mediaView = mediaPlayer;
        m_mediaSource = mediaSource;
        m_hostConfig = hostConfig;
        m_isAudio = isAudio;
        m_context = context;
    }

    @Override
    protected Void doInBackground(String... strings) {
        // if the provided uri is a valid uri or is valid with the resource resolver, then use that
        // otherwise, try to get the media from a local file
        String mediaSourceUrl = m_mediaSource.GetUrl();
        try
        {
            // Try loading online using only the path first
            try
            {
                HttpRequestHelper.query(mediaSourceUrl);
                m_mediaView.setVideoURI(Uri.parse(mediaSourceUrl), m_isAudio);
            }
            catch (MalformedURLException e1)
            {
                // Then try using image base URL to load online
                String baseUrl = m_hostConfig.GetImageBaseUrl();
                try
                {
                    if (baseUrl == null || baseUrl.isEmpty())
                    {
                        throw new IOException("Image base URL is empty or not specified");
                    }

                    // Construct a URL using the image base URL and path
                    URL urlContext = new URL(baseUrl);
                    URL url = new URL(urlContext, mediaSourceUrl);

                    HttpRequestHelper.query(url.toString());
                    m_mediaView.setVideoURI(Uri.parse(baseUrl + mediaSourceUrl), m_isAudio);

                }
                catch (MalformedURLException e2)
                {
                    String authority = m_context.getPackageName();

                    // Get media identifier
                    Resources resources = m_context.getResources();
                    int identifier = resources.getIdentifier(mediaSourceUrl, baseUrl, authority);
                    if (identifier == 0)
                    {
                        throw new IOException("Media not found: " + mediaSourceUrl);
                    }

                    m_mediaView.setVideoPath("android.resource://" + authority + "/" + baseUrl + "/" + mediaSourceUrl, m_isAudio);

                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
            // Do nothing if the media was not found at all
        }
        return null;
    }


    private FullscreenVideoView m_mediaView;
    private MediaSource m_mediaSource;
    private HostConfig m_hostConfig;
    private boolean m_isAudio;
    private Context m_context;
}
