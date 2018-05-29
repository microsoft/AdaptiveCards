package io.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;

import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;

import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;

/** Abstract class that specifies image loading mechanism */
public abstract class GenericImageLoaderAsync extends AsyncTask<String, Void, HttpRequestResult<Bitmap>>
{
    RenderedAdaptiveCard m_renderedCard;
    String m_imageBaseUrl;

    GenericImageLoaderAsync(RenderedAdaptiveCard renderedCard, String imageBaseUrl)
    {
        m_renderedCard = renderedCard;
        m_imageBaseUrl = imageBaseUrl;
    }

    private HttpRequestResult<Bitmap> loadOnlineImage(String url) throws IOException, URISyntaxException
    {
        Bitmap bitmap;
        byte[] bytes = HttpRequestHelper.get(url);
        if (bytes == null)
        {
            throw new IOException("Failed to retrieve content from " + url);
        }

        bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
        bitmap = styleBitmap(bitmap);

        if (bitmap == null)
        {
            throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
        }

        return new HttpRequestResult<>(bitmap);
    }

    HttpRequestResult<Bitmap> loadImage(String path, Context context)
    {
        // Try loading online using only the path first
        try
        {
            return loadOnlineImage(path);
        }
        catch (MalformedURLException e1) {
            // Then try using image base URL to load online
            try
            {
                if (m_imageBaseUrl == null || m_imageBaseUrl.isEmpty())
                {
                    return new HttpRequestResult<>(new Exception("Image base URL is empty or not specified"));
                }

                // Construct a URL using the image base URL and path
                URL urlContext = new URL(m_imageBaseUrl);
                URL url = new URL(urlContext, path);

                return loadOnlineImage(url.toString());
            }
            catch (MalformedURLException e2)
            {
                // Then try reading it from local resources
                return Util.loadLocalImage(m_imageBaseUrl, context, path);
            }
            catch (Exception e)
            {
                return new HttpRequestResult<>(e);
            }
        }
        catch (Exception excep)
        {
            return new HttpRequestResult<>(excep);
        }
    }

    // By default, this function keeps the bitmap as is
    protected Bitmap styleBitmap(Bitmap bitmap)
    {
        return bitmap;
    }

    @Override
    protected void onPostExecute(HttpRequestResult<Bitmap> result)
    {
        if (result.isSuccessful())
        {
            onSuccessfulPostExecute(result.getResult());
        }
        else
        {
            m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
        }
    }

    abstract void onSuccessfulPostExecute(Bitmap result);
}
