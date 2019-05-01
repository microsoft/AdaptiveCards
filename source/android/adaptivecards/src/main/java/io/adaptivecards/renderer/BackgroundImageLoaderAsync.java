// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Shader;
import android.graphics.drawable.BitmapDrawable;
import android.view.Gravity;
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
        background.set
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
            switch (m_backgroundImageProperties.GetFillMode())
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
                case Cover:
                default:
                    Bitmap bitmap = resizeBitmapForCover(canvas);
                    setGravity(getCoverAlignmentGravity());
                    super.draw(canvas);
                    break;
            }
        }

        /**
         *
         * @param containerCanvas
         * @param originalSizeBitmap
         * @return
         */
        private double getScaleFactorForCover(Canvas containerCanvas, Bitmap originalSizeBitmap)
        {
            double xScaleFactor = (double)containerCanvas.getWidth() / (double)originalSizeBitmap.getWidth();
            double yScaleFactor = (double)containerCanvas.getHeight() / (double)originalSizeBitmap.getHeight();

            return Math.max(xScaleFactor, yScaleFactor);
        }

        // Taken from here https://stackoverflow.com/questions/35276834/scale-bitmap-maintaining-aspect-ratio-and-fitting-both-width-and-height 
        /**
         * Resizes the bitmap so the bitmap will completely fill the container where it is inserted
         * @return
         */
        private Bitmap resizeBitmapForCover(Canvas canvas, Bitmap bitmap)
        {
            double originalWidth = bitmap.getWidth(), originalHeight = bitmap.getHeight();
            double scale = getScaleFactorForCover(canvas, bitmap);
            float xTranslation = 0.0f, yTranslation = 0.0f;

            Bitmap background = Bitmap.createBitmap((int)(scale * originalWidth), (int)(scale * originalHeight), Bitmap.Config.ARGB_8888);

            Matrix transformation = new Matrix();
            transformation.postTranslate(xTranslation, yTranslation);
            transformation.preScale((float)scale, (float)scale);
            Paint paint = new Paint();
            paint.setFilterBitmap(true);
            canvas.drawBitmap(bitmap, transformation, paint);
            return background;
        }

        private int getCoverAlignmentGravity()
        {
            int verticalAlignment = Gravity.TOP, horizontalAlignment = Gravity.LEFT;

            switch (m_backgroundImageProperties.GetVerticalAlignment())
            {
                case Center:
                    verticalAlignment = Gravity.CENTER_VERTICAL;
                    break;
                case Bottom:
                    verticalAlignment = Gravity.BOTTOM;
                    break;
                case Top:
                default:
                    verticalAlignment = Gravity.TOP;
                    break;
            }

            switch (m_backgroundImageProperties.GetHorizontalAlignment())
            {
                case Center:
                    horizontalAlignment = Gravity.CENTER_HORIZONTAL;
                    break;
                case Right:
                    horizontalAlignment = Gravity.RIGHT;
                    break;
                case Left:
                default:
                    horizontalAlignment = Gravity.LEFT;
                    break;
            }

            return (verticalAlignment | horizontalAlignment);
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
