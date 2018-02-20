package com.microsoft.adaptivecards.renderer.readonly;

import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.ContainerStyle;
import com.microsoft.adaptivecards.renderer.BaseCardElementRenderer;
import com.microsoft.adaptivecards.renderer.Util;
import com.microsoft.adaptivecards.renderer.actionhandler.ICardActionHandler;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.objectmodel.BaseCardElement;
import com.microsoft.adaptivecards.objectmodel.CardElementType;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.Image;
import com.microsoft.adaptivecards.objectmodel.ImageSet;
import com.microsoft.adaptivecards.objectmodel.ImageSize;
import com.microsoft.adaptivecards.objectmodel.ImageVector;
import com.microsoft.adaptivecards.renderer.registration.CardRendererRegistration;
import com.microsoft.adaptivecards.renderer.layout.HorizontalFlowLayout;

import java.util.Vector;

public class ImageSetRenderer extends BaseCardElementRenderer
{
    private ImageSetRenderer()
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
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            Vector<IInputHandler> inputActionHandlerList,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            ContainerStyle containerStyle)
    {
        ImageSet imageSet = null;
        if (baseCardElement instanceof ImageSet)
        {
            imageSet = (ImageSet) baseCardElement;
        }
        else if ((imageSet = ImageSet.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to ImageSet object model.");
        }

        setSpacingAndSeparator(context, viewGroup, imageSet.GetSpacing(), imageSet.GetSeparator(), hostConfig, true);

        //TODO: Remove this cast. If someone overrides the image renderer in the registration, this will fail since the type may not extend from ImageRenderer.
        ImageRenderer imageRenderer = (ImageRenderer) CardRendererRegistration.getInstance().getRenderer(CardElementType.Image.toString());
        if (imageRenderer == null)
        {
            throw new IllegalArgumentException("No renderer registered for: " + CardElementType.Image.toString());
        }

        HorizontalFlowLayout horizFlowLayout = new HorizontalFlowLayout(context);
        horizFlowLayout.setTag(imageSet);
        ImageSize imageSize = imageSet.GetImageSize();
        ImageVector imageVector = imageSet.GetImages();
        long imageVectorSize = imageVector.size();
        for (int i = 0; i < imageVectorSize; i++)
        {
            Image image = imageVector.get(i);

            // TODO: temporary - this will be handled in the object model
            image.SetImageSize(imageSize);
            View imageView = imageRenderer.render(context, fragmentManager, horizFlowLayout, image, inputActionHandlerList, cardActionHandler, hostConfig, containerStyle, true);
            ((ImageView) imageView).setMaxHeight(Util.dpToPixels(context, hostConfig.getImageSet().getMaxImageHeight()));
        }

        viewGroup.addView(horizFlowLayout, new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));

        return horizFlowLayout;
    }

    private static ImageSetRenderer s_instance = null;
}