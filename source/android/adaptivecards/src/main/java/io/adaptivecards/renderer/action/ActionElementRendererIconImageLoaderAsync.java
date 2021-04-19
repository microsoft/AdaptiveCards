// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.action;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.view.View;
import android.widget.Button;

import java.lang.ref.WeakReference;

import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;

class ActionElementRendererIconImageLoaderAsync extends InnerImageLoaderAsync
{
    private final IconPlacement m_iconPlacement;
    private final long m_iconSize;
    private final long m_padding;
    private final WeakReference<Context> m_context;

    protected ActionElementRendererIconImageLoaderAsync(RenderedAdaptiveCard renderedCard, View containerView, String imageBaseUrl, IconPlacement iconPlacement, long iconSize, long padding, Context context)
    {
        super(renderedCard, containerView, imageBaseUrl, containerView.getResources().getDisplayMetrics().widthPixels);
        m_iconPlacement = iconPlacement;
        m_iconSize = iconSize;
        m_padding = padding;
        m_context = new WeakReference<>(context);
    }

    @Override
    public Bitmap styleBitmap(Bitmap bitmap)
    {
        Button button = (Button) super.m_view;
        float imageHeight;

        if (m_iconPlacement == IconPlacement.AboveTitle)
        {
            // If icon is above title, iconSize should be used as the height of the image
            imageHeight = Util.dpToPixels(m_context.get(), m_iconSize);
        }
        else
        {
            // Otherwise, the height of the image should be the height of the action's text
            imageHeight = button.getTextSize();
        }

        return Util.scaleBitmapToHeight(imageHeight, bitmap);
    }

    @Override
    protected void renderBitmap(Bitmap bitmap) {
        Button button = (Button) super.m_view;
        Drawable drawableIcon = new BitmapDrawable(null, bitmap);

        // Preserve any existing icons that may have been added by the host
        // Per Android docs, this array's order is: start, top, end, bottom
        Drawable[] drawables = button.getCompoundDrawablesRelative();

        if (m_iconPlacement == IconPlacement.AboveTitle)
        {
            drawables[1] = drawableIcon;
        }
        else
        {
            drawables[0] = drawableIcon;
            button.setCompoundDrawablePadding(Util.dpToPixels(m_context.get(), (int) m_padding));
        }

        button.setCompoundDrawablesRelativeWithIntrinsicBounds(drawables[0], drawables[1], drawables[2], drawables[3]);
    }
}
