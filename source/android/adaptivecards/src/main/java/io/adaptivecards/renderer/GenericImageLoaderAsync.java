package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;

import java.io.IOException;
import java.io.InputStream;
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
    IOnlineImageLoader m_onlineImageLoader = null;

    GenericImageLoaderAsync(RenderedAdaptiveCard renderedCard, String imageBaseUrl)
    {
        m_renderedCard = renderedCard;
        m_imageBaseUrl = imageBaseUrl;
        m_onlineImageLoader = new OnlineImageLoader();
    }

    // Main function to try different ways to load an image
    HttpRequestResult<Bitmap> loadImage(String path, Context context)
    {
        try
        {
            // Try loading online using only the path first
            try
            {
                return m_onlineImageLoader.loadOnlineImage(path, this);
            }
            catch (MalformedURLException e1) {
                // Then try using image base URL to load online
                try
                {
                    if (m_imageBaseUrl == null || m_imageBaseUrl.isEmpty())
                    {
                        throw new IOException("Image base URL is empty or not specified");
                    }

                    // Construct a URL using the image base URL and path
                    URL urlContext = new URL(m_imageBaseUrl);
                    URL url = new URL(urlContext, path);

                    return m_onlineImageLoader.loadOnlineImage(url.toString(), this);
                    // return loadOnlineImage(url.toString());
                }
                catch (MalformedURLException e2)
                {
                    // Then try reading it from local resources
                    return loadLocalImage(m_imageBaseUrl, context, path);
                }
            }
        }
        catch (Exception e)
        {
            return new HttpRequestResult<>(e);
        }
    }

    // Helper function to load local image URL from res/
    private HttpRequestResult<Bitmap> loadLocalImage(String imageBaseUrl, Context context, String url) throws IOException
    {
        String authority = context.getPackageName();

        // Get image identifier
        Resources resources = context.getResources();
        int identifier = resources.getIdentifier(url, imageBaseUrl, authority);
        if (identifier == 0)
        {
            throw new IOException("Image not found: " + url);
        }

        InputStream ins = resources.openRawResource(identifier);
        Bitmap bitmap = BitmapFactory.decodeStream(ins);
        if (bitmap == null)
        {
            throw new IOException("Failed to convert local content to bitmap: " + url);
        }

        return new HttpRequestResult<>(bitmap);
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

    public void registerCustomOnlineImageLoader(IOnlineImageLoader onlineImageLoader)
    {
        m_onlineImageLoader = onlineImageLoader;
    }

    abstract void onSuccessfulPostExecute(Bitmap result);
}
