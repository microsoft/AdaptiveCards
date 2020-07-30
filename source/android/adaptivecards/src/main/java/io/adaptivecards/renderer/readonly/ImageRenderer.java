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
import android.support.constraint.ConstraintLayout;
import android.support.constraint.ConstraintSet;
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
     * Set ImageView size. Only for use in ImageSet. For first-class Images, use {@link #setImageConstraints}
     * @param context
     * @param imageView
     * @param image
     * @param hostConfig
     * @return the ImageView
     */
    private static View setImageSize(Context context, ImageView imageView, Image image, HostConfig hostConfig)
    {
        int semanticWidth = getImageSizePixels(context, image.GetImageSize(), hostConfig.GetImageSizes());

        imageView.setAdjustViewBounds(true);
        imageView.setScaleType(ImageView.ScaleType.FIT_START);
        imageView.setLayoutParams(new LinearLayout.LayoutParams(semanticWidth, LinearLayout.LayoutParams.WRAP_CONTENT));

        return imageView;
    }

    /**
     * Wrap ImageView in a layout, to control horizontal alignment and stretch height, then constrain size of ImageView.
     * For sizing Images in ImageSets, use {@link #setImageSize}
     * @param context
     * @param imageView the view to resize
     * @param image the parsed Image
     * @param hostConfig the HostConfig that configures semantic 'size' values
     * @param tagContent the view's TagContent (to assign stretchContainer)
     * @return the wrapper layout
     */
    private static View setImageConstraints(Context context, ImageView imageView, Image image, HostConfig hostConfig, TagContent tagContent)
    {
        // Wrapper layout around the ImageView
        ConstraintLayout wrapper = new ConstraintLayout(context);
        wrapper.addView(imageView);
        tagContent.SetStretchContainer(wrapper);

        // Grow wrapper layout if height is stretch (assumes the parent is a vertical LinearLayout)
        if (image.GetHeight() == HeightType.Stretch)
        {
            wrapper.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            wrapper.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        }

        // ConstraintLayout requires unique id
        if(imageView.getId() == View.NO_ID) {
            imageView.setId(View.generateViewId());
        }

        long explicitWidth = image.GetPixelWidth();
        long explicitHeight = image.GetPixelHeight();
        ImageSize imageSize = image.GetImageSize();
        ConstraintSet imageConstraints = new ConstraintSet();

        // Set horizontal alignment
        if (image.GetHorizontalAlignment() == HorizontalAlignment.Center)
        {
            imageConstraints.setHorizontalBias(imageView.getId(), 0.5f);
        }
        else if (image.GetHorizontalAlignment() == HorizontalAlignment.Right)
        {
            imageConstraints.setHorizontalBias(imageView.getId(), 1);
        }
        else
        {
            imageConstraints.setHorizontalBias(imageView.getId(), 0);
        }

        // By default, scale image and maintain aspect ratio
        imageView.setAdjustViewBounds(true);
        imageView.setScaleType(ImageView.ScaleType.FIT_START);

        // By default, constrain view to top of parent, and stretch width to fill parent
        imageConstraints.connect(imageView.getId(), ConstraintSet.START, ConstraintSet.PARENT_ID, ConstraintSet.START);
        imageConstraints.connect(imageView.getId(), ConstraintSet.END, ConstraintSet.PARENT_ID, ConstraintSet.END);
        imageConstraints.connect(imageView.getId(), ConstraintSet.TOP, ConstraintSet.PARENT_ID, ConstraintSet.TOP);
        imageConstraints.constrainWidth(imageView.getId(), ConstraintSet.MATCH_CONSTRAINT);
        imageConstraints.constrainHeight(imageView.getId(), ConstraintSet.WRAP_CONTENT);

        // Explicit height and/or width given
        if (explicitWidth != 0 || explicitHeight != 0)
        {
            if (explicitWidth != 0 && explicitHeight != 0)
            {
                // If both are set, ignore aspect ratio
                imageView.setScaleType(ImageView.ScaleType.FIT_XY);
            }
            if (explicitWidth != 0)
            {
                // Stretch width + max width = exact width
                imageConstraints.constrainMaxWidth(imageView.getId(), Util.dpToPixels(context, explicitWidth));
            }
            if (explicitHeight != 0)
            {
                // Exact height
                imageConstraints.constrainHeight(imageView.getId(), Util.dpToPixels(context, explicitHeight));
            }
        }
        // Semantic size from host config
        else if (imageSize == ImageSize.Small || imageSize == ImageSize.Medium || imageSize == ImageSize.Large)
        {
            // Stretch width + max width = exact width
            imageConstraints.constrainMaxWidth(imageView.getId(), getImageSizePixels(context, imageSize, hostConfig.GetImageSizes()));
        }
        // Don't scale image
        else if (imageSize == ImageSize.Auto || imageSize == ImageSize.None)
        {
            // Disable stretch width
            imageConstraints.constrainWidth(imageView.getId(), ConstraintSet.WRAP_CONTENT);
        }
        else if (imageSize != ImageSize.Stretch)
        {
            // TODO: Don't fail. Provide warning and then make a best-effort render w/ size "auto"
            throw new IllegalArgumentException("Unknown image size: " + imageSize.toString());
        }

        imageConstraints.applyTo(wrapper);
        return wrapper;
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

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        Image image = Util.castTo(baseCardElement, Image.class);

        View separator = null;
        boolean isInImageSet = viewGroup instanceof HorizontalFlowLayout;
        if (isInImageSet)
        {
            separator = setSpacingAndSeparator(context, viewGroup, image.GetSpacing(), image.GetSeparator(), hostConfig, false /* horizontal line */, isInImageSet);
        }

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

        View imageContainer = isInImageSet
            ? setImageSize(context, imageView, image, hostConfig)
            : setImageConstraints(context, imageView, image, hostConfig, tagContent);

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
