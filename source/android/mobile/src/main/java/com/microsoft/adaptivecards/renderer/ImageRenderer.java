package com.microsoft.adaptivecards.renderer;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapShader;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Shader;
import android.os.AsyncTask;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HorizontalAlignment;
import com.microsoft.adaptivecards.objectmodel.HostOptions;
import com.microsoft.adaptivecards.objectmodel.Image;
import com.microsoft.adaptivecards.objectmodel.ImageSize;
import com.microsoft.adaptivecards.objectmodel.ImageSizeOptions;
import com.microsoft.adaptivecards.objectmodel.ImageStyle;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

/**
 * Created by bekao on 4/27/2017.
 */

public class ImageRenderer extends BaseCardElementRenderer
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
        ImageLoaderAsync(Context context, ImageView imageView, ImageStyle imageStyle)
        {
            m_context = context;
            m_imageView = imageView;
            m_imageStyle = imageStyle;
        }

        @Override
        protected Bitmap doInBackground(String... args)
        {
            String url = args[0];
            try
            {
                InputStream inputStream = new java.net.URL(url).openStream();
                Bitmap bitmap = BitmapFactory.decodeStream(inputStream);

                if (m_imageStyle == ImageStyle.Person)
                {
                    Bitmap circleBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
                    BitmapShader shader = new BitmapShader(bitmap,  Shader.TileMode.CLAMP, Shader.TileMode.CLAMP);
                    Paint paint = new Paint();
                    paint.setShader(shader);
                    Canvas c = new Canvas(circleBitmap);
                    c.drawCircle(bitmap.getWidth()/2, bitmap.getHeight()/2, bitmap.getWidth()/2, paint);
                    bitmap = circleBitmap;
                }

                return bitmap;
            }
            catch (IOException ioExcep)
            {
                errorString = ioExcep.getMessage();
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
            else
            {
                Toast.makeText(m_context, "Unable to load image: " + errorString, Toast.LENGTH_SHORT);
            }
        }

        private Context m_context;
        private ImageView m_imageView;
        private ImageStyle m_imageStyle;
        private String errorString;
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
            imageView.setMaxWidth((int)imageSizeOptions.getSmallSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Medium.swigValue())
        {
            imageView.setMaxWidth((int)imageSizeOptions.getMediumSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Large.swigValue())
        {
            imageView.setMaxWidth((int)imageSizeOptions.getLargeSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Default.swigValue())
        {
            // Default Android
        }
        else
        {
            throw new IllegalArgumentException("Unknown image size: " + imageSize.toString());
        }

        imageView.setAdjustViewBounds(true);
    }

    private static View setHorizontalAlignment(Context context, ImageView imageView, HorizontalAlignment horizontalAlignment)
    {
        if (horizontalAlignment.swigValue() == HorizontalAlignment.Left.swigValue())
        {
            return imageView;
        }
        if (horizontalAlignment.swigValue() == HorizontalAlignment.Right.swigValue())
        {
            RelativeLayout relativeLayout = new RelativeLayout(context);
            RelativeLayout.LayoutParams relativeLayoutParams = new RelativeLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
            relativeLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);
            relativeLayout.addView(imageView, relativeLayoutParams);
            relativeLayout.setLayoutParams(new LinearLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT));
            return relativeLayout;
        }
        if (horizontalAlignment.swigValue() == HorizontalAlignment.Center.swigValue())
        {
            LinearLayout.LayoutParams linearLayoutParams = (LinearLayout.LayoutParams) imageView.getLayoutParams();
            linearLayoutParams.gravity = Gravity.CENTER;
            imageView.setLayoutParams(linearLayoutParams);
            return imageView;
        }
        else
        {
            throw new IllegalArgumentException("Unknown Horizontal alignment: " + horizontalAlignment.toString());
        }
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
        new ImageLoaderAsync(context, imageView, image.GetImageStyle()).execute(image.GetUrl());
        setImageSize(imageView, image.GetImageSize(), hostOptions.getImageSizes());
        imageView.setLayoutParams(new LinearLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT));
        setSeparationOptions(context, viewGroup, image.GetSeparationStyle(), hostOptions.getImage().getSeparation(), hostOptions.getStrongSeparation(), true /* horizontal line */);
        viewGroup.addView(setHorizontalAlignment(context, imageView, image.GetHorizontalAlignment()));
        return viewGroup;
    }

    private static ImageRenderer s_instance = null;
}
