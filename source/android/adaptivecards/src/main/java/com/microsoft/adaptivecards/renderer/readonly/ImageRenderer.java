package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.BitmapShader;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Shader;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.microsoft.adaptivecards.renderer.http.HttpRequestHelper;
import com.microsoft.adaptivecards.renderer.http.HttpRequestResult;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.HorizontalAlignment;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.Image;
import com.microsoft.adaptivecards.objectmodel.ImageSize;
import com.microsoft.adaptivecards.objectmodel.ImageSizesConfig;
import com.microsoft.adaptivecards.objectmodel.ImageStyle;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;

import java.io.IOException;
import java.util.Vector;

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

    private class ImageLoaderAsync extends AsyncTask<String, Void, HttpRequestResult<Bitmap>>
    {
        ImageLoaderAsync(Context context, ImageView imageView, ImageStyle imageStyle)
        {
            m_context = context;
            m_imageView = imageView;
            m_imageStyle = imageStyle;
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
                if (bitmap != null && m_imageStyle == ImageStyle.Person)
                {
                    Bitmap circleBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
                    BitmapShader shader = new BitmapShader(bitmap,  Shader.TileMode.CLAMP, Shader.TileMode.CLAMP);
                    Paint paint = new Paint();
                    paint.setShader(shader);
                    Canvas c = new Canvas(circleBitmap);
                    c.drawCircle(bitmap.getWidth()/2, bitmap.getHeight()/2, bitmap.getWidth()/2, paint);
                    bitmap = circleBitmap;
                }

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
                m_imageView.setImageBitmap(result.getResult());
            }
            else
            {
                Toast.makeText(m_context, "Unable to load image: " + result.getException().getMessage(), Toast.LENGTH_SHORT).show();
            }
        }

        private Context m_context;
        private ImageView m_imageView;
        private ImageStyle m_imageStyle;
        private String errorString;
    }

    private static void setImageSize(ImageView imageView, ImageSize imageSize, ImageSizesConfig imageSizesConfig)
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
            imageView.setMaxWidth((int)imageSizesConfig.getSmallSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Medium.swigValue())
        {
            imageView.setMaxWidth((int)imageSizesConfig.getMediumSize());
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        }
        else if (imageSize.swigValue() == ImageSize.Large.swigValue())
        {
            imageView.setMaxWidth((int)imageSizesConfig.getLargeSize());
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

    @Override
    public View render(
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            HostConfig hostConfig)
    {
        Image image = null;
        if (baseCardElement instanceof Image)
        {
            image = (Image) baseCardElement;
        }
        else if ((image = Image.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Image object model.");
        }

        ImageView imageView = new ImageView(context);
        imageView.setTag(image);
        ImageLoaderAsync imageLoaderAsync = new ImageLoaderAsync(context, imageView, image.GetImageStyle());
        imageLoaderAsync.execute(image.GetUrl());
        setImageSize(imageView, image.GetImageSize(), hostConfig.getImageSizes());
        imageView.setLayoutParams(new LinearLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT));
        setSeparationConfig(context, viewGroup, image.GetSeparationStyle(), hostConfig.getImage().getSeparation(), hostConfig.getStrongSeparation(), true /* horizontal line */);
        viewGroup.addView(setHorizontalAlignment(context, imageView, image.GetHorizontalAlignment()));
        return imageView;
    }

    private static ImageRenderer s_instance = null;
}
