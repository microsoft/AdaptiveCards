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
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.IOnlineImageLoader;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
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
     * Set ImageView size. Only for use in ImageSet.
     * @param context
     * @param imageView the view to resize
     * @param image the parsed Image
     * @param hostConfig the HostConfig that configures semantic 'size' values
     */
    private static void sizeImageForImageSet(Context context, ImageView imageView, Image image, HostConfig hostConfig)
    {
        int semanticWidth = getImageSizePixels(context, image.GetImageSize(), hostConfig.GetImageSizes());

        imageView.setAdjustViewBounds(true);
        imageView.setScaleType(ImageView.ScaleType.FIT_START);
        imageView.setLayoutParams(new LinearLayout.LayoutParams(semanticWidth, LinearLayout.LayoutParams.WRAP_CONTENT));
    }

    /**
     * Calculate horizontal bias for ConstraintLayout
     * @param image the parsed Image
     * @return horizontal bias
     */
    private static float getHorizontalBias(Image image) {
        if (image.GetHorizontalAlignment() == HorizontalAlignment.Center)
        {
            return 0.5f;
        }
        if (image.GetHorizontalAlignment() == HorizontalAlignment.Right)
        {
            return 1;
        }
        return 0;
    }

    /**
     * Calculate constraints for placing/sizing this ImageView in a ConstraintLayout
     * For sizing Images in ImageSets, use {@link #sizeImageForImageSet}
     * @param context
     * @param imageView the view to constrain
     * @param image the parsed Image
     * @param hostConfig the HostConfig that configures semantic 'size' values
     * @return
     */
    private static ConstraintSet getConstraints(Context context, ImageView imageView, Image image, HostConfig hostConfig)
    {
        long explicitWidth = image.GetPixelWidth();
        long explicitHeight = image.GetPixelHeight();
        ImageSize imageSize = image.GetImageSize();
        ConstraintSet constraints = new ConstraintSet();

        // ConstraintSet requires unique id
        if(imageView.getId() == View.NO_ID) {
            imageView.setId(View.generateViewId());
        }
        int id = imageView.getId();

        // Set horizontal alignment
        constraints.setHorizontalBias(id, getHorizontalBias(image));

        // By default, scale image and maintain aspect ratio
        imageView.setAdjustViewBounds(true);
        imageView.setScaleType(ImageView.ScaleType.FIT_START);

        // By default, constrain view to top of parent, and expand width to parent
        constraints.connect(id, ConstraintSet.START, ConstraintSet.PARENT_ID, ConstraintSet.START);
        constraints.connect(id, ConstraintSet.END, ConstraintSet.PARENT_ID, ConstraintSet.END);
        constraints.connect(id, ConstraintSet.TOP, ConstraintSet.PARENT_ID, ConstraintSet.TOP);
        constraints.constrainWidth(id, ConstraintSet.MATCH_CONSTRAINT);
        constraints.constrainHeight(id, ConstraintSet.WRAP_CONTENT);

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
                // Limit width expansion to the given width (this approach ensures width never exceeds parent)
                constraints.constrainMaxWidth(id, Util.dpToPixels(context, explicitWidth));
            }
            if (explicitHeight != 0)
            {
                // Exact height
                constraints.constrainHeight(id, Util.dpToPixels(context, explicitHeight));
            }
        }
        // Semantic size from host config
        else if (imageSize == ImageSize.Small || imageSize == ImageSize.Medium || imageSize == ImageSize.Large)
        {
            // Limit width expansion to the given width (this approach ensures width never exceeds parent)
            constraints.constrainMaxWidth(id, getImageSizePixels(context, imageSize, hostConfig.GetImageSizes()));
        }
        // Don't scale image
        else if (imageSize != ImageSize.Stretch)
        {
            // Disable width expansion
            constraints.constrainWidth(id, ConstraintSet.WRAP_CONTENT);
        }
        return constraints;
    }

    /**
     * Create container for this image (with stretch height if needed), and assign to TagContent's stretchContainer
     * @param context
     * @param image the parsed Image
     * @param tagContent the image's TagContent
     * @return the container
     */
    private static ConstraintLayout getContainer(Context context, Image image, TagContent tagContent)
    {
        ConstraintLayout container = new ConstraintLayout(context);
        tagContent.SetStretchContainer(container);

        // Grow container layout if height is stretch (assumes the parent is a vertical LinearLayout)
        int weight = (image.GetHeight() == HeightType.Stretch) ? 1 : 0;
        container.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT, weight));

        return container;
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

        // No container needed for image in ImageSet
        if(isInImageSet)
        {
            sizeImageForImageSet(context, imageView, image, hostConfig);
            viewGroup.addView(imageView);
        }
        // ConstraintLayout container for first-class images
        else
        {
            ConstraintLayout container = getContainer(context, image, tagContent);
            container.addView(imageView);
            getConstraints(context, imageView, image, hostConfig).applyTo(container);
            viewGroup.addView(container);
        }

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
