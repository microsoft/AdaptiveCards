package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Shader;
import android.graphics.drawable.BitmapDrawable;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.renderer.http.HttpRequestResult;

public class BackgroundImageLoaderAsync extends GenericImageLoaderAsync
{
    private Context m_context;
    private LinearLayout m_layout;
    private BackgroundImage m_backgroundImageProperties;

    public BackgroundImageLoaderAsync(RenderedAdaptiveCard renderedCard, Context context, LinearLayout layout, String imageBaseUrl, int maxWidth, BackgroundImage backgroundImageProperties)
    {
        super(renderedCard, imageBaseUrl, maxWidth);

        m_context = context;
        m_layout = layout;
        m_backgroundImageProperties = backgroundImageProperties;
    }

    @Override
    protected HttpRequestResult<Bitmap> doInBackground(String... args)
    {
        if (args.length == 0)
        {
            return null;
        }
        return loadImage(args[0], m_context);
    }

    void onSuccessfulPostExecute(Bitmap bitmap)
    {
        BitmapDrawable background = new BackgroundImageDrawable(m_context.getResources(), bitmap, m_backgroundImageProperties);
        m_layout.setBackground(background);
        m_layout.bringChildToFront(m_layout.getChildAt(0));
    }

    private class BackgroundImageDrawable extends BitmapDrawable
    {
        private BackgroundImage m_backgroundImageProperties;

        public BackgroundImageDrawable(Resources resources, Bitmap bitmap, BackgroundImage backgroundImageProperties)
        {
            super(resources, bitmap);
            m_backgroundImageProperties = backgroundImageProperties;
        }

        @Override
        public void draw(Canvas canvas)
        {
            switch (m_backgroundImageProperties.GetMode())
            {
                case Repeat:
                    setTileModeXY(Shader.TileMode.REPEAT, Shader.TileMode.REPEAT);
                    super.draw(canvas);
                    break;
                case RepeatVertically:
                    tileVertically(canvas);
                    break;
                case RepeatHorizontally:
                    tileHorizontally(canvas);
                    break;
                case Stretch:
                default:
                    super.draw(canvas);
                    break;
            }
        }

        private void tileHorizontally(Canvas canvas)
        {
            float verticalOffset;
            switch (m_backgroundImageProperties.GetVerticalAlignment())
            {
                case Bottom:
                    verticalOffset = canvas.getHeight() - getBitmap().getHeight();
                    break;
                case Center:
                    verticalOffset = (canvas.getHeight() - getBitmap().getHeight()) / (float) 2;
                    break;
                case Top:
                default:
                    verticalOffset = 0;
                    break;
            }

            for (int x = 0; x < canvas.getWidth(); x += getBitmap().getWidth())
            {
                canvas.drawBitmap(getBitmap(), x, verticalOffset, getPaint());
            }
        }

        private void tileVertically(Canvas canvas)
        {
            float horizontalOffset;
            switch (m_backgroundImageProperties.GetHorizontalAlignment())
            {
                case Right:
                    horizontalOffset = canvas.getWidth() - getBitmap().getWidth();
                    break;
                case Center:
                    horizontalOffset = (canvas.getWidth() - getBitmap().getWidth()) / (float) 2;
                    break;
                case Left:
                default:
                    horizontalOffset = 0;
                    break;
            }

            for (int y = 0; y < canvas.getHeight(); y += getBitmap().getHeight())
            {
                canvas.drawBitmap(getBitmap(), horizontalOffset, y, getPaint());
            }
        }
    }
}
