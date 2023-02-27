// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import static com.google.android.exoplayer2.Player.EVENT_PLAYBACK_STATE_CHANGED;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Build;
import androidx.fragment.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import com.google.android.exoplayer2.C;
import com.google.android.exoplayer2.ExoPlayer;
import com.google.android.exoplayer2.MediaItem;
import com.google.android.exoplayer2.Player;
import com.google.android.exoplayer2.extractor.DefaultExtractorsFactory;
import com.google.android.exoplayer2.source.DefaultMediaSourceFactory;
import com.google.android.exoplayer2.trackselection.DefaultTrackSelector;
import com.google.android.exoplayer2.ui.AspectRatioFrameLayout;
import com.google.android.exoplayer2.ui.StyledPlayerView;
import com.google.android.exoplayer2.upstream.DefaultHttpDataSource;
import com.google.android.exoplayer2.util.MimeTypes;
import com.google.common.collect.ImmutableList;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.CaptionSource;
import io.adaptivecards.objectmodel.CaptionSourceVector;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.objectmodel.MediaSource;
import io.adaptivecards.objectmodel.MediaSourceVector;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.ChannelAdaptor;
import io.adaptivecards.renderer.IMediaDataSourceOnPreparedListener;
import io.adaptivecards.renderer.IOnlineMediaLoader;
import io.adaptivecards.renderer.MediaLoaderAsync;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.layout.FullscreenVideoLayout;
import io.adaptivecards.renderer.layout.FullscreenVideoView;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class MediaRenderer extends BaseCardElementRenderer
{
    private MediaRenderer()
    {
    }

    public static MediaRenderer getInstance()
    {
        if(s_instance == null)
        {
            s_instance = new MediaRenderer();
        }
        return s_instance;
    }

    private class PosterOnClickListener implements View.OnClickListener
    {
        public PosterOnClickListener(ImageView poster, ImageView playButton, View mediaView, boolean allowedInlinePlayback, BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard, ICardActionHandler cardActionHandler, ViewGroup posterLayout)
        {
            m_poster = poster;
            m_playButton = playButton;
            m_mediaView = mediaView;
            m_allowedInlinePlayback = allowedInlinePlayback;

            m_cardMediaElement = mediaElement;
            m_renderedAdaptiveCard = renderedAdaptiveCard;
            m_cardActionHandler = cardActionHandler;
            m_posterLayout = posterLayout;
        }

        @Override
        public void onClick(View v)
        {
            if (!m_alreadyClicked)
            {
                if (m_allowedInlinePlayback)
                {
                    if (m_poster != null)
                    {
                        m_poster.setVisibility(View.GONE);
                    }
                    m_playButton.setVisibility(View.GONE);
                    m_mediaView.setVisibility(View.VISIBLE);
                }
                m_posterLayout.setClickable(false);

                if (m_mediaView instanceof StyledPlayerView)
                {
                    StyledPlayerView styledPlayerView = (StyledPlayerView) m_mediaView;
                    styledPlayerView.getPlayer().play();
                }

                m_cardActionHandler.onMediaPlay(m_cardMediaElement, m_renderedAdaptiveCard);

                m_alreadyClicked = true;
            }
        }

        private ViewGroup m_posterLayout;
        private ImageView m_poster;
        private ImageView m_playButton;
        private View m_mediaView;
        private boolean m_allowedInlinePlayback = true;
        private boolean m_alreadyClicked = false;

        private BaseCardElement m_cardMediaElement;
        private RenderedAdaptiveCard m_renderedAdaptiveCard;
        private ICardActionHandler m_cardActionHandler;
    }

    private class MediaOnCompletionListener implements MediaPlayer.OnCompletionListener
    {
        MediaOnCompletionListener(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard, ICardActionHandler cardActionHandler)
        {
            m_cardMediaElement = mediaElement;
            m_renderedAdaptiveCard = renderedAdaptiveCard;
            m_cardActionHandler = cardActionHandler;
        }

        @Override
        public void onCompletion(MediaPlayer mp)
        {
            m_cardActionHandler.onMediaStop(m_cardMediaElement, m_renderedAdaptiveCard);
        }

        private BaseCardElement m_cardMediaElement;
        private RenderedAdaptiveCard m_renderedAdaptiveCard;
        private ICardActionHandler m_cardActionHandler;
    }

    private boolean isSupportedMimeType(String mimetype)
    {
        final String supportedMimeTypes[] = {"video/mp4", "audio/mp4", "audio/aac", "audio/mpeg"};
        for(String supportedMimeType : supportedMimeTypes)
        {
            if(supportedMimeType.compareTo(mimetype) == 0)
            {
                return true;
            }
        }
        return false;
    }

    private ImageView renderPoster(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            Media media,
            ChannelAdaptor channelAdaptor,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        ImageView posterView = null;

        Image poster = new Image();
        if (!media.GetPoster().isEmpty())
        {
            poster.SetUrl(media.GetPoster());
        }
        else
        {
            poster.SetUrl(hostConfig.GetMedia().getDefaultPoster());
        }
        poster.SetAltText(media.GetAltText());

        if (!poster.GetUrl().isEmpty())
        {
            // Draw poster in posterLayout
            poster.SetImageSize(ImageSize.Auto);
            posterView = ImageRenderer.getInstance().render(renderedCard, context, fragmentManager, viewGroup, poster, channelAdaptor, hostConfig, renderArgs);

            RelativeLayout.LayoutParams posterLayoutParams = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
            posterLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
            ((TagContent) posterView.getTag()).GetStretchContainer().setLayoutParams(posterLayoutParams);
        }
        return posterView;
    }

    private ImageView renderPlayButton(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            ChannelAdaptor channelAdaptor,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        // Draw play button on top of poster (or instead of the poster if no poster defined)
        ImageView playButtonView;
        String playButtonUrl = hostConfig.GetMedia().getPlayButton();

        RelativeLayout.LayoutParams playButtonLayoutParams = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        playButtonLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);

        if (!playButtonUrl.isEmpty())
        {
            Image playButton = new Image();
            playButton.SetUrl(playButtonUrl);
            playButton.SetImageSize(ImageSize.Small);

            playButtonView = ImageRenderer.getInstance().render(renderedCard, context, fragmentManager, viewGroup, playButton, channelAdaptor, hostConfig, renderArgs);
            ((TagContent) playButtonView.getTag()).GetStretchContainer().setLayoutParams(playButtonLayoutParams);
        }
        else
        {
            Resources resources = context.getResources();
            Bitmap playButton = BitmapFactory.decodeResource(resources, android.R.drawable.ic_media_play);

            playButtonView = new ImageView(context);
            playButtonView.setImageBitmap(playButton);
            viewGroup.addView(playButtonView);
            playButtonView.setLayoutParams(playButtonLayoutParams);
        }

        return playButtonView;
    }

    private class PlayerListener implements Player.Listener
    {
        private MediaOnCompletionListener m_onCompletionListener = null;

        public PlayerListener(MediaOnCompletionListener onCompletionListener)
        {
            m_onCompletionListener = onCompletionListener;
        }

        @Override
        public void onEvents(Player player, Player.Events events)
        {
            if (events.contains(EVENT_PLAYBACK_STATE_CHANGED))
            {
                m_onCompletionListener.onCompletion(null);
            }
        }
    }

    private View renderNewMediaPlayer(
        RenderedAdaptiveCard renderedCard,
        Context context,
        ViewGroup viewGroup,
        Media media,
        ICardActionHandler cardActionHandler,
        HostConfig hostConfig)
    {
        StyledPlayerView playerView = new StyledPlayerView(context);
        playerView.setUseController(true);
        playerView.setControllerHideOnTouch(true);
        playerView.setResizeMode(AspectRatioFrameLayout.RESIZE_MODE_FIXED_WIDTH);
        playerView.setShowSubtitleButton(true);
        playerView.setControllerShowTimeoutMs(4000);
        playerView.setControllerHideOnTouch(true);

        ExoPlayer player = new ExoPlayer.Builder(context).setTrackSelector(new DefaultTrackSelector(context)).build();

        DefaultHttpDataSource.Factory dataSourceFactory = new DefaultHttpDataSource.Factory();
        io.adaptivecards.objectmodel.MediaSource mediaSource = media.GetSources().get(0);
        MediaItem.Builder mediaItemBuilder = new MediaItem.Builder().setUri(Uri.parse(mediaSource.GetUrl()));

        CaptionSourceVector captionSources = media.GetCaptionSources();
        int captionSourcesCount = captionSources.size();
        for (int i = 0; i < captionSourcesCount; ++i)
        {
            CaptionSource captionSource = media.GetCaptionSources().get(i);
            if (captionSource.GetMimeType().contains("vtt"))
            {
                Uri subtitleUri = Uri.parse(captionSource.GetUrl());

                MediaItem.SubtitleConfiguration.Builder subtitleConfigurationBuilder = new MediaItem.SubtitleConfiguration.Builder(subtitleUri);
                subtitleConfigurationBuilder.setLabel(captionSource.GetLabel());
                subtitleConfigurationBuilder.setMimeType(MimeTypes.TEXT_VTT);
                subtitleConfigurationBuilder.setSelectionFlags(C.SELECTION_FLAG_DEFAULT);

                mediaItemBuilder.setSubtitleConfigurations(ImmutableList.of(subtitleConfigurationBuilder.build()));
            }
        }

        MediaItem mediaItem = mediaItemBuilder.build();
        com.google.android.exoplayer2.source.MediaSource playerMediaSource = new DefaultMediaSourceFactory(dataSourceFactory, new DefaultExtractorsFactory()).createMediaSource(mediaItem);
        player.setMediaSource(playerMediaSource);

        playerView.setPlayer(player);

        player.prepare();

        player.addListener(new PlayerListener(new MediaOnCompletionListener(media, renderedCard, cardActionHandler)));

        viewGroup.addView(playerView);

        return playerView;
    }

    private View renderOldMediaPlayer(
        RenderedAdaptiveCard renderedCard,
        Context context,
        ViewGroup viewGroup,
        Media media,
        ICardActionHandler cardActionHandler,
        HostConfig hostConfig)
    {
        final FullscreenVideoView mediaView = new FullscreenVideoLayout(context);

        final MediaSourceVector mediaSources = media.GetSources();
        final long sourcesSize = mediaSources.size();

        if (sourcesSize > 0)
        {
            final boolean isAudio = mediaSources.get(0).GetMimeType().startsWith("audio");
            boolean registeredOnlineMediaLoader = false;

            // DataMediaSource was introduced in Android M
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M)
            {
                // We're leaving everything to the online media loader implementation
                IOnlineMediaLoader onlineMediaLoader = CardRendererRegistration.getInstance().getOnlineMediaLoader();
                if (onlineMediaLoader != null)
                {
                    mediaView.setDataSource(onlineMediaLoader.loadOnlineMedia(mediaSources, new IMediaDataSourceOnPreparedListener() {
                        @Override
                        public void prepareMediaPlayer() {
                            mediaView.prepare();
                        }
                    }), isAudio);
                    registeredOnlineMediaLoader = true;
                }
            }

            if (!registeredOnlineMediaLoader)
            {
                for (int i = 0; i < sourcesSize; i++)
                {
                    MediaSource mediaSource = mediaSources.get(i);
                    String mimeType = mediaSource.GetMimeType();

                    if (isSupportedMimeType(mimeType))
                    {
                        try
                        {
                            new MediaLoaderAsync(mediaView, mediaSource, hostConfig, isAudio, context).execute("");
                            break;
                        }
                        catch (Exception e)
                        { }
                    }
                }
            }
        }
        mediaView.setShouldAutoplay(true);
        mediaView.setContentDescription(media.GetAltText());

        mediaView.setOnCompletionListener(new MediaOnCompletionListener(media, renderedCard, cardActionHandler));

        viewGroup.addView(mediaView);

        return mediaView;
    }

    private View renderMediaPlayer(
            RenderedAdaptiveCard renderedCard,
            Context context,
            ViewGroup viewGroup,
            Media media,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig)
    {
        final long sourcesSize = media.GetSources().size();

        View playerView = null;

        // If there's a video or audio to render proceed
        if (sourcesSize > 0)
        {
            IOnlineMediaLoader onlineMediaLoader = CardRendererRegistration.getInstance().getOnlineMediaLoader();

            // if the onlineMediaLoader is null we can proceed using the new loader
            if (onlineMediaLoader == null)
            {
                playerView = renderNewMediaPlayer(renderedCard, context, viewGroup, media, cardActionHandler, hostConfig);
            }
            else
            {
                playerView = renderOldMediaPlayer(renderedCard, context, viewGroup, media, cardActionHandler, hostConfig);
            }
        }

        RelativeLayout.LayoutParams videoViewLayoutParams = new RelativeLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
        videoViewLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_START);
        videoViewLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_END);
        videoViewLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT);

        playerView.setLayoutParams(videoViewLayoutParams);
        playerView.setVisibility(View.GONE);

        return playerView;
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ChannelAdaptor channelAdaptor,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        Media media = Util.castTo(baseCardElement, Media.class);

        LinearLayout mediaLayout = new LinearLayout(context);
        mediaLayout.setTag(new TagContent(media));
        mediaLayout.setOrientation(LinearLayout.VERTICAL);

        RelativeLayout posterLayout = new RelativeLayout(context);
        ImageView posterView = renderPoster(renderedCard, context, fragmentManager, posterLayout, media, channelAdaptor, hostConfig, renderArgs);
        ImageView playButtonView = renderPlayButton(renderedCard, context, fragmentManager, posterLayout, channelAdaptor, hostConfig, renderArgs);
        View mediaView = renderMediaPlayer(renderedCard, context, posterLayout, media, channelAdaptor.getCardActionHandler(), hostConfig);

        posterLayout.setOnClickListener(new PosterOnClickListener(posterView, playButtonView, mediaView, hostConfig.GetMedia().getAllowInlinePlayback(), media, renderedCard, channelAdaptor.getCardActionHandler(), posterLayout));

        mediaLayout.addView(posterLayout);
        viewGroup.addView(mediaLayout);

        return mediaLayout;
    }

    private static MediaRenderer s_instance = null;
}
