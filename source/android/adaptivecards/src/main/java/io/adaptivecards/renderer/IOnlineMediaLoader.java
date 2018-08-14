package io.adaptivecards.renderer;

import android.media.MediaDataSource;
import android.media.MediaPlayer;
import android.os.Build;
import android.support.annotation.RequiresApi;

@RequiresApi(api = Build.VERSION_CODES.M)
public interface IOnlineMediaLoader
{
    MediaDataSource loadOnlineMedia(String uri, IMediaDataSourceOnPreparedListener mediaDataSourceOnPreparedListener);
}
