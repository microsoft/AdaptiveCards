// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.graphics.Paint;
import android.graphics.Rect;
import android.graphics.drawable.BitmapDrawable;
import android.view.ViewGroup;

import io.adaptivecards.objectmodel.BackgroundImage;
import io.adaptivecards.renderer.http.HttpRequestResult;

public class BackgroundImageLoaderAsync extends GenericImageLoaderAsync
{
    private Context m_context;
    private ViewGroup m_layout;
    private BackgroundImage m_backgroundImageProperties;

    public BackgroundImageLoaderAsync(RenderedAdaptiveCard renderedCard, Context context, ViewGroup layout, String imageBaseUrl, int maxWidth, BackgroundImage backgroundImageProperties)
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
    }

    private class BackgroundImageDrawable extends BitmapDrawable
    {
        private Bitmap m_bitmap;
        private BackgroundImage m_backgroundImageProperties;

        public BackgroundImageDrawable(Resources resources, Bitmap bitmap, BackgroundImage backgroundImageProperties)
        {
            // A 1x1 bitmap is created to avoid the container to have a minimum width/height defined by the actual image
            // When the background is set with setBackground, the layout may grow if the original image is larger than the layout
            super(resources, Bitmap.createBitmap(1, 1, Bitmap.Config.ARGB_8888));
            m_bitmap = bitmap;
            m_backgroundImageProperties = backgroundImageProperties;
        }

        @Override
        public void draw(Canvas canvas)
        {
            switch (m_backgroundImageProperties.GetFillMode())
            {
                case Repeat:
                    tileHorizontallyAndVertically(canvas);
                    break;
                case RepeatVertically:
                    tileVertically(canvas);
                    break;
                case RepeatHorizontally:
                    tileHorizontally(canvas);
                    break;
                case Cover:
                default:
                    resizeBitmapForCover(canvas);
                    break;
            }
        }

        /**
         *
         * @param originalSizeBitmap Bitmap to be drawn in the container
         * @return Max scale factor between x and y scale factor
         */
        private double getScaleFactorForCover(Canvas containerCanvas, Bitmap originalSizeBitmap)
        {
            double xScaleFactor = (double)containerCanvas.getWidth() / (double)originalSizeBitmap.getWidth();
            double yScaleFactor = (double)containerCanvas.getHeight() / (double)originalSizeBitmap.getHeight();

            return Math.max(xScaleFactor, yScaleFactor);
        }

        // TODO: Optimize the rendering as drawBitmap source rectangle can scale images automatically
        // Taken from here https://stackoverflow.com/questions/35276834/scale-bitmap-maintaining-aspect-ratio-and-fitting-both-width-and-height
        /**
         * Resizes the bitmap so the bitmap will completely fill the container where it is inserted
         * @param canvas
         */
        private void resizeBitmapForCover(Canvas canvas)
        {
            Bitmap bitmap = m_bitmap;
            double originalWidth = bitmap.getWidth(), originalHeight = bitmap.getHeight();
            double scale = getScaleFactorForCover(canvas, bitmap);

            int scaledWidth = (int)(scale * originalWidth);
            int scaledHeight = (int)(scale * originalHeight);
            Bitmap background = Bitmap.createBitmap(scaledWidth, scaledHeight, Bitmap.Config.ARGB_8888);
            Canvas backgroundCanvas = new Canvas(background);

            Matrix transformation = new Matrix();
            transformation.preScale((float)scale, (float)scale);
            Paint scaledImagePaint = new Paint();
            scaledImagePaint.setFilterBitmap(true);
            backgroundCanvas.drawBitmap(bitmap, transformation, scaledImagePaint);

            // canvasWidth <= scaledBitmapWidth and canvasHeight <= scaledBitmapHeight
            int canvasWidth = canvas.getWidth(), canvasHeight = canvas.getHeight();
            int origX = 0, origY = 0;
            switch (m_backgroundImageProperties.GetHorizontalAlignment())
            {
                case Center:
                    origX = (scaledWidth - canvasWidth) / 2;
                    break;
                case Right:
                    origX = scaledWidth - canvasWidth;
                    break;
            }

            switch (m_backgroundImageProperties.GetVerticalAlignment())
            {
                case Center:
                    origY = (scaledHeight - canvasHeight) / 2;
                    break;
                case Bottom:
                    origY = scaledHeight - canvasHeight;
                    break;
            }

            canvas.drawBitmap(background,
                                new Rect(origX, origY, origX + canvasWidth, origY + canvasHeight),
                                new Rect(0, 0, canvasWidth, canvasHeight),
                                scaledImagePaint);
        }

        private void tileHorizontally(Canvas canvas)
        {
            float verticalOffset;
            Bitmap bitmap = m_bitmap;
            switch (m_backgroundImageProperties.GetVerticalAlignment())
            {
                case Bottom:
                    verticalOffset = canvas.getHeight() - bitmap.getHeight();
                    break;
                case Center:
                    verticalOffset = (canvas.getHeight() - bitmap.getHeight()) / (float) 2;
                    break;
                case Top:
                default:
                    verticalOffset = 0;
                    break;
            }

            int imageWidth  = bitmap.getWidth();
            int canvasWidth = canvas.getWidth();
            for (int x = 0; x < canvasWidth; x += imageWidth)
            {
                int remainingWidth = canvasWidth - x;
                // If the image can be drawn completely, then do it
                if (imageWidth <= remainingWidth)
                {
                    canvas.drawBitmap(bitmap, x, verticalOffset, getPaint());
                }
                else
                {
                    int imageHeight = bitmap.getHeight();
                    canvas.drawBitmap(bitmap,
                                        new Rect(0, 0, remainingWidth, imageHeight),
                                        new Rect(x, (int)verticalOffset, canvasWidth, (int)verticalOffset + imageHeight),
                                        getPaint());
                }
            }
        }

        private void tileVertically(Canvas canvas)
        {
            Bitmap bitmap = m_bitmap;
            float horizontalOffset;
            switch (m_backgroundImageProperties.GetHorizontalAlignment())
            {
                case Right:
                    horizontalOffset = canvas.getWidth() - bitmap.getWidth();
                    break;
                case Center:
                    horizontalOffset = (canvas.getWidth() - bitmap.getWidth()) / (float) 2;
                    break;
                case Left:
                default:
                    horizontalOffset = 0;
                    break;
            }

            int imageHeight  = bitmap.getHeight();
            int canvasHeight = canvas.getHeight();
            for (int y = 0; y < canvasHeight; y += imageHeight)
            {
                int remainingHeight = canvasHeight - y;
                // If the image can be drawn completely, then do it
                if (imageHeight <= remainingHeight)
                {
                    canvas.drawBitmap(bitmap, horizontalOffset, y, getPaint());
                }
                else
                {
                    int imageWidth = bitmap.getWidth();
                    canvas.drawBitmap(bitmap,
                        new Rect(0, 0, imageWidth, remainingHeight),
                        new Rect((int)horizontalOffset, y, (int)horizontalOffset + imageWidth, canvasHeight),
                        getPaint());
                }
            }
        }

        private void tileHorizontallyAndVertically(Canvas canvas)
        {
            Bitmap bitmap = m_bitmap;

            int imageHeight = bitmap.getHeight();
            int imageWidth  = bitmap.getWidth();
            int canvasHeight = canvas.getHeight();
            int canvasWidth = canvas.getWidth();
            for (int y = 0; y < canvasHeight; y += imageHeight)
            {
                int remainingHeight = canvasHeight - y;
                for (int x = 0; x < canvasWidth; x += imageWidth)
                {
                    int remainingWidth = canvasWidth - x;
                    // If the image can be drawn completely, then do it
                    if (imageWidth <= remainingWidth && imageHeight <= remainingHeight)
                    {
                        canvas.drawBitmap(bitmap, x, y, getPaint());
                    }
                    else
                    {
                        // If the image can't be drawn completely, then draw as much of the image as possible
                        int drawableWidth = Math.min(remainingWidth, imageWidth);
                        int drawableHeight = Math.min(remainingHeight, imageHeight);

                        canvas.drawBitmap(bitmap,
                            new Rect(0, 0, drawableWidth, drawableHeight),
                            new Rect(x, y, x + drawableWidth, y + drawableHeight),
                            getPaint());
                    }
                }
            }
        }
    }
}
