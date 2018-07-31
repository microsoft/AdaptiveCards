package io.adaptivecards.renderer;

import android.annotation.TargetApi;
import android.media.MediaDataSource;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.util.Log;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;

/**
 * Created by almedina on 7/30/2018.
 */

@TargetApi(Build.VERSION_CODES.M)
public class OnlineMediaLoader extends IOnlineMediaLoader
{

    Runnable m_downloadMediaRunnable = new Runnable() {
        @Override
        public void run() {
            try
            {
                URL url = new URL("https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4");
                InputStream inputStream = url.openStream();
                ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
                int read = 0;
                while(read != -1)
                {
                    read = inputStream.read();
                    byteArrayOutputStream.write(read);
                }
                inputStream.close();

                byteArrayOutputStream.flush();
                m_mediaBuffer = byteArrayOutputStream.toByteArray();

                byteArrayOutputStream.close();

                m_downloadListener.onMediaDownloaded();
            }
            catch (MalformedURLException urlException)
            {
                urlException.printStackTrace();
                Log.d("Error on video download", urlException.toString());
            }
            catch (IOException e)
            {
                e.printStackTrace();
                Log.d("Error on video download", e.toString());
            }
            finally
            {
                m_isDownloading = false;
            }
        }
    };

    public OnlineMediaLoader()
    {
        m_isDownloading = false;
    }

    public void loadMedia(IMediaDownloadListener mediaDownloadListener)
    {
        if(m_isDownloading)
        {
            return;
        }

        m_downloadListener = mediaDownloadListener;
        Thread mediaDownloadThread = new Thread(m_downloadMediaRunnable);
        mediaDownloadThread.start();
        m_isDownloading = true;
    }

    @Override
    public int readAt(long position, byte[] buffer, int offset, int size) throws IOException
    {
        synchronized (m_mediaBuffer)
        {
            int length = m_mediaBuffer.length;
            if(position >= length)
            {
                return -1;
            }

            if(position + size > length)
            {
                size -= (position + size) - length;
                // size = length - position;
            }
            System.arraycopy(m_mediaBuffer, (int)position, buffer, offset, size);
            return size;
        }
    }

    @Override
    public long getSize() throws IOException
    {
        synchronized (m_mediaBuffer)
        {
            return m_mediaBuffer.length;
        }
    }

    @Override
    public void close() throws IOException
    {
    }

    private volatile byte[] m_mediaBuffer;
    private volatile boolean m_isDownloading;

    private volatile IMediaDownloadListener m_downloadListener;
}
