package io.adaptivecards.renderer;

import android.media.MediaDataSource;
import android.os.Build;
import android.support.annotation.RequiresApi;

@RequiresApi(api = Build.VERSION_CODES.M)
public abstract class IOnlineMediaLoader extends MediaDataSource
{
    public IOnlineMediaLoader()
    {
    }

    public IOnlineMediaLoader(String mediaUri)
    {
        m_mediaUrl = mediaUri;
    }

    public String getMediaUrl()
    {
        return m_mediaUrl;
    }

    public abstract void loadMedia(IMediaDownloadListener mediaLoaderListener);

    private String m_mediaUrl;
}
