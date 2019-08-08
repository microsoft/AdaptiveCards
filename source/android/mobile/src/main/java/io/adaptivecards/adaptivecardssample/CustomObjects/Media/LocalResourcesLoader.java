package io.adaptivecards.adaptivecardssample.CustomObjects.Media;

import android.app.Activity;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.io.IOException;
import java.io.InputStream;
import java.net.URISyntaxException;

import io.adaptivecards.renderer.GenericImageLoaderAsync;
import io.adaptivecards.renderer.IResourceResolver;
import io.adaptivecards.renderer.http.HttpRequestResult;

public class LocalResourcesLoader implements IResourceResolver
{
    public LocalResourcesLoader(Activity activity)
    {
        m_activity = activity;
    }

    @Override
    public HttpRequestResult<Bitmap> resolveImageResource(String url, GenericImageLoaderAsync loader) throws IOException, URISyntaxException
    {
        // Get image identifier
        String authority = m_activity.getPackageName();
        Resources resources = m_activity.getResources();

        // For host app only provides image file name as url, host app can pass "package:[IMAGE NAME]" as replacement for
        // meeting the valid URL format checking. Here we will remove this prefix to get file name.
        if (url.startsWith("package:"))
        {
            url = url.replace("package:", "drawable/");
        }

        int identifier = resources.getIdentifier(url, "", authority);
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

    @Override
    public HttpRequestResult<Bitmap> resolveImageResource(String url, GenericImageLoaderAsync loader, int maxWidth) throws IOException, URISyntaxException
    {
        return resolveImageResource(url, loader);
    }

    private Activity m_activity;
}
