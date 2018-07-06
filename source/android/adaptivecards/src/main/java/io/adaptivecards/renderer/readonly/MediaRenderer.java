package io.adaptivecards.renderer.readonly;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.media.MediaPlayer;
import android.net.Uri;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.MediaController;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.VideoView;

import java.net.URL;
import java.net.URLConnection;

import io.adaptivecards.objectmodel.BaseCardElement;
import io.adaptivecards.objectmodel.CardElementType;
import io.adaptivecards.objectmodel.ContainerStyle;
import io.adaptivecards.objectmodel.Fact;
import io.adaptivecards.objectmodel.FactSet;
import io.adaptivecards.objectmodel.FactVector;
import io.adaptivecards.objectmodel.HeightType;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.IconPlacement;
import io.adaptivecards.objectmodel.Image;
import io.adaptivecards.objectmodel.ImageSize;
import io.adaptivecards.objectmodel.Media;
import io.adaptivecards.renderer.BaseCardElementRenderer;
import io.adaptivecards.renderer.IBaseCardElementRenderer;
import io.adaptivecards.renderer.InnerImageLoaderAsync;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class MediaRenderer extends BaseCardElementRenderer
{
    private MediaRenderer()
    {
    }

    public static  MediaRenderer getInstance()
    {
        if(s_instance == null)
        {
            s_instance = new MediaRenderer();
        }
        return s_instance;
    }

    private class MediaOnPreparedListener implements MediaPlayer.OnPreparedListener
    {

        public MediaOnPreparedListener(VideoView videoView)
        {
            m_videoView = videoView;
        }

        @Override
        public void onPrepared(MediaPlayer mediaPlayer)
        {
            m_videoView.start();
        }

        private VideoView m_videoView;

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

        // LinearLayout mediaLayout = new LinearLayout(context);


        VideoView videoView = new VideoView(context);
        videoView.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.MATCH_PARENT));
        videoView.setTag(media);

        MediaController mediaController = new MediaController(context);

        videoView.setMediaController(mediaController);
        mediaController.setAnchorView(videoView);
        mediaController.setMediaPlayer(videoView);
        videoView.setVideoURI(Uri.parse(media.GetSources().get(0).GetUrl()));



        videoView.setOnErrorListener(new MediaPlayer.OnErrorListener() {
            @Override
            public boolean onError(MediaPlayer mediaPlayer, int i, int i1) {
                return false;
            }
        });

        videoView.setOnPreparedListener(new MediaOnPreparedListener(videoView));

        videoView.setOnCompletionListener(new MediaPlayer.OnCompletionListener() {
            @Override
            public void onCompletion(MediaPlayer mediaPlayer) {
                mediaPlayer.start();
            }
        });

        videoView.setOnInfoListener(new MediaPlayer.OnInfoListener() {
            @Override
            public boolean onInfo(MediaPlayer mediaPlayer, int i, int i1) {
                return false;
            }
        });
        // mediaLayout.addView(videoView);

        viewGroup.addView(videoView);
        /*
        VideoView videoView = new VideoView(context);
        videoView.setTag(media);
        videoView.setMediaController(new MediaController(context));
        videoView.setVideoURI(media.Get);
        */

        return videoView;
    }

    private long getMediaSize(String uri)
    {
        long mediaSize = 0;
        try
        {
            URL url = new URL(uri);
            URLConnection urlConnection = url.openConnection();
            urlConnection.connect();
            mediaSize = urlConnection.getContentLength();
        }
        catch(Exception e)
        {

        }
        return mediaSize;
    }

    private static MediaRenderer s_instance = null;
}
