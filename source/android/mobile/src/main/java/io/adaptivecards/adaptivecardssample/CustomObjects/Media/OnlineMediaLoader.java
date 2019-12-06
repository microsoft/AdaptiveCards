package io.adaptivecards.adaptivecardssample.CustomObjects.Media;

import android.media.MediaDataSource;
import android.os.AsyncTask;
import android.os.Build;
import android.support.annotation.RequiresApi;

import io.adaptivecards.objectmodel.MediaSourceVector;
import io.adaptivecards.renderer.IMediaDataSourceOnPreparedListener;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.http.HttpRequestHelper;

@RequiresApi(api = Build.VERSION_CODES.M)
public class OnlineMediaLoader implements IOnlineMediaLoader
{
    public class OnlineFileAvailableChecker extends AsyncTask<String, Void, Boolean>
    {
        public OnlineFileAvailableChecker(String uri)
        {
            m_uri = uri;
        }

        @Override
        protected Boolean doInBackground(String... strings) {
            // if the provided uri is a valid uri or is valid with the resource resolver, then use that
            // otherwise, try to get the media from a local file
            try
            {
                HttpRequestHelper.query(m_uri);
                return true;
            }
            catch (Exception e)
            {
                // Do nothing if the media was not found at all
                e.printStackTrace();
                return false;
            }
        }

        private String m_uri;
    }


    @Override
    public MediaDataSource loadOnlineMedia(MediaSourceVector mediaSources, IMediaDataSourceOnPreparedListener mediaDataSourceOnPreparedListener)
    {
        final long mediaSourcesSize = mediaSources.size();
        for(int i = 0; i < mediaSourcesSize; i++)
        {
            String mediaUri = mediaSources.get(i).GetUrl();

            OnlineFileAvailableChecker checker = new OnlineFileAvailableChecker(mediaUri);
            try
            {
                Boolean fileExists = checker.execute("").get();
                if(fileExists)
                {
                    return new MediaDataSourceImpl(mediaUri, mediaDataSourceOnPreparedListener);
                }
            }
            catch (Exception e)
            {
            }
        }
        return null;
    }
}
