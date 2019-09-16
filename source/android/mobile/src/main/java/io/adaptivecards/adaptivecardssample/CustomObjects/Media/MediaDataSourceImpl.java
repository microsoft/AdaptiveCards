package io.adaptivecards.adaptivecardssample.CustomObjects.Media;

import android.media.MediaDataSource;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.util.Log;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;

import io.adaptivecards.renderer.IMediaDataSourceOnPreparedListener;

/*
 * MediaDataSource implementation taken from https://github.com/jacks205/MediaDataSourceExample
 * */
@RequiresApi(api = Build.VERSION_CODES.M)
public class MediaDataSourceImpl extends MediaDataSource
{
    MediaDataSourceImpl(String uri, IMediaDataSourceOnPreparedListener mediaDataSourceOnPreparedListener)
    {
        m_mediaUri = uri;
        m_mediaDataSourceListener = mediaDataSourceOnPreparedListener;
        Thread mediaDownloadThread = new Thread(m_downloadMediaRunnable);
        mediaDownloadThread.start();
    }

    Runnable m_downloadMediaRunnable = new Runnable() {
        @Override
        public void run() {
            try
            {
                URL url = new URL(m_mediaUri);
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

                // Call this function to signalize that the mediaPlayer is able to prepare with the current state for DataMediaSource
                m_mediaDataSourceListener.prepareMediaPlayer();
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
        }
    };

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

    private volatile IMediaDataSourceOnPreparedListener m_mediaDataSourceListener;

    private volatile String m_mediaUri;
    private volatile byte[] m_mediaBuffer;
}
