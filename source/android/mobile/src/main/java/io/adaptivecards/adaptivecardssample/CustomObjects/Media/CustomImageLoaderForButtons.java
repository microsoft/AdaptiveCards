package io.adaptivecards.adaptivecardssample.CustomObjects.Media;

import android.graphics.Bitmap;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import android.graphics.BitmapFactory;

import java.net.URISyntaxException;

import io.adaptivecards.renderer.GenericImageLoaderAsync;
import io.adaptivecards.renderer.IResourceResolver;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;

public class CustomImageLoaderForButtons implements IResourceResolver
{
    @Override
    public HttpRequestResult<Bitmap> resolveImageResource(String s, GenericImageLoaderAsync genericImageLoaderAsync) throws IOException, URISyntaxException
    {
        byte[] bytes = HttpRequestHelper.get(s);
        if (bytes == null)
        {
            throw new IOException("Failed to retrieve content from " + s);
        }

        Bitmap bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
        bitmap = genericImageLoaderAsync.styleBitmap(bitmap);

        if (bitmap == null)
        {
            throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
        }

        return new HttpRequestResult<>(bitmap);
    }

    @Override
    public HttpRequestResult<Bitmap> resolveImageResource(String s, GenericImageLoaderAsync genericImageLoaderAsync, int i) throws IOException, URISyntaxException
    {
        return resolveImageResource(s, genericImageLoaderAsync);
    }
}
