// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.graphics.Bitmap;

import java.io.IOException;
import java.net.URISyntaxException;

import io.adaptivecards.renderer.GenericImageLoaderAsync;
import io.adaptivecards.renderer.http.HttpRequestResult;

public interface IResourceResolver
{
    HttpRequestResult<Bitmap> resolveImageResource(String url, GenericImageLoaderAsync loader) throws IOException, URISyntaxException;
    HttpRequestResult<Bitmap> resolveImageResource(String url, GenericImageLoaderAsync loader, int maxWidth) throws IOException, URISyntaxException;
}
