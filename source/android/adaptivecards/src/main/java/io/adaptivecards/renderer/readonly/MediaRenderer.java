// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;in
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.objectmodel.MediaSource;
import io.adaptivecards.objectmodel.MediaSourceVector;
import io.adaptivecards.renderer.BaseCardElementRenderer;
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
        public PosterOnClickListener(ImageView poster, ImageView playButton, FullscreenVideoView mediaView, boolean allowedInlinePlayback, BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard, ICardActionHandler cardActionHandler)
        {
            m_poster = poster;
            m_playButton = playButton;
            m_mediaView = mediaView;
            m_allowedInlinePlayback = allowedInlinePlayback;

            m_cardMediaElement = mediaElement;
            m_renderedAdaptiveCard = renderedAdaptiveCard;
            m_cardActionHandler = cardActionHandler;
        }

        @Override
        public void onClick(View v)
        {
            if(!m_alreadyClicked)
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

                m_cardActionHandler.onMediaPlay(m_cardMediaElement, m_renderedAdaptiveCard);

                m_alreadyClicked = true;
            }
        }

        private ImageView m_poster;
        private ImageView m_playButton;
        private FullscreenVideoView m_mediaView;
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
            ICardActionHandler cardActionHandler,
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

        if(!poster.GetUrl().isEmpty())
        {
            // Draw poster in posterLayout
            poster.SetImageSize(ImageSize.Auto);
            posterView = ImageRenderer.getInstance().render(renderedCard, context, fragmentManager, viewGroup, poster, cardActionHandler, hostConfig, renderArgs);

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
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        // Draw play button on top of poster (or instead of the poster if no poster defined)
        ImageView playButtonView;
        String playButtonUrl = hostConfig.GetMedia().getPlayButton();

        RelativeLayout.LayoutParams playButtonLayoutParams = new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        playButtonLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);

        if(!playButtonUrl.isEmpty())
        {
            Image playButton = new Image();
            playButton.SetUrl(playButtonUrl);
            playButton.SetImageSize(ImageSize.Small);

            playButtonView = ImageRenderer.getInstance().render(renderedCard, context, fragmentManager, viewGroup, playButton, cardActionHandler, hostConfig, renderArgs);
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

    private FullscreenVideoView renderMediaPlayer(
            Context context,
            ViewGroup viewGroup,
            Media media,
            HostConfig hostConfig)
    {
        final FullscreenVideoView mediaView = new FullscreenVideoLayout(context);

        final MediaSourceVector mediaSources = media.GetSources();
        final long sourcesSize = mediaSources.size();

        if(sourcesSize > 0)
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

            if(!registeredOnlineMediaLoader)
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

        RelativeLayout.LayoutParams videoViewLayoutParams = new RelativeLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        videoViewLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_LEFT);
        videoViewLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);
        videoViewLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT);
        mediaView.setLayoutParams(videoViewLayoutParams);

        mediaView.setVisibility(View.GONE);

        viewGroup.addView(mediaView);

        return mediaView;
    }

    @Override
    public View render(
            RenderedAdaptiveCard renderedCard,
            Context context,
            FragmentManager fragmentManager,
            ViewGroup viewGroup,
            BaseCardElement baseCardElement,
            ICardActionHandler cardActionHandler,
            HostConfig hostConfig,
            RenderArgs renderArgs) throws Exception
    {
        Media media = Util.castTo(baseCardElement, Media.class);

        LinearLayout mediaLayout = new LinearLayout(context);
        mediaLayout.setTag(new TagContent(media));
        mediaLayout.setOrientation(LinearLayout.VERTICAL);

        RelativeLayout posterLayout = new RelativeLayout(context);
        ImageView posterView = renderPoster(renderedCard, context, fragmentManager, posterLayout, media, cardActionHandler, hostConfig, renderArgs);
        ImageView playButtonView = renderPlayButton(renderedCard, context, fragmentManager, posterLayout, cardActionHandler, hostConfig, renderArgs);
        FullscreenVideoView mediaView = renderMediaPlayer(context, posterLayout, media, hostConfig);

        posterLayout.setOnClickListener(new PosterOnClickListener(posterView, playButtonView, mediaView, hostConfig.GetMedia().getAllowInlinePlayback(), media, renderedCard, cardActionHandler));
        mediaView.setOnCompletionListener(new MediaOnCompletionListener(media, renderedCard, cardActionHandler));

        mediaLayout.addView(posterLayout);
        viewGroup.addView(mediaLayout);

        return mediaLayout;
    }

    private static MediaRenderer s_instance = null;
}
