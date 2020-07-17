// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapShader;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Shader;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.text.TextUtils;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.HorizontalAlignment;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.ImageSizesConfig;
import io.adaptivecards.objectmodel.ImageStyle;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.layout.HorizontalFlowLayout;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class ImageRenderer extends BaseCardElementRenderer
{
    protected ImageRenderer()
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

    private class ImageRendererImageLoaderAsync extends InnerImageLoaderAsync
    {
        ImageRendererImageLoaderAsync(
            RenderedAdaptiveCard renderedCard,
            ImageView imageView,
            String imageBaseUrl,
            ImageStyle imageStyle,
            int backgroundColor)
        {
            this(renderedCard, imageView, imageBaseUrl, imageStyle, backgroundColor, -1);
        }

        ImageRendererImageLoaderAsync(
            RenderedAdaptiveCard renderedCard,
            ImageView imageView,
            String imageBaseUrl,
            ImageStyle imageStyle,
            int backgroundColor,
            int maxWidth)
        {
            super(renderedCard, imageView, imageBaseUrl, maxWidth);
            m_imageStyle = imageStyle;
            m_backgroundColor = backgroundColor;
        }

        @Override
        public Bitmap styleBitmap(Bitmap bitmap)
        {
            if (bitmap != null && m_imageStyle == ImageStyle.Person)
            {
                Bitmap circleBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(), Bitmap.Config.ARGB_8888);
                BitmapShader shader = new BitmapShader(bitmap,  Shader.TileMode.CLAMP, Shader.TileMode.CLAMP);
                Paint paint = new Paint();
                paint.setShader(shader);

                Paint backgroundColorPaint = new Paint();
                backgroundColorPaint.setColor(m_backgroundColor);

                Canvas c = new Canvas(circleBitmap);
                c.drawCircle(bitmap.getWidth()/2, bitmap.getHeight()/2, bitmap.getWidth()/2, backgroundColorPaint);
                c.drawCircle(bitmap.getWidth()/2, bitmap.getHeight()/2, bitmap.getWidth()/2, paint);
                bitmap = circleBitmap;
            }

            return bitmap;
        }

        @Override
        protected void renderBitmap(Bitmap bitmap)
        {
            ImageView view = (ImageView) m_view ;
            view.setImageBitmap(bitmap);
        }

        private ImageStyle m_imageStyle;
        private int m_backgroundColor;
    }

    /**
     * Get the pixels for the given ImageSize, as configured in the given ImageSizesConfig
     * @param context
     * @param imageSize parsed ImageSize
     * @param imageSizesConfig ImageSizesConfig from host config
     * @return size in pixels, scaled by screen density
     */
    private static int getImageSizePixels(Context context, ImageSize imageSize, ImageSizesConfig imageSizesConfig) {
        int imageSizeLimit = context.getResources().getDisplayMetrics().widthPixels;

        if (imageSize == ImageSize.Small)
        {
            imageSizeLimit = Util.dpToPixels(context, imageSizesConfig.getSmallSize());
        }
        else if (imageSize == ImageSize.Medium)
        {
            imageSizeLimit = Util.dpToPixels(context, imageSizesConfig.getMediumSize());
        }
        else if (imageSize == ImageSize.Large)
        {
            imageSizeLimit = Util.dpToPixels(context, imageSizesConfig.getLargeSize());
        }

        return imageSizeLimit;
    }

    /**
     * Set ImageView size according to 'height', 'width', and 'size' attributes of the given Image
     * @param context
     * @param imageView the view to resize
     * @param image the parsed Image
     * @param hostConfig the HostConfig that configures semantic 'size' values
     * @param isInImageSet true if the Image was declared in an ImageSet
     */
    private static void setImageSize(Context context, ImageView imageView, Image image, HostConfig hostConfig, boolean isInImageSet)
    {
        long explicitWidth = image.GetPixelWidth();
        long explicitHeight = image.GetPixelHeight();
        ImageSize imageSize = image.GetImageSize();

        imageView.setAdjustViewBounds(true);
        imageView.setScaleType(ImageView.ScaleType.FIT_START);

        int viewWidth = ViewGroup.LayoutParams.WRAP_CONTENT;
        int viewHeight = ViewGroup.LayoutParams.WRAP_CONTENT;

        // explicit height and/or width given
        if (explicitWidth != 0 || explicitHeight != 0)
        {
            if (explicitWidth != 0 && explicitHeight != 0)
            {
                imageView.setScaleType(ImageView.ScaleType.FIT_XY);
            }
            if (explicitWidth != 0)
            {
                viewWidth = Util.dpToPixels(context, explicitWidth);
            }
            if (explicitHeight != 0)
            {
                viewHeight = Util.dpToPixels(context, explicitHeight);
            }
        }
        // stretch
        else if (imageSize == ImageSize.Stretch)
        {
            viewWidth = ViewGroup.LayoutParams.MATCH_PARENT;
        }
        // semantic size from host config
        else if ((imageSize == ImageSize.Small) || (imageSize == ImageSize.Medium) || (imageSize == ImageSize.Large))
        {
            viewWidth = getImageSizePixels(context, imageSize, hostConfig.GetImageSizes());
        }
        else if (imageSize != ImageSize.Auto && imageSize != ImageSize.None) {
            // TODO: Instead of failing, proceed to render w/ default size "auto"
            throw new IllegalArgumentException("Unknown image size: " + imageSize.toString());
        }
        imageView.setLayoutParams(new LinearLayout.LayoutParams(viewWidth, viewHeight));
    }

    private int getBackgroundColorFromHexCode(String hexColorCode)
    {
        int backgroundColor = 0;
        if (!TextUtils.isEmpty(hexColorCode))
        {
            // check that it has 9 characters and that the color string isn't a color name
            if (hexColorCode.length() == 9 && hexColorCode.charAt(0) == '#')
            {
                try
                {
                    // if the color string is not valid, parseColor will throw a IllegalArgumentException
                    // so we just turn the color to transparent on the catch statement
                    backgroundColor = Color.parseColor(hexColorCode);
                }
                catch (IllegalArgumentException e)
                {
                    backgroundColor = 0;
                }
            }
            else
            {
                backgroundColor = 0;
            }
        }

        return backgroundColor;
    }

    private int getImageHorizontalAlignment(Image image)
    {
        HorizontalAlignment horizontalAlignment = image.GetHorizontalAlignment();
        int gravity = Gravity.LEFT;

        if (horizontalAlignment == HorizontalAlignment.Center)
        {
            gravity = Gravity.CENTER_HORIZONTAL;
        }
        else if (horizontalAlignment == HorizontalAlignment.Right)
        {
            gravity = Gravity.RIGHT;
        }

        return gravity;
    }

    private View setImageHeightAndHorizontalAlignment(Context context, boolean isInImageSet, ImageView imageView, Image image, TagContent tagContent)
    {
        int height = LinearLayout.LayoutParams.WRAP_CONTENT, width = LinearLayout.LayoutParams.WRAP_CONTENT, weight = 0;

        // The expected behavior for the image must be:
        // If the image has stretch size:
        //      width grows as big as the parent but only uses as much vertical space as needed
        // If the image has stretch size and also stretches in height:
        //      width grows as big as the parent and uses as much leftover vertical space as there is
        // If the image has a fixed or auto size:
        //      width is limited to image size or defined size and only uses as much vertical space as needed
        // If the image has a fixed or auto size and also stretched in height:
        //      width is limited to image size or defined size and uses as much leftover vertical space as there is
        if (image.GetImageSize() == ImageSize.Stretch)
        {
            width = LinearLayout.LayoutParams.MATCH_PARENT;
        }

        if (image.GetHeight() == HeightType.Stretch)
        {
            height = LinearLayout.LayoutParams.MATCH_PARENT;
            weight = 1;
        }

        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(width, height, weight);

        // Set horizontal alignment for the image
        layoutParams.gravity = getImageHorizontalAlignment(image);

        // If the image is part of an imageSet or has height auto, we set the layout parameter to
        // it and return just the view, otherwise we have to create a layout to grow in height and
        // contain the image avoiding it to grow larger and making the background color to stretch
        if (isInImageSet || image.GetHeight() != HeightType.Stretch)
        {
            imageView.setLayoutParams(layoutParams);
            return imageView;
        }
        else
        {
            LinearLayout stretchLayout = new LinearLayout(context);
            stretchLayout.setLayoutParams(layoutParams);
            stretchLayout.addView(imageView);
            tagContent.SetStretchContainer(stretchLayout);
            return stretchLayout;
        }
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
            RenderArgs renderArgs)
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

        boolean isInImageSet = viewGroup instanceof HorizontalFlowLayout;
        View separator = setSpacingAndSeparator(context, viewGroup, image.GetSpacing(), image.GetSeparator(), hostConfig, !isInImageSet /* horizontal line */, isInImageSet);

        ImageView imageView = new ImageView(context);

        int backgroundColor = getBackgroundColorFromHexCode(image.GetBackgroundColor());

        if(image.GetImageStyle() != ImageStyle.Person)
        {
            imageView.setBackgroundColor(backgroundColor);
        }

        int imageSizeLimit = getImageSizePixels(context, image.GetImageSize(), hostConfig.GetImageSizes());
        ImageRendererImageLoaderAsync imageLoaderAsync = new ImageRendererImageLoaderAsync(
            renderedCard,
            imageView,
            hostConfig.GetImageBaseUrl(),
            image.GetImageStyle(),
            backgroundColor,
            imageSizeLimit);

        IOnlineImageLoader onlineImageLoader = CardRendererRegistration.getInstance().getOnlineImageLoader();
        if (onlineImageLoader != null)
        {
            imageLoaderAsync.registerCustomOnlineImageLoader(onlineImageLoader);
        }

        imageLoaderAsync.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, image.GetUrl());

        TagContent tagContent = new TagContent(image, separator, viewGroup);

        View imageContainer = setImageHeightAndHorizontalAlignment(context, isInImageSet, imageView, image, tagContent);
        setImageSize(context, imageView, image, hostConfig, isInImageSet);

        viewGroup.addView(imageContainer);
        imageView.setTag(tagContent);
        setVisibility(baseCardElement.GetIsVisible(), imageView);

        if (image.GetSelectAction() != null)
        {
            imageView.setClickable(true);
            imageView.setOnClickListener(new BaseActionElementRenderer.SelectActionOnClickListener(renderedCard, image.GetSelectAction(), cardActionHandler));
        }

        return imageView;
    }

    private static ImageRenderer s_instance = null;
}
