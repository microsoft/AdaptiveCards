package io.adaptivecards.renderer.readonly;

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

import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.renderer.AdaptiveWarning;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.ImageSizesConfig;
import io.adaptivecards.objectmodel.ImageStyle;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.layout.HorizontalFlowLayout;

import java.io.IOException;

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
        ImageLoaderAsync(RenderedAdaptiveCard renderedCard, Context context, ImageView imageView, ImageStyle imageStyle)
        {
            m_context = context;
            m_imageView = imageView;
            m_imageStyle = imageStyle;
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
                m_renderedCard.addWarning(new AdaptiveWarning(AdaptiveWarning.UNABLE_TO_LOAD_IMAGE, result.getException().getMessage()));
            }
        }

        private Context m_context;
        private ImageView m_imageView;
        private ImageStyle m_imageStyle;
        private RenderedAdaptiveCard m_renderedCard;
    }

    private static void setImageSize(Context context, ImageView imageView, ImageSize imageSize, ImageSizesConfig imageSizesConfig) {
        imageView.setScaleType(ImageView.ScaleType.CENTER);
        if (imageSize == ImageSize.Stretch) {
            //ImageView must match parent for stretch to work
            imageView.setLayoutParams(new LinearLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.MATCH_PARENT));
            imageView.setScaleType(ImageView.ScaleType.CENTER_INSIDE);
        } else if (imageSize == ImageSize.Small) {
            imageView.setMaxWidth(Util.dpToPixels(context, imageSizesConfig.getSmallSize()));
        } else if (imageSize == ImageSize.Medium) {
            imageView.setMaxWidth(Util.dpToPixels(context, imageSizesConfig.getMediumSize()));
        } else if (imageSize == ImageSize.Large) {
            imageView.setMaxWidth(Util.dpToPixels(context, imageSizesConfig.getLargeSize()));
        } else if (imageSize != ImageSize.Auto && imageSize != ImageSize.None){
            throw new IllegalArgumentException("Unknown image size: " + imageSize.toString());
        }

        imageView.setAdjustViewBounds(true);
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
    {
        Image image;
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
        ImageLoaderAsync imageLoaderAsync = new ImageLoaderAsync(renderedCard, context, imageView, image.GetImageStyle());
        imageLoaderAsync.execute(image.GetUrl());

        LinearLayout.LayoutParams layoutParams;
        if (image.GetImageSize() == ImageSize.Stretch)
        {
            //ImageView must match parent for stretch to work
            layoutParams = new LinearLayout.LayoutParams(RelativeLayout.LayoutParams.MATCH_PARENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
        }
        else
        {
            layoutParams = new LinearLayout.LayoutParams(RelativeLayout.LayoutParams.WRAP_CONTENT, RelativeLayout.LayoutParams.WRAP_CONTENT);
        }

        HorizontalAlignment horizontalAlignment = image.GetHorizontalAlignment();
        if (horizontalAlignment == HorizontalAlignment.Right)
        {
            layoutParams.gravity = Gravity.RIGHT;
        }
        else if (horizontalAlignment == HorizontalAlignment.Center)
        {
            layoutParams.gravity = Gravity.CENTER_HORIZONTAL;
        }

        if (image.GetSelectAction() != null)
        {
            imageView.setClickable(true);
            imageView.setOnClickListener(new ActionElementRenderer.ButtonOnClickListener(renderedCard, image.GetSelectAction(), cardActionHandler));
        }

        //set horizontalAlignment
        imageView.setLayoutParams(layoutParams);

        setImageSize(context, imageView, image.GetImageSize(), hostConfig.getImageSizes());
        setSpacingAndSeparator(context, viewGroup, image.GetSpacing(), image.GetSeparator(), hostConfig, !(viewGroup instanceof HorizontalFlowLayout) /* horizontal line */);

        viewGroup.addView(imageView);
        return imageView;
    }

    private static ImageRenderer s_instance = null;
}
