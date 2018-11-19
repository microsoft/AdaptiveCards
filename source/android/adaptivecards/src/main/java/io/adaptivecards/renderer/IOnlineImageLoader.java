package io.adaptivecards.renderer;

import android.graphics.Bitmap;

import java.io.IOException;
import java.net.URISyntaxException;

import io.adaptivecards.renderer.http.HttpRequestResult;

public interface IOnlineImageLoader
{
    HttpRequestResult<Bitmap> loadOnlineImage(String url, GenericImageLoaderAsync loader) throws IOException, URISyntaxException;
}
