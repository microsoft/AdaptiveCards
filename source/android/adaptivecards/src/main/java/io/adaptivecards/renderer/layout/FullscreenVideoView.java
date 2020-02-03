// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.layout;

/**
 * Copyright (C) 2016 Toshiro Sugii
 * <p>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import android.annotation.SuppressLint;
import android.content.Context;
import android.graphics.Color;
import android.graphics.SurfaceTexture;
import android.media.AudioManager;
import android.media.MediaDataSource;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnBufferingUpdateListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.OnSeekCompleteListener;
import android.net.Uri;
import android.media.MediaPlayer.OnVideoSizeChangedListener;
import android.os.Handler;
import android.os.Looper;
import android.os.Parcelable;
import android.util.AttributeSet;
import android.view.Surface;
import android.view.TextureView;
import android.view.View;

import android.widget.FrameLayout;
import java.io.IOException;

import io.adaptivecards.renderer.IMediaDataSourceOnPreparedListener;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

/**
 * Acts like a android.widget.VideoView with fullscreen functionality
 *
 * @author rtoshiro
 * @version 2015.0527
 * @since 1.0
 */

/**
 * Portions Copyright (c) Microsoft Corporation
 */

@SuppressLint("NewApi")
public class FullscreenVideoView extends FrameLayout implements OnPreparedListener, OnErrorListener, OnSeekCompleteListener, OnCompletionListener, OnInfoListener, OnVideoSizeChangedListener, OnBufferingUpdateListener, TextureView.SurfaceTextureListener
{
    protected Context m_context;

    protected MediaPlayer m_mediaPlayer;
    protected boolean m_videoIsReady, m_surfaceIsReady;
    protected boolean m_isAudioOnly;
    protected State m_currentState;
    protected State m_lastState; // Tells onSeekCompletion what to do

    protected boolean m_shouldAutoplay;
    protected int m_initialConfigOrientation;
    protected int m_initialMovieWidth, m_initialMovieHeight;
    protected String m_videoPath;
    protected Uri m_videoUri;

    protected OnBufferingUpdateListener m_bufferingUpdateListener;
    protected OnCompletionListener m_completionListener;
    protected OnErrorListener m_errorListener;
    protected OnInfoListener m_infoListener;
    protected OnPreparedListener m_preparedListener;
    protected OnSeekCompleteListener m_seekCompleteListener;
    protected OnVideoSizeChangedListener m_videoSizeChangedListener;

    protected TextureView m_textureView;

    /**
     * States of MediaPlayer
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#StateDiagram">MediaPlayer</a>
     */
    public enum State {
        IDLE,
        INITIALIZED,
        PREPARED,
        PREPARING,
        STARTED,
        STOPPED,
        PAUSED,
        PLAYBACKCOMPLETED,
        ERROR,
        END
    }

    public FullscreenVideoView(Context context)
    {
        super(context);
        m_context = context;
        init();
    }

    public FullscreenVideoView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        m_context = context;
        init();
    }

    public FullscreenVideoView(Context context, AttributeSet attrs, int defStyleAttr)
    {
        super(context, attrs, defStyleAttr);
        m_context = context;
        init();
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh)
    {
        super.onSizeChanged(w, h, oldw, oldh);
        resize();
    }

    @Override
    public Parcelable onSaveInstanceState()
    {
        Parcelable p = super.onSaveInstanceState();
        return p;
    }

    @Override
    public void onRestoreInstanceState(Parcelable state)
    {
        super.onRestoreInstanceState(state);
    }

    @Override
    protected void onDetachedFromWindow()
    {
        super.onDetachedFromWindow();
    }

    @Override
    protected void onAttachedToWindow()
    {
        super.onAttachedToWindow();
        // If Object still exists, reload the video
        if (m_mediaPlayer == null && m_currentState == State.END)
        {
            initObjects();
            try
            {
                if (m_videoPath != null)
                {
                    setVideoPath(m_videoPath, m_isAudioOnly);
                }
                else if (m_videoUri != null)
                {
                    setVideoURI(m_videoUri, m_isAudioOnly);
                }
            }
            catch (IOException e)
            {
                e.printStackTrace();
            }
        }
    }

    // TextureView
    @Override
    public void onSurfaceTextureAvailable(SurfaceTexture surfaceTexture, int width, int height)
    {
        Surface surface = new Surface(surfaceTexture);
        if (m_mediaPlayer != null)
        {
            m_mediaPlayer.setSurface(surface);

            // If is not prepared yet - tryToPrepare()
            if (!m_surfaceIsReady)
            {
                m_surfaceIsReady = true;
                if (m_currentState == State.INITIALIZED || m_currentState == State.PREPARING)
                {
                    tryToPrepare();
                }
            }
        }
    }

    @Override
    public void onSurfaceTextureSizeChanged(SurfaceTexture surface, int width, int height)
    {
        resize();
    }

    @Override
    public boolean onSurfaceTextureDestroyed(SurfaceTexture surface)
    {
        if (m_mediaPlayer != null && m_mediaPlayer.isPlaying())
        {
            m_mediaPlayer.pause();
        }
        m_surfaceIsReady = false;
        return true;
    }

    @Override
    public void onSurfaceTextureUpdated(SurfaceTexture surface)
    {
    }

    @Override
    synchronized public void onPrepared(MediaPlayer mp)
    {
        m_videoIsReady = true;
        tryToPrepare();
    }

    /**
     * Restore the last State before seekTo()
     *
     * @param mp the MediaPlayer that issued the seek operation
     */
    @Override
    public void onSeekComplete(MediaPlayer mp) {
        if (m_lastState != null)
        {
            switch (m_lastState)
            {
                case STARTED:
                {
                    start();
                    break;
                }
                case PLAYBACKCOMPLETED:
                {
                    m_currentState = State.PLAYBACKCOMPLETED;
                    break;
                }
                case PREPARED:
                {
                    m_currentState = State.PREPARED;
                    break;
                }
            }
        }

        if (m_seekCompleteListener != null)
        {
            m_seekCompleteListener.onSeekComplete(mp);
        }
    }

    @Override
    public void onCompletion(MediaPlayer mp)
    {
        if (m_mediaPlayer != null)
        {
            if (m_currentState != State.ERROR)
            {
                if (!m_mediaPlayer.isLooping())
                {
                    m_currentState = State.PLAYBACKCOMPLETED;
                }
                else
                {
                    start();
                }
            }
        }

        if (m_completionListener != null)
        {
            m_completionListener.onCompletion(mp);
        }
    }

    @Override
    public boolean onInfo(MediaPlayer mediaPlayer, int what, int extra)
    {
        if (m_infoListener != null)
        {
            return m_infoListener.onInfo(mediaPlayer, what, extra);
        }
        return false;
    }

    @Override
    public boolean onError(MediaPlayer mp, int what, int extra)
    {
        m_currentState = State.ERROR;
        if (m_errorListener != null)
        {
            return m_errorListener.onError(mp, what, extra);
        }
        return false;
    }

    @Override
    public void onVideoSizeChanged(MediaPlayer mp, int width, int height)
    {
        if (m_initialMovieWidth == -1 && m_initialMovieHeight == -1 && width != 0 && height != 0)
        {
            m_initialMovieWidth = width;
            m_initialMovieHeight = height;
            resize();
        }

        if (m_videoSizeChangedListener != null)
        {
            m_videoSizeChangedListener.onVideoSizeChanged(mp, width, height);
        }
    }

    @Override
    public void onBufferingUpdate(MediaPlayer mp, int percent)
    {
        if (m_bufferingUpdateListener != null)
        {
            m_bufferingUpdateListener.onBufferingUpdate(mp, percent);
        }
    }

    // Initializes the default configuration
    protected void init()
    {
        if (isInEditMode())
        {
            return;
        }

        m_mediaPlayer = null;
        m_shouldAutoplay = false;
        m_initialConfigOrientation = -1;
        m_videoIsReady = false;
        m_surfaceIsReady = false;
        m_initialMovieHeight = -1;
        m_initialMovieWidth = -1;
        setBackgroundColor(Color.BLACK);

        initObjects();
    }

    // Releases and ends the current Object
    protected void release() {
        releaseObjects();
        if (m_mediaPlayer != null)
        {
            m_mediaPlayer.setOnBufferingUpdateListener(null);
            m_mediaPlayer.setOnPreparedListener(null);
            m_mediaPlayer.setOnErrorListener(null);
            m_mediaPlayer.setOnSeekCompleteListener(null);
            m_mediaPlayer.setOnCompletionListener(null);
            m_mediaPlayer.setOnInfoListener(null);
            m_mediaPlayer.setOnVideoSizeChangedListener(null);
            m_mediaPlayer.release();
            m_mediaPlayer = null;
        }
        m_currentState = State.END;
    }

    /**
     * Initializes all objects FullscreenVideoView depends on
     * It does not interfere with configuration properties
     * because it is supposed to be called when this Object
     * still exists
     */
    protected void initObjects()
    {
        if (m_mediaPlayer == null)
        {
            m_mediaPlayer = new MediaPlayer();
            m_mediaPlayer.setOnInfoListener(this);
            m_mediaPlayer.setOnErrorListener(this);
            m_mediaPlayer.setOnPreparedListener(this);
            m_mediaPlayer.setOnCompletionListener(this);
            m_mediaPlayer.setOnSeekCompleteListener(this);
            m_mediaPlayer.setOnBufferingUpdateListener(this);
            m_mediaPlayer.setOnVideoSizeChangedListener(this);
            m_mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
        }

        if (m_textureView == null)
        {
            m_textureView = new TextureView(m_context);
            m_textureView.setSurfaceTextureListener(this);
        }

        m_textureView.setLayoutParams(new FrameLayout.LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.MATCH_PARENT));
        addView(m_textureView);

        m_currentState = State.IDLE;
    }

    /**
     * Releases all objects FullscreenVideoView depends on
     * It does not interfere with configuration properties
     * because it is supposed to be called when this Object
     * still exists
     */
    protected void releaseObjects()
    {
        if (m_mediaPlayer != null)
        {
            m_mediaPlayer.setSurface(null);
            m_mediaPlayer.reset();
        }

        m_videoIsReady = false;
        m_surfaceIsReady = false;
        m_initialMovieHeight = -1;
        m_initialMovieWidth = -1;

        if (m_textureView != null)
        {
            m_textureView.setSurfaceTextureListener(null);
            removeView(m_textureView);
            m_textureView = null;
        }
    }

    // Calls prepare() method of MediaPlayer
    public void prepare() throws IllegalStateException
    {
        m_currentState = State.PREPARING;
        m_mediaPlayer.prepareAsync();
    }

    /**
     * Try to call state PREPARED
     * Only if SurfaceView is already created and MediaPlayer is prepared
     * Video is loaded and is ok to play.
     */
    protected void tryToPrepare()
    {
        if (m_surfaceIsReady && m_videoIsReady)
        {
            if (m_mediaPlayer != null && m_mediaPlayer.getVideoWidth() != 0 && m_mediaPlayer.getVideoHeight() != 0)
            {
                m_initialMovieWidth = m_mediaPlayer.getVideoWidth();
                m_initialMovieHeight = m_mediaPlayer.getVideoHeight();
            }

            resize();
            m_currentState = State.PREPARED;

            if (m_shouldAutoplay)
            {
                start();
            }

            if (m_preparedListener != null)
            {
                m_preparedListener.onPrepared(m_mediaPlayer);
            }
        }
    }

    /**
     * Get the current {@link FullscreenVideoView.State}.
     *
     * @return Current {@link FullscreenVideoView.State}
     */
    synchronized public State getCurrentState()
    {
        return m_currentState;
    }

    public void resize()
    {
        if ( ((m_initialMovieHeight == -1 || m_initialMovieWidth == -1) && !m_isAudioOnly) || m_textureView == null)
        {
            return;
        }

        Handler handler = new Handler(Looper.getMainLooper());
        handler.post(new Runnable()
        {
            @Override
            public void run()
            {
                View currentParent = (View) getParent();
                if (currentParent != null)
                {
                    int screenWidth = currentParent.getWidth();
                    int newHeight = 200;
                    if(!m_isAudioOnly)
                    {
                        newHeight = (int) ((float) (screenWidth * m_initialMovieHeight) / (float) m_initialMovieWidth);
                    }
                    else
                    {
                        newHeight = 200;
                    }

                    if (m_textureView != null) {
                        FrameLayout.LayoutParams layoutParams = (FrameLayout.LayoutParams) m_textureView.getLayoutParams();
                        layoutParams.width = screenWidth;
                        layoutParams.height = newHeight;
                        m_textureView.setLayoutParams(layoutParams);
                    }
                }
            }
        });
    }

    /**
     * Tells if application should autoplay videos as soon as it is prepared
     *
     * @return true if application are going to play videos as soon as it is prepared
     */
    public boolean isShouldAutoplay()
    {
        return m_shouldAutoplay;
    }

    /**
     * Tells application that it should begin playing as soon as buffering
     * is ok
     *
     * @param shouldAutoplay If true, call start() method when getCurrentState() == PREPARED. Default is false.
     */
    public void setShouldAutoplay(boolean shouldAutoplay)
    {
        m_shouldAutoplay = shouldAutoplay;
    }

    /**
     * MediaPlayer method (getCurrentPosition)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#getCurrentPosition%28%29">getCurrentPosition</a>
     */
    public int getCurrentPosition()
    {
        if (m_mediaPlayer != null)
        {
            return m_mediaPlayer.getCurrentPosition();
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (getDuration)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#getDuration%28%29">getDuration</a>
     */
    public int getDuration()
    {
        if (m_mediaPlayer != null)
        {
            return m_mediaPlayer.getDuration();
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (getVideoHeight)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#getVideoHeight%28%29">getVideoHeight</a>
     */
    public int getVideoHeight()
    {
        if (m_mediaPlayer != null)
        {
            return m_mediaPlayer.getVideoHeight();
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (getVideoWidth)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#getVideoWidth%28%29">getVideoWidth</a>
     */
    public int getVideoWidth()
    {
        if (m_mediaPlayer != null)
        {
            return m_mediaPlayer.getVideoWidth();
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (isLooping)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#isLooping%28%29">isLooping</a>
     */
    public boolean isLooping()
    {
        if (m_mediaPlayer != null)
        {
            return m_mediaPlayer.isLooping();
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (isPlaying)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#isPlaying%28%29">isPlaying</a>
     */
    public boolean isPlaying() throws IllegalStateException
    {
        if (m_mediaPlayer != null)
        {
            return m_mediaPlayer.isPlaying();
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (pause)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#pause%28%29">pause</a>
     */
    public void pause() throws IllegalStateException
    {
        if (m_mediaPlayer != null)
        {
            m_currentState = State.PAUSED;
            m_mediaPlayer.pause();
        } else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * Due to a lack of access of SurfaceView, it rebuilds mediaPlayer and all
     * views to update SurfaceView canvas
     */
    public void reset()
    {
        releaseObjects();
        initObjects();
    }

    /**
     * MediaPlayer method (start)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#start%28%29">start</a>
     */
    public void start() throws IllegalStateException
    {
        if (m_mediaPlayer != null)
        {
            m_currentState = State.STARTED;
            m_mediaPlayer.setOnCompletionListener(this);
            m_mediaPlayer.start();
        } else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (stop)
     *
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#stop%28%29">stop</a>
     */
    public void stop() throws IllegalStateException
    {
        if (m_mediaPlayer != null)
        {
            m_currentState = State.STOPPED;
            m_mediaPlayer.stop();
        } else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * MediaPlayer method (seekTo)
     * It calls pause() method before calling MediaPlayer.seekTo()
     *
     * @param msec the offset in milliseconds from the start to seek to
     * @throws IllegalStateException if the internal player engine has not been initialized
     * @see <a href="http://developer.android.com/reference/android/media/MediaPlayer.html#seekTo%28%29">seekTo</a>
     */
    public void seekTo(int msec) throws IllegalStateException
    {
        if (m_mediaPlayer != null)
        {
            // No live streaming
            if (m_mediaPlayer.getDuration() > -1 && msec <= m_mediaPlayer.getDuration())
            {
                m_lastState = m_currentState;
                pause();
                m_mediaPlayer.seekTo(msec);
            }
        } else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnCompletionListener(OnCompletionListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_completionListener = l;
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnErrorListener(OnErrorListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_errorListener = l;
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnBufferingUpdateListener(OnBufferingUpdateListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_bufferingUpdateListener = l;
            m_mediaPlayer.setOnBufferingUpdateListener(this);
        } else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnInfoListener(OnInfoListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_infoListener = l;
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnSeekCompleteListener(OnSeekCompleteListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_seekCompleteListener = l;
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnVideoSizeChangedListener(OnVideoSizeChangedListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_videoSizeChangedListener = l;
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setOnPreparedListener(OnPreparedListener l)
    {
        if (m_mediaPlayer != null)
        {
            m_preparedListener = l;
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setLooping(boolean looping)
    {
        if (m_mediaPlayer != null)
        {
            m_mediaPlayer.setLooping(looping);
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    public void setVolume(float leftVolume, float rightVolume)
    {
        if (m_mediaPlayer != null)
        {
            m_mediaPlayer.setVolume(leftVolume, rightVolume);
        }
        else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * VideoView method (setVideoPath)
     */
    public void setVideoPath(String path, boolean isAudio) throws IOException, IllegalStateException, SecurityException, IllegalArgumentException, RuntimeException
    {
        if (m_mediaPlayer != null)
        {
            if (m_currentState != State.IDLE)
            {
                throw new IllegalStateException("FullscreenVideoView Invalid State: " + m_currentState);
            }

            m_videoPath = path;
            m_videoUri = null;
            m_isAudioOnly = isAudio;
            m_mediaPlayer.setDataSource(path);

            m_currentState = State.INITIALIZED;
            prepare();
        } else throw new RuntimeException("Media Player is not initialized");
    }

    /**
     * VideoView method (setVideoURI)
     */
    public void setVideoURI(Uri uri, boolean isAudio) throws IOException, IllegalStateException, SecurityException, IllegalArgumentException, RuntimeException
    {
        if (m_mediaPlayer != null)
        {
            if (m_currentState != State.IDLE)
            {
                throw new IllegalStateException("FullscreenVideoView Invalid State: " + m_currentState);
            }

            m_videoUri = uri;
            m_videoPath = null;
            m_isAudioOnly = isAudio;
            m_mediaPlayer.setDataSource(m_context, uri);

            m_currentState = State.INITIALIZED;
            prepare();
        } else throw new RuntimeException("Media Player is not initialized");
    }

    public void setDataSource(MediaDataSource dataSource, boolean isAudio)
    {
        if(m_mediaPlayer != null)
        {
            if (m_currentState != State.IDLE)
            {
                throw new IllegalStateException("FullscreenVideoView Invalid State: " + m_currentState);
            }

            m_videoUri = null;
            m_videoPath = null;
            m_isAudioOnly = isAudio;

            m_mediaPlayer.setDataSource(dataSource);
            m_currentState = State.INITIALIZED;
        } else throw new RuntimeException("Media Player is not initialized");
    }

}
