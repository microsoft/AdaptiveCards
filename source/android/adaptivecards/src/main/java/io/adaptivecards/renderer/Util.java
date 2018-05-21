package io.adaptivecards.renderer;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.DisplayMetrics;
import android.util.TypedValue;

import java.io.InputStream;

import io.adaptivecards.renderer.http.HttpRequestResult;

public final class Util {

    public static int dpToPixels(Context context, long dp)
    {
        DisplayMetrics metrics = context.getResources().getDisplayMetrics();
        int returnVal = (int) TypedValue.applyDimension(TypedValue.COMPLEX_UNIT_DIP, dp, metrics);
        return returnVal;
    }

    /** Helper function to load local image URL from res/drawable */
    public static HttpRequestResult<Bitmap> tryLocalImage(Context context, String url)
    {
        try
        {
            String authority = context.getPackageName();
            String type = "drawable";

            // Get image identifier
            Resources resources = context.getResources();
            int identifier = resources.getIdentifier(url, type, authority);
            if (identifier == 0) {
                throw new Exception("Image not found: " + url);
            }

            InputStream ins = resources.openRawResource(identifier);
            Bitmap bitmap = BitmapFactory.decodeStream(ins);
            if (bitmap == null)
            {
                throw new Exception("Failed to convert local content to bitmap: " + url);
            }

            return new HttpRequestResult<>(bitmap);
        }
        catch (Exception e)
        {
            return new HttpRequestResult<>(e);
        }
    }
}
