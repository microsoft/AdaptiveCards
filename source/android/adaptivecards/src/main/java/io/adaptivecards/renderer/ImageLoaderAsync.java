package io.adaptivecards.renderer;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.view.View;

import java.io.IOException;

import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;

public abstract class ImageLoaderAsync extends AsyncTask<String, Void, HttpRequestResult<Bitmap>>
{

    public ImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView)
    {
        m_view = containerView;
        m_renderedCard = renderedCard;
    }

    @Override
    protected HttpRequestResult<Bitmap> doInBackground(String... args)
    {
        try
        {
            Bitmap bitmap = null;
            byte[] bytes = HttpRequestHelper.get(args[0]);
            if (bytes == null)
            {
                throw new IOException("Failed to retrieve content from " + args[0]);
            }

            bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
            bitmap = styleBitmap(bitmap);

            if (bitmap == null)
            {
                throw new IOException("Failed to convert content to bitmap: " + new String(bytes));
            }

            return new HttpRequestResult<Bitmap>(bitmap);
        }
        catch (Exception excep)
        {
            return new HttpRequestResult<Bitmap>(excep);
        }
    }

    @Override
    protected void onPostExecute(HttpRequestResult<Bitmap> result)
    {
        if (result.isSuccessful())
        {
            renderBitmap(result.getResult());
        }
        else
        {
            m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
        }
    }

    protected abstract Bitmap styleBitmap(Bitmap bitmap);
    protected abstract void renderBitmap(Bitmap bitmap);

    protected View m_view; // button and imageview inherit from this
    private RenderedAdaptiveCard m_renderedCard;

}
