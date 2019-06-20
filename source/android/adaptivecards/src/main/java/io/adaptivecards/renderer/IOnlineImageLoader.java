// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.graphics.Bitmap;

import java.io.IOException;
import java.net.URISyntaxException;

import io.adaptivecards.renderer.http.HttpRequestResult;

/**
 * @deprecated As of AdaptiveCards 1.2, replaced by {@link IResourceResolver}
 */
@Deprecated
public interface IOnlineImageLoader
{
    HttpRequestResult<Bitmap> loadOnlineImage(String url, GenericImageLoaderAsync loader) throws IOException, URISyntaxException;
}
