package io.adaptivecards.renderer;

import android.graphics.Bitmap;

import io.adaptivecards.renderer.http.HttpRequestResult;

public interface IDataUriImageLoader
{
    HttpRequestResult<Bitmap> loadDataUriImage(String url, GenericImageLoaderAsync loader) throws Exception;
}
