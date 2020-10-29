// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.AsyncTask;
import android.util.DisplayMetrics;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.URL;

import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;
import io.adaptivecards.objectmodel.CharVector;
import io.adaptivecards.objectmodel.AdaptiveBase64Util;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

/** Abstract class that specifies image loading mechanism */
public abstract class GenericImageLoaderAsync extends AsyncTask<String, Void, HttpRequestResult<Bitmap>>
{
    RenderedAdaptiveCard m_renderedCard;
    String m_imageBaseUrl;
    int m_maxWidth;
    IOnlineImageLoader m_onlineImageLoader = null;

    GenericImageLoaderAsync(RenderedAdaptiveCard renderedCard, String imageBaseUrl)
    {
        this(renderedCard, imageBaseUrl, -1);
    }

    GenericImageLoaderAsync(RenderedAdaptiveCard renderedCard, String imageBaseUrl, int maxWidth)
    {
        m_renderedCard = renderedCard;
        m_imageBaseUrl = imageBaseUrl;
        m_maxWidth = maxWidth;
    }

    protected String getUriScheme(String path) throws URISyntaxException
    {
        try
        {
            // Try to get the uri scheme using java URI class
            URI uri = new URI(path);
            return uri.getScheme();
        }
        catch (URISyntaxException uriSyntaxException)
        {
            // If the path couldn't be converted with the java URI then try to follow
            // https://tools.ietf.org/html/rfc7595 finding the first ':' and consider that
            // as the scheme. This is made to support the working svg support for android
            int schemeEndIndex = path.indexOf(':');
            if(schemeEndIndex > 0)
            {
                return path.substring(0, schemeEndIndex);
            }
            else
            {
                // If the path doesn't contain a scheme then throw the URISyntaxException
                throw uriSyntaxException;
            }
        }
    }

    // Main function to try different ways to load an image
    HttpRequestResult<Bitmap> loadImage(String path, Context context)
    {
        try
        {
            // Step 1: Check if user specified the scheme name as a Resource Resolver
            String uriScheme = getUriScheme(path);
            IResourceResolver resourceResolver = CardRendererRegistration.getInstance().getResourceResolver(uriScheme);

            if (resourceResolver != null)
            {
                if (m_maxWidth != -1)
                {
                    return resourceResolver.resolveImageResource(path, this, m_maxWidth);
                }
                else
                {
                    return resourceResolver.resolveImageResource(path, this);
                }
            }
            else if (path.startsWith("content:"))
            {
                return loadLocalContentImage(context, path);
            }

            //Step 2: If resource resolver doesn't exist, then try with treating it as a dataUri
            // Let's try to see if we got the image in the card as a base64 encoded string
            // The syntax of data URIs as in RFX 2397 is  data:[<media type>][;base64],<data>
            if (uriScheme.equals("data"))
            {
                return loadDataUriImage(path);
            }

            // Step 3: Try to load the image from an online source, if the URL is not valid, try using the imageBaseURL, else try a local resource
            // Try loading online using only the path first
            try
            {
                if(m_onlineImageLoader != null)
                {
                    HttpRequestResult<Bitmap> loadedOnlineImage = m_onlineImageLoader.loadOnlineImage(path, this);
                    if(loadedOnlineImage.getResult() != null)
                    {
                        return new HttpRequestResult(styleBitmap(loadedOnlineImage.getResult()));
                    }
                    else
                    {
                        return loadedOnlineImage;
                    }
                }
                else
                {
                    return loadOnlineImage(path);
                }
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

                    if(m_onlineImageLoader != null)
                    {
                        HttpRequestResult<Bitmap> loadedOnlineImage = m_onlineImageLoader.loadOnlineImage(url.toString(), this);
                        if(loadedOnlineImage.getResult() != null)
                        {
                            return new HttpRequestResult(styleBitmap(loadedOnlineImage.getResult()));
                        }
                        else
                        {
                            return loadedOnlineImage;
                        }
                    }
                    else
                    {
                        return loadOnlineImage(url.toString());
                    }
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

    public HttpRequestResult<Bitmap> loadOnlineImage(String url) throws IOException, URISyntaxException
    {
        byte[] bytes = HttpRequestHelper.get(url);
        if (bytes == null)
        {
            throw new IOException("Failed to retrieve content from " + url);
        }

        Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
        bitmap = styleBitmap(bitmap);

        if (bitmap == null)
        {
            throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
        }

        return new HttpRequestResult<>(bitmap);
    }

    // Helper function to load local image URL from res/
    public HttpRequestResult<Bitmap> loadLocalImage(String imageBaseUrl, Context context, String url) throws IOException
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
        bitmap = styleBitmap(bitmap);
        if (bitmap == null)
        {
            throw new IOException("Failed to convert local content to bitmap: " + url);
        }

        return new HttpRequestResult<>(bitmap);
    }

    // Helper function to load local image from content://com.android.*, like
    // content://com.android.contacts/contacts/9/photo
    private HttpRequestResult<Bitmap> loadLocalContentImage(Context context, String url) throws IOException
    {
        Uri uri = Uri.parse(url);
        Bitmap bm = BitmapFactory.decodeStream(context.getContentResolver().openInputStream(uri));
        bm = styleBitmap(bm);
        if (bm == null)
        {
            throw  new IOException("Failed to convert local content image to bitmap: " + url);
        }

        return new HttpRequestResult<>(bm);
    }

    public HttpRequestResult<Bitmap> loadDataUriImage(String uri) throws Exception
    {
        String dataUri = AdaptiveBase64Util.ExtractDataFromUri(uri);
        CharVector decodedDataUri = AdaptiveBase64Util.Decode(dataUri);

        byte[] decodedByteArray = Util.getBytes(decodedDataUri);
        Bitmap bitmap = BitmapFactory.decodeByteArray(decodedByteArray, 0, decodedByteArray.length);
        bitmap = styleBitmap(bitmap);
        return new HttpRequestResult<>(bitmap);
    }

    /**
     * @deprecated Deprecated as of AdaptiveCards 1.2, replaced by {@link IResourceResolver}
     */
    @Deprecated
    public void registerCustomOnlineImageLoader(IOnlineImageLoader onlineImageLoader)
    {
        m_onlineImageLoader = onlineImageLoader;
    }

    // By default, this function keeps the bitmap as is
    public Bitmap styleBitmap(Bitmap bitmap)
    {
        return bitmap;
    }

    @Override
    protected void onPostExecute(HttpRequestResult<Bitmap> result)
    {
        if (result.isSuccessful())
        {
            Bitmap image = result.getResult();
            image.setDensity(DisplayMetrics.DENSITY_DEFAULT);
            onSuccessfulPostExecute(image);
        }
        else
        {
            m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
        }
    }

    abstract void onSuccessfulPostExecute(Bitmap result);
}
