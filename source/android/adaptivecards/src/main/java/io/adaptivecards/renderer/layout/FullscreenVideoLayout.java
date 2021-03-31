// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.layout;


/**
 * Copyright (C) 2016 Toshiro Sugii
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * Portions Copyright (c) Microsoft Corporation
 */

import android.content.Context;
import android.media.MediaPlayer;
import android.support.annotation.NonNull;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.MediaController;

public class FullscreenVideoLayout extends FullscreenVideoView implements MediaPlayer.OnPreparedListener, View.OnTouchListener
{
    public FullscreenVideoLayout(Context context)
    {
        super(context);
    }

    public FullscreenVideoLayout(Context context, AttributeSet attrs)
    {
        super(context, attrs);
    }

    public FullscreenVideoLayout(Context context, AttributeSet attrs, int defStyleAttr)
    {
        super(context, attrs, defStyleAttr);
    }

    @Override
    protected void release()
    {
        super.release();
        super.setOnTouchListener(null);
    }

    @Override
    protected void onVisibilityChanged(@NonNull View changedView, int visibility) {
        super.onVisibilityChanged(changedView, visibility);
        if (visibility == VISIBLE)
        {
            updateControls();
        }
        else
        {
            hideControls();
        }
    }

    @Override
    protected void initObjects()
    {
        super.initObjects();

        // We need to add it to show/hide the controls
        super.setOnTouchListener(this);

        if (m_mediaControlView == null)
        {
            // TODO: Switch to androidx.media2.widget.MediaControlView after AndroidX upgrade
            m_mediaControlView = new MediaController(m_context);
            FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            layoutParams.gravity = Gravity.BOTTOM;
            m_mediaControlView.setLayoutParams(layoutParams);
            m_mediaControlView.setMediaPlayer(this);
            m_mediaControlView.setAnchorView(this);
        }
    }

    @Override
    protected void releaseObjects()
    {
        super.releaseObjects();
        if (m_mediaControlView != null)
        {
            m_mediaControlView.hide();
            m_mediaControlView.setAnchorView(null);
        }
    }

    @Override
    public void setOnTouchListener(View.OnTouchListener l)
    {
        m_touchListener = l;
    }

    @Override
    public void onCompletion(MediaPlayer mp)
    {
        super.onCompletion(mp);
        updateControls();
    }

    @Override
    public boolean onError(MediaPlayer mp, int what, int extra)
    {
        boolean result = super.onError(mp, what, extra);
        updateControls();
        return result;
    }

    @Override
    protected void onDetachedFromWindow()
    {
        super.onDetachedFromWindow();
        m_mediaControlView.hide();
    }

    @Override
    public void start() throws IllegalStateException {
        if (!isPlaying())
        {
            super.start();
        }
        updateControls();
    }

    @Override
    public void pause() throws IllegalStateException {
        if (isPlaying())
        {
            super.pause();
        }
        updateControls();
    }

    @Override
    public void reset()
    {
        super.reset();
    }

    @Override
    public void stop() throws IllegalStateException
    {
        super.stop();
        updateControls();
    }

    protected void updateControls()
    {
        if (m_currentState == State.STARTED)
        {
            showControls();
        }
        else
        {
            showControlsForever();
        }
    }

    public void hideControls()
    {
        m_mediaControlView.hide();
    }

    public void showControls()
    {
        m_mediaControlView.show();
    }

    private void showControlsForever()
    {
        m_mediaControlView.show(0);
    }

    @Override
    public boolean onTouch(View v, MotionEvent event)
    {
        if (event.getAction() == MotionEvent.ACTION_DOWN)
        {
            if (m_mediaControlView != null)
            {
                if(m_mediaControlView.isShowing())
                {
                    hideControls();
                }
                else
                {
                    showControls();
                }
            }
        }

        if (m_touchListener != null)
        {
            return m_touchListener.onTouch(FullscreenVideoLayout.this, event);
        }

        return false;
    }


    protected OnTouchListener m_touchListener;
    private MediaController m_mediaControlView;

}
