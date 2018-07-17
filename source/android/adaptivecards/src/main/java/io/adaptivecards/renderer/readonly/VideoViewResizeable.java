package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.media.MediaMetadataRetriever;
import android.net.Uri;
import android.widget.VideoView;

import java.util.HashMap;

// Taken from here: https://stackoverflow.com/questions/13603553/videoview-to-match-parent-height-and-keep-aspect-ratio/40475998

public class VideoViewResizeable extends VideoView
{
    public VideoViewResizeable(Context context)
    {
        super(context);
    }

    public void retrieveVideoDimensions(String uri)
    {
        MediaMetadataRetriever metadataRetriever = new MediaMetadataRetriever();
        metadataRetriever.setDataSource(uri, new HashMap<String, String>());

        m_videoHeight = Integer.parseInt(metadataRetriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_VIDEO_HEIGHT));
        m_videoWidth = Integer.parseInt(metadataRetriever.extractMetadata(MediaMetadataRetriever.METADATA_KEY_VIDEO_WIDTH));
    }

    public void setVideoURI(String uri, boolean isAudio)
    {
        m_isAudio = isAudio;
        if(!m_isAudio)
        {
            retrieveVideoDimensions(uri);
        }
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
        else
        {
            // Give some height so the media controller fits
            height = 200;
        }
        setMeasuredDimension(width, height);
    }

    public boolean isAudioOnly()
    {
        return m_isAudio;
    }

    private int m_videoWidth;
    private int m_videoHeight;
    private boolean m_isAudio = false;
}
