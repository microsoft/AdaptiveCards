package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.view.ViewGroup;
import android.widget.ImageView;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.FontSizeOptions;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.Image;
import com.microsoft.adaptivecards.objectmodel.ImageSize;
import com.microsoft.adaptivecards.objectmodel.ImageSizeOptions;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

/**
 * Created by bekao on 4/27/2017.
 */

public class ImageRenderer implements BaseCardElementRenderer
{
    private ImageRenderer()
    {
    }

    public static ImageRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ImageRenderer();
        }

        return s_instance;
    }

    private class ImageLoaderAsync extends AsyncTask<String, Void, Bitmap>
    {
        ImageLoaderAsync(ImageView imageView)
        {
            m_imageView = imageView;
        }

        @Override
        protected Bitmap doInBackground(String... args)
        {
            try
            {
                return BitmapFactory.decodeStream((InputStream)new URL(args[0]).getContent());
            }
            catch (IOException ioExcep)
            {
                // TODO: Where to log?
            }

            return null;
        }

        @Override
        protected void onPostExecute(Bitmap result)
        {
            if (result != null)
            {
                m_imageView.setImageBitmap(result);
            }
        }

        private ImageView m_imageView;
    }

    private static void setImageSize(ImageView imageView, ImageSize imageSize, ImageSizeOptions imageSizeOptions)
    {
        if (imageSize.swigValue() == ImageSize.Auto.swigValue())
        {
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Stretch.swigValue())
        {
            imageView.setScaleType(ImageView.ScaleType.CENTER_CROP);
        }
        else if (imageSize.swigValue() == ImageSize.Small.swigValue())
        {
            imageView.setMaxWidth(imageSizeOptions.getSmallSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Medium.swigValue())
        {
            imageView.setMaxWidth(imageSizeOptions.getMediumSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Large.swigValue())
        {
            imageView.setMaxWidth(imageSizeOptions.getLargeSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else
        {
            throw new IllegalArgumentException("Unknown image size: " + imageSize.toString());
        }

        imageView.setAdjustViewBounds(true);
    }

    public ViewGroup render(Context context, ViewGroup viewGroup, BaseCardElement baseCardElement, HostOptions hostOptions)
    {
        Image image = null;
        if (baseCardElement instanceof Image)
        {
            image = (Image) baseCardElement;
        }
        else if ((image = Image.dynamic_cast(baseCardElement)) == null)
        {
            return viewGroup;
        }

        ImageView imageView = new ImageView(context);
        new ImageLoaderAsync(imageView).execute(image.GetUrl());
        setImageSize(imageView, image.GetImageSize(), hostOptions.getImageSizes());
        image.GetImageStyle().swigValue()
        imageView.setMaxWidth(image.GetImageSize().swigValue());
        image.GetHorizontalAlignment().swigValue()
        imageView.setLayoutDirection(L);
        return viewGroup;
    }

    private static ImageRenderer s_instance = null;
}
