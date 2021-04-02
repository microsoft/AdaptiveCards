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
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.MediaController;

public class FullscreenVideoLayout extends FullscreenVideoView implements MediaPlayer.OnPreparedListener, View.OnClickListener
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
    protected void initObjects()
    {
        super.initObjects();

        // We need to add it to show/hide the controls
        super.setOnClickListener(this);

        if (m_mediaControlView == null)
        {
            // TODO: Switch to androidx.media2.widget.MediaControlView after AndroidX upgrade
            // Existing "floating" MediaController doesn't scroll with anchorView, and creates a keyboard focus trap.
            // So, we override to add the view as a child of the given anchorView instead.
            m_mediaControlView = new MediaController(m_context)
            {
                private View m_anchorView;
                private ViewGroup.LayoutParams m_layoutParams;

                @Override
                public void setAnchorView(View view) {
                    m_anchorView = view;
                    m_layoutParams = view.getLayoutParams();
                    super.setAnchorView(view);

                    if (view instanceof ViewGroup)
                    {
                        ((ViewGroup) getParent()).removeView(this);
                        setLayoutDirection(LAYOUT_DIRECTION_LTR);
                        ((ViewGroup) view).addView(this);
                    }
                }

                @Override
                public void show() {
                    super.show();
                    if(isShowing() && getVisibility() == INVISIBLE)
                    {
                        setVisibility(VISIBLE);
                        requestFocus();
                        requestFocusFromTouch();
                    }
                }

                @Override
                public void hide() {
                    super.hide();
                    if(!isShowing() && getVisibility() == VISIBLE)
                    {
                        setVisibility(INVISIBLE);
                        m_anchorView.requestFocus();
                        m_anchorView.requestFocusFromTouch();
                    }
                }
            };
            m_mediaControlView.setMediaPlayer(this);
            m_mediaControlView.setLayoutParams(new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT, Gravity.BOTTOM));
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
    public void setOnClickListener(View.OnClickListener l)
    {
        m_clickListener = l;
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
        // return focus to player after hiding control view
        requestFocus();
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
    public void onClick(View v)
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

        if (m_clickListener != null)
        {
            m_clickListener.onClick(v);
        }
    }

    private void togglePlaying()
    {
        if (m_currentState == State.STARTED)
        {
            pause();
        }
        else
        {
            start();
        }
    }

    protected OnClickListener m_clickListener;
    private MediaController m_mediaControlView;

}
