package io.adaptivecards.renderer;

import android.media.MediaDataSource;
import android.os.Build;
import android.support.annotation.RequiresApi;

/**
 * Created by almedina on 7/31/2018.
 */

@RequiresApi(api = Build.VERSION_CODES.M)
public abstract class IOnlineMediaLoader extends MediaDataSource
{
    public abstract void loadMedia(IMediaDownloadListener mediaLoaderListener);
}
