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
import android.graphics.Color;
import android.graphics.drawable.Drawable;
import android.media.MediaPlayer;
import android.os.Handler;
import android.util.AttributeSet;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.SeekBar;
import android.widget.TextView;

import java.util.Locale;

public class FullscreenVideoLayout extends FullscreenVideoView implements View.OnClickListener, SeekBar.OnSeekBarChangeListener, MediaPlayer.OnPreparedListener, View.OnTouchListener
{
    // Handler and Runnable to keep tracking on elapsed time
    protected static Handler TIME_THREAD = null;
    protected Runnable updateTimeRunnable = new Runnable()
    {
        public void run()
        {
            updateCounter();
            autoHideControls();
            TIME_THREAD.postDelayed(this, 200);
        }
    };

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

    private void arrangeControlBar()
    {
        LinearLayout controlsAndSeekBarLayout = new LinearLayout(m_context);
        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        params.gravity = Gravity.BOTTOM;
        controlsAndSeekBarLayout.setLayoutParams(params);
        controlsAndSeekBarLayout.setOrientation(LinearLayout.VERTICAL);
        m_videoControlsView.addView(controlsAndSeekBarLayout);

        m_seekBar = new SeekBar(m_context);
        m_seekBar.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        controlsAndSeekBarLayout.addView(m_seekBar);

        LinearLayout controlsBarLayout = new LinearLayout(m_context);
        controlsBarLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT));
        controlsBarLayout.setOrientation(LinearLayout.HORIZONTAL);
        controlsAndSeekBarLayout.addView(controlsBarLayout);

        LinearLayout elapsedTimeViewLayout = new LinearLayout(m_context);
        elapsedTimeViewLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        elapsedTimeViewLayout.setOrientation(LinearLayout.HORIZONTAL);
        m_elapsedTimeView = new TextView(m_context);
        LinearLayout.LayoutParams elapsedTimeViewLayoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        elapsedTimeViewLayoutParams.gravity = Gravity.CENTER_VERTICAL;
        m_elapsedTimeView.setLayoutParams(elapsedTimeViewLayoutParams);
        m_elapsedTimeView.setTextColor(Color.WHITE);
        elapsedTimeViewLayout.addView(m_elapsedTimeView);
        controlsBarLayout.addView(elapsedTimeViewLayout);

        m_playButton = new ImageButton(m_context);
        controlsBarLayout.addView(m_playButton);

        LinearLayout totalTimeViewLayout = new LinearLayout(m_context);
        totalTimeViewLayout.setLayoutParams(new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT, 1));
        m_totalTimeView = new TextView(m_context);
        LinearLayout.LayoutParams totalTimeViewLayoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        totalTimeViewLayoutParams.gravity = Gravity.CENTER_VERTICAL;
        m_totalTimeView.setLayoutParams(totalTimeViewLayoutParams);
        m_totalTimeView.setTextAlignment(TEXT_ALIGNMENT_TEXT_END);
        m_totalTimeView.setTextColor(Color.WHITE);
        totalTimeViewLayout.addView(m_totalTimeView);
        controlsBarLayout.addView(totalTimeViewLayout);
    }

    @Override
    protected void initObjects()
    {
        super.initObjects();

        // We need to add it to show/hide the controls
        super.setOnTouchListener(this);

        if (m_videoControlsView == null)
        {
            m_videoControlsView = new FrameLayout(m_context);
            FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
            layoutParams.gravity = Gravity.BOTTOM;
            m_videoControlsView.setLayoutParams(layoutParams);

            // Apply black color so elapsed time and total time are visible
            m_videoControlsView.setBackgroundColor(0x44000000);

            addView(m_videoControlsView);
        }

        if (m_videoControlsView != null)
        {
            arrangeControlBar();
        }

        if (m_playButton != null)
        {
            m_playButton.setOnClickListener(this);
        }

        if (m_seekBar != null)
        {
            m_seekBar.setOnSeekBarChangeListener(this);
        }

        // Start controls invisible. Make it visible when it is prepared
        if (m_videoControlsView != null)
        {
            m_videoControlsView.setVisibility(View.INVISIBLE);
        }
    }

    @Override
    protected void releaseObjects()
    {
        super.releaseObjects();
        if (m_videoControlsView != null)
        {
            removeView(m_videoControlsView);
        }
    }

    protected void startCounter()
    {
        if(TIME_THREAD == null)
        {
            TIME_THREAD = new Handler();
        }
        TIME_THREAD.postDelayed(updateTimeRunnable, 200);
    }

    protected void stopCounter()
    {
        TIME_THREAD.removeCallbacks(updateTimeRunnable);
    }

    protected void updateCounter()
    {
        if (m_elapsedTimeView == null)
        {
            return;
        }

        int elapsed = getCurrentPosition();
        // getCurrentPosition is a little bit buggy :(
        if (elapsed > 0 && elapsed < getDuration())
        {
            m_seekBar.setProgress(elapsed);

            elapsed = Math.round(elapsed / 1000.f);
            long s = elapsed % 60;
            long m = (elapsed / 60) % 60;
            long h = (elapsed / (60 * 60)) % 24;

            if (h > 0)
            {
                m_elapsedTimeView.setText(String.format(Locale.US, "%d:%02d:%02d", h, m, s));
            }
            else
            {
                m_elapsedTimeView.setText(String.format(Locale.US, "%02d:%02d", m, s));
            }
        }
    }

    protected void autoHideControls()
    {
        if (m_elapsedTimeView == null)
        {
            return;
        }

        // We add one tick every 200 miliseconds and if the ticks have surpassed the 3 seconds ticks,
        // we hide the controls
        m_currentTicksForAutoHide++;

        if (m_currentTicksForAutoHide > c_ticksBeforeAutohide)
        {
            hideControls();
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
        stopCounter();
        updateControls();
        if (m_currentState != State.ERROR)
        {
            updateCounter();
        }
    }

    @Override
    public boolean onError(MediaPlayer mp, int what, int extra)
    {
        boolean result = super.onError(mp, what, extra);
        stopCounter();
        updateControls();
        return result;
    }

    @Override
    protected void onDetachedFromWindow()
    {
        super.onDetachedFromWindow();
        if (getCurrentState() == State.END)
        {
            stopCounter();
        }
    }

    @Override
    protected void tryToPrepare()
    {
        super.tryToPrepare();

        if (getCurrentState() == State.PREPARED || getCurrentState() == State.STARTED)
        {
            if (m_elapsedTimeView != null && m_totalTimeView != null)
            {
                int total = getDuration();
                if (total > 0)
                {
                    m_seekBar.setMax(total);
                    m_seekBar.setProgress(0);

                    total = total / 1000;
                    long s = total % 60;
                    long m = (total / 60) % 60;
                    long h = (total / (60 * 60)) % 24;
                    if (h > 0)
                    {
                        m_elapsedTimeView.setText("00:00:00");
                        m_totalTimeView.setText(String.format(Locale.US, "%d:%02d:%02d", h, m, s));
                    }
                    else
                    {
                        m_elapsedTimeView.setText("00:00");
                        m_totalTimeView.setText(String.format(Locale.US, "%02d:%02d", m, s));
                    }
                }
            }

            if (m_videoControlsView != null)
            {
                m_videoControlsView.setVisibility(View.VISIBLE);
            }
        }
    }

    @Override
    public void start() throws IllegalStateException {
        if (!isPlaying())
        {
            super.start();
            startCounter();
            updateControls();
        }
    }

    @Override
    public void pause() throws IllegalStateException {
        if (isPlaying())
        {
            stopCounter();
            super.pause();
            updateControls();
        }
    }

    @Override
    public void reset()
    {
        super.reset();
        stopCounter();
        updateControls();
    }

    @Override
    public void stop() throws IllegalStateException
    {
        super.stop();
        stopCounter();
        updateControls();
    }

    protected void updateControls()
    {
        if (m_playButton == null) return;

        Drawable icon;
        if (getCurrentState() == State.STARTED)
        {
            icon = m_context.getResources().getDrawable(android.R.drawable.ic_media_pause);
        }
        else
        {
            icon = m_context.getResources().getDrawable(android.R.drawable.ic_media_play);
        }

        m_playButton.setBackground(icon);
    }

    public void hideControls() {
        if (m_videoControlsView != null)
        {
            m_videoControlsView.setVisibility(View.INVISIBLE);
        }
    }

    public void showControls() {
        if (m_videoControlsView != null)
        {
            m_videoControlsView.setVisibility(View.VISIBLE);
            m_currentTicksForAutoHide = 0;
        }
    }

    @Override
    public boolean onTouch(View v, MotionEvent event)
    {
        if (event.getAction() == MotionEvent.ACTION_DOWN)
        {
            if (m_videoControlsView != null)
            {
                if (m_videoControlsView.getVisibility() == View.VISIBLE)
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

    // Onclick action Controls play button
    @Override
    public void onClick(View v) {
        if (isPlaying())
        {
            pause();
        }
        else
        {
            start();
        }
    }

    // SeekBar Listener
    @Override
    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser)
    {
    }

    @Override
    public void onStartTrackingTouch(SeekBar seekBar)
    {
        stopCounter();
    }

    @Override
    public void onStopTrackingTouch(SeekBar seekBar)
    {
        int progress = seekBar.getProgress();
        seekTo(progress);
    }

    protected OnTouchListener m_touchListener;
    protected ViewGroup m_videoControlsView;
    protected SeekBar m_seekBar;
    protected ImageButton m_playButton;
    protected TextView m_elapsedTimeView, m_totalTimeView;

    // We update the play counter every 200 miliseconds so we keep this count to hide the separator
    protected int m_currentTicksForAutoHide = 0;

    // The controls will autohide after 3 seconds
    private final int c_ticksBeforeAutohide = 15;
}
