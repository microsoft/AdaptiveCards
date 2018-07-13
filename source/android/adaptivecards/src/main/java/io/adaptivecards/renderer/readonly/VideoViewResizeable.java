package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.media.MediaMetadataRetriever;
import android.net.Uri;
import android.view.View;
import android.widget.ImageView;
import android.widget.VideoView;

import java.net.HttpURLConnection;
import java.net.URL;
import java.util.HashMap;

// Taken from here: https://stackoverflow.com/questions/13603553/videoview-to-match-parent-height-and-keep-aspect-ratio/40475998

public class VideoViewResizeable extends VideoView {

    public VideoViewResizeable(Context context)
    {
        super(context);
    }

    public void retrieveMetadata(String uri)
    {
        MediaMetadataRetriever metadataRetriever = new MediaMetadataRetriever();
        metadataRetriever.setDataSource(uri, new HashMap<String, String>());

        String mimetype = metadataRetriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_MIMETYPE);
        if(!mimetype.startsWith("audio"))
        {
            m_videoHeight = Integer.parseInt(metadataRetriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_VIDEO_HEIGHT));
            m_videoWidth = Integer.parseInt(metadataRetriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_VIDEO_WIDTH));
        }
        else
        {
            m_isAudio = true;
            // Hard coded values, not sure what to do here, but this works
            m_videoHeight = 300;
            m_videoWidth = 1000;
        }
    }

    public void setVideoURI(String uri)
    {
        retrieveMetadata(uri);
        super.setVideoURI(Uri.parse(uri));
    }

    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec)
    {
        int width = getDefaultSize(m_videoWidth, widthMeasureSpec);
        int height = getDefaultSize(m_videoHeight, heightMeasureSpec);
        if (m_videoWidth > 0 && m_videoHeight > 0)
        {
            if ((m_videoWidth * height) > (width * m_videoHeight))
            {
                height = (width * m_videoHeight) / m_videoWidth;
            }
            else if ((m_videoWidth * height) < (width * m_videoHeight))
            {
                width = (height * m_videoWidth) / m_videoHeight;
            }
        }
        setMeasuredDimension(width, height);
    }

    public boolean containsVideo()
    {
        return !m_isAudio;
    }

    private int m_videoWidth;
    private int m_videoHeight;
    private boolean m_isAudio = false;
}
