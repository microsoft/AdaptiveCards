// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer;

import android.media.MediaDataSource;
import android.os.Build;
import androidx.annotation.RequiresApi;

import io.adaptivecards.objectmodel.MediaSourceVector;

@RequiresApi(api = Build.VERSION_CODES.M)
public interface IOnlineMediaLoader
{
    MediaDataSource loadOnlineMedia(MediaSourceVector mediaSources, IMediaDataSourceOnPreparedListener mediaDataSourceOnPreparedListener);
}
