// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import androidx.fragment.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.IBaseCardElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSet;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.ImageVector;
import io.adaptivecards.renderer.registration.CardRendererRegistration;
import io.adaptivecards.renderer.layout.HorizontalFlowLayout;

public class ImageSetRenderer extends BaseCardElementRenderer
{
    protected ImageSetRenderer()
    {
    }

    public static ImageSetRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new ImageSetRenderer();
        }

        return s_instance;
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
        ImageSet imageSet = Util.castTo(baseCardElement, ImageSet.class);

        IBaseCardElementRenderer imageRenderer = CardRendererRegistration.getInstance().getRenderer(CardElementType.Image.toString());
        if (imageRenderer == null)
        {
            throw new IllegalArgumentException("No renderer registered for: " + CardElementType.Image.toString());
        }

        HorizontalFlowLayout horizFlowLayout = new HorizontalFlowLayout(context);
        horizFlowLayout.setTag(new TagContent(imageSet));

        setVisibility(baseCardElement.GetIsVisible(), horizFlowLayout);

        ImageSize imageSize = imageSet.GetImageSize();
        ImageVector imageVector = imageSet.GetImages();
        long imageVectorSize = imageVector.size();
        for (int i = 0; i < imageVectorSize; i++)
        {
            Image image = imageVector.get(i);

            // TODO: temporary - this will be handled in the object model
            if(imageSize != ImageSize.Small && imageSize != ImageSize.Medium && imageSize != ImageSize.Large) {
                imageSize = ImageSize.Medium;
            }
            image.SetImageSize(imageSize);

            try
            {
                View imageView = imageRenderer.render(renderedCard, context, fragmentManager, horizFlowLayout, image, cardActionHandler, hostConfig, renderArgs);
                ((ImageView) imageView).setMaxHeight(Util.dpToPixels(context, hostConfig.GetImageSet().getMaxImageHeight()));
            }
            catch (AdaptiveFallbackException e)
            {
                continue;
            }
        }

        if (imageSet.GetHeight() == HeightType.Stretch)
        {
            viewGroup.addView(horizFlowLayout, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            viewGroup.addView(horizFlowLayout, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        }

        return horizFlowLayout;
    }

    private static ImageSetRenderer s_instance = null;
}
