package io.adaptivecards.renderer;

import android.graphics.Bitmap;
import android.view.View;

import io.adaptivecards.renderer.http.HttpRequestResult;

public abstract class InnerImageLoaderAsync extends GenericImageLoaderAsync
{
    protected View m_view; // button and imageview inherit from this

    public InnerImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String imageBaseUrl)
    {
        super(renderedCard, imageBaseUrl);

        m_view = containerView;
    }

    @Override
    protected HttpRequestResult<Bitmap> doInBackground(String... args)
    {
        if (args.length == 0)
        {
            return null;
        }
        return loadImage(args[0], m_view.getContext());
    }

    void onSuccessfulPostExecute(Bitmap bitmap)
    {
        renderBitmap(bitmap);
    }

    protected abstract void renderBitmap(Bitmap bitmap);
}
