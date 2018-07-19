package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.MediaPlayer;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.MediaController;
import android.widget.RelativeLayout;
import android.widget.VideoView;

import java.io.IOException;
import java.io.InputStream;
import java.net.MalformedURLException;
import java.net.URL;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.objectmodel.MediaSource;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.http.HttpRequestHelper;
import io.adaptivecards.renderer.http.HttpRequestResult;

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
        public PosterOnClickListener(ImageView poster, ImageView playButton, VideoView mediaView, boolean allowedInlinePlayback, BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard, ICardActionHandler cardActionHandler)
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
            if(m_allowedInlinePlayback)
            {
                if(((VideoViewResizeable) m_mediaView).isAudioOnly())
                {
                    // if it's audio, just move the video to the top
                    m_mediaView.setZOrderOnTop(true);
                }
                else
                {
                    // If it's a video, hide the poster (if it exists)
                    if(m_poster != null)
                    {
                        m_poster.setVisibility(View.GONE);
                    }
                }
                m_mediaView.start();
                m_mediaView.setVisibility(View.VISIBLE);
                m_playButton.setVisibility(View.GONE);
            }

            m_cardActionHandler.onMediaPlay(m_cardMediaElement, m_renderedAdaptiveCard);
        }

        private ImageView m_poster;
        private ImageView m_playButton;
        private VideoView m_mediaView;
        private boolean m_allowedInlinePlayback = true;

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

    private class MediaOnPreparedListener implements MediaPlayer.OnPreparedListener
    {
        public MediaOnPreparedListener(MediaController mediaController)
        {
            m_mediaController = mediaController;
        }

        @Override
        public void onPrepared(MediaPlayer mp)
        {
            m_mediaController.show(0);
            m_mediaController.requestLayout();
        }

        private MediaController m_mediaController;
    }

    private boolean isSupportedMimeType(String mimetype)
    {
        final String supportedMimeTypes[] = {"video/mp4", "audio/mp3", "audio/mpeg"};
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
            ContainerStyle containerStyle)
    {
        ImageView posterView = null;

        Image poster = new Image();
        if (!media.GetPoster().isEmpty())
        {
            poster.SetUrl(media.GetPoster());
        }
        else
        {
            poster.SetUrl(hostConfig.getMedia().getDefaultPoster());
        }

        if(!poster.GetUrl().isEmpty())
        {
            // Draw poster in posterLayout
            poster.SetImageSize(ImageSize.Auto);
            posterView = (ImageView) ImageRenderer.getInstance().render(renderedCard, context, fragmentManager, viewGroup, poster, cardActionHandler, hostConfig, containerStyle);

            RelativeLayout.LayoutParams posterLayoutParams = (RelativeLayout.LayoutParams) posterView.getLayoutParams();
            posterLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
            posterView.setLayoutParams(posterLayoutParams);
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
            ContainerStyle containerStyle)
    {
        // Draw play button on top of poster (or instead of the poster if no poster defined)
        ImageView playButtonView;
        String playButtonUrl = hostConfig.getMedia().getPlayButton();
        if(!playButtonUrl.isEmpty())
        {
            Image playButton = new Image();
            playButton.SetUrl(playButtonUrl);
            playButton.SetImageSize(ImageSize.Small);

            playButtonView = (ImageView) ImageRenderer.getInstance().render(renderedCard, context, fragmentManager, viewGroup, playButton, cardActionHandler, hostConfig, containerStyle);
        }
        else
        {
            Resources resources = context.getResources();
            Bitmap playButton = BitmapFactory.decodeResource(resources, android.R.drawable.ic_media_play);

            playButtonView = new ImageView(context);
            playButtonView.setImageBitmap(playButton);
            viewGroup.addView(playButtonView);
        }

        RelativeLayout.LayoutParams playButtonLayoutParams = (RelativeLayout.LayoutParams) playButtonView.getLayoutParams();
        playButtonLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT, RelativeLayout.TRUE);
        playButtonView.setLayoutParams(playButtonLayoutParams);

        return playButtonView;
    }

    private VideoViewResizeable renderMediaPlayer(
            Context context,
            ViewGroup viewGroup,
            Media media,
            HostConfig hostConfig)
    {
        VideoViewResizeable mediaView = new VideoViewResizeable(context);
        mediaView.setTag(media);

        final long sourcesSize = media.GetSources().size();
        for(int i = 0; i < sourcesSize; i++)
        {
            MediaSource mediaSource = media.GetSources().get(i);
            String mimeType = mediaSource.GetMimeType();
            if(isSupportedMimeType(mimeType))
            {
                try
                {
                    new MediaLoaderAsync(mediaView, mediaSource, hostConfig, mimeType.startsWith("audio"), context).execute("").get();
                    break;
                } catch(Exception e)
                {

                }
            }
        }

        RelativeLayout.LayoutParams videoViewLayoutParams = new RelativeLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT);
        videoViewLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_LEFT);
        videoViewLayoutParams.addRule(RelativeLayout.ALIGN_PARENT_RIGHT);
        videoViewLayoutParams.addRule(RelativeLayout.CENTER_IN_PARENT);
        mediaView.setLayoutParams(videoViewLayoutParams);

        mediaView.setVisibility(View.GONE);
        viewGroup.addView(mediaView);

        return mediaView;
    }

    private class MediaLoaderAsync extends AsyncTask<String, Void, Void>
    {
        public MediaLoaderAsync(VideoViewResizeable mediaView, MediaSource mediaSource, HostConfig hostConfig, boolean isAudio, Context context)
        {
            m_mediaView = mediaView;
            m_mediaSource = mediaSource;
            m_hostConfig = hostConfig;
            m_isAudio = isAudio;
            m_context = context;
        }

        @Override
        protected Void doInBackground(String... strings) {
            // if the provided uri is a valid uri or is valid with the resource resolver, then use that
            // otherwise, try to get the media from a local file
            String mediaSourceUrl = m_mediaSource.GetUrl();
            try {
                // Try loading online using only the path first
                try {
                    // check what to do here as I don't want to download the stream
                    HttpRequestHelper.query(mediaSourceUrl);
                    m_mediaView.setVideoURI(mediaSourceUrl, m_isAudio);
                } catch (MalformedURLException e1) {
                    // Then try using image base URL to load online
                    String baseUrl = m_hostConfig.getImageBaseUrl();
                    try {
                        if (baseUrl == null || baseUrl.isEmpty()) {
                            throw new IOException("Image base URL is empty or not specified");
                        }

                        // Construct a URL using the image base URL and path
                        URL urlContext = new URL(baseUrl);
                        URL url = new URL(urlContext, mediaSourceUrl);

                        HttpRequestHelper.query(url.toString());
                        m_mediaView.setVideoURI(baseUrl + mediaSourceUrl, m_isAudio);
                    } catch (MalformedURLException e2) {
                        String authority = m_context.getPackageName();

                        // Get media identifier
                        Resources resources = m_context.getResources();
                        int identifier = resources.getIdentifier(mediaSourceUrl, baseUrl, authority);
                        if (identifier == 0) {
                            throw new IOException("Media not found: " + mediaSourceUrl);
                        }

                        m_mediaView.setVideoPath("android.resource://" + authority + "/" + baseUrl + "/" + mediaSourceUrl, m_isAudio);
                    }
                }
            } catch (Exception e) {
                e.printStackTrace();
                // Do nothing if the media was not found at all
            }
            return null;
        }


        private VideoViewResizeable m_mediaView;
        private MediaSource m_mediaSource;
        private HostConfig m_hostConfig;
        private boolean m_isAudio;
        private Context m_context;
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
            ContainerStyle containerStyle)
    {
        Media media = null;

        if (baseCardElement instanceof Media)
        {
            media = (Media) baseCardElement;
        }
        else if ((media = Media.dynamic_cast(baseCardElement)) == null)
        {
            throw new InternalError("Unable to convert BaseCardElement to Media object model.");
        }

        setSpacingAndSeparator(context, viewGroup, media.GetSpacing(), media.GetSeparator(), hostConfig, true);

        LinearLayout mediaLayout = new LinearLayout(context);
        if( media.GetHeight() == HeightType.Stretch )
        {
            mediaLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT, 1));
        }
        else
        {
            mediaLayout.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        }
        mediaLayout.setOrientation(LinearLayout.VERTICAL);

        RelativeLayout posterLayout = new RelativeLayout(context);
        ImageView posterView = renderPoster(renderedCard, context, fragmentManager, posterLayout, media, cardActionHandler, hostConfig, containerStyle);
        ImageView playButtonView = renderPlayButton(renderedCard, context, fragmentManager, posterLayout, cardActionHandler, hostConfig, containerStyle);
        VideoViewResizeable mediaView = renderMediaPlayer(context, posterLayout, media, hostConfig);

        MediaController mediaController = new MediaController(context);
        mediaView.setMediaController(mediaController);

        if(!mediaView.isAudioOnly())
        {
            mediaController.setAnchorView(mediaView);
        }
        else
        {
            mediaController.setAnchorView(posterView);
        }

        mediaController.setMediaPlayer(mediaView);

        posterLayout.setOnClickListener(new PosterOnClickListener(posterView, playButtonView, mediaView, hostConfig.getMedia().getAllowInlinePlayback(), media, renderedCard, cardActionHandler));
        if (mediaView.isAudioOnly() && media.GetPoster().isEmpty() && hostConfig.getMedia().getDefaultPoster().isEmpty())
        {
            mediaView.setOnPreparedListener(new MediaOnPreparedListener(mediaController));
        }
        mediaView.setOnCompletionListener(new MediaOnCompletionListener(media, renderedCard, cardActionHandler));

        mediaLayout.addView(posterLayout);
        viewGroup.addView(mediaLayout);

        return mediaView;
    }

    private static MediaRenderer s_instance = null;
}
