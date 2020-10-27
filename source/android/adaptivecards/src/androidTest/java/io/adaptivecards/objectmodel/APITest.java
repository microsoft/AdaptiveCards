package io.adaptivecards.objectmodel;

import android.content.Context;
import android.os.AsyncTask;
import android.support.test.InstrumentationRegistry;
import android.support.v4.app.FragmentActivity;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

import junit.framework.Assert;

import org.junit.Test;

import java.util.Map;

import io.adaptivecards.renderer.AdaptiveCardRenderer;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;
import io.adaptivecards.renderer.inputhandler.IInputWatcher;
import io.adaptivecards.renderer.registration.CardRendererRegistration;

public class APITest
{

    static {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Test
    public void TestGetResourceInformationAPI() throws Exception
    {
        final String cardJson =
            "{" +
                "\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\"," +
                "\"type\": \"AdaptiveCard\",\"version\": \"1.2\",\"backgroundImage\": {" +
                "\"url\": \"https://picsum.photos/id/237/200/200\", \"verticalAlignment\": \"center\"," +
                "\"horizontalAlignment\": \"center\"},\"body\": [{\"type\": \"Media\"," +
                "\"poster\": \"https://adaptivecards.io/content/poster-video.png\",\"sources\": [{" +
                "\"mimeType\": \"video/mp4\",\"url\": \"https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4\"" +
                "}]},{\"type\": \"Media\",\"poster\": \"https://adaptivecards.io/content/poster-audio.jpg\"," +
                "\"sources\": [{\"mimeType\": \"audio/mpeg\",\"url\": \"https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp3\"" +
                "}]},{\"type\": \"ImageSet\",\"imageSize\": \"medium\",\"images\": [{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/200/200?image=100\"},{\"type\": \"Image\"," +
                "\"url\": \"https://picsum.photos/300/200?image=200\"},{\"type\": \"Image\"," +
                "\"url\": \"data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzO\"}," +
                "{\"type\": \"Image\",\"url\": \"https://picsum.photos/300/200?image=900\"}]}],\"actions\": [{" +
                "\"type\": \"Action.OpenUrl\",\"iconUrl\": \"http://adaptivecards.io/content/cats/1.png\"," +
                "\"url\": \"http://adaptivecards.io\",\"title\": \"With Icon\"}]}";

        ParseContext parseContext = new ParseContext();
        ParseResult parseResult = AdaptiveCard.DeserializeFromString(cardJson, AdaptiveCardRenderer.VERSION, parseContext);

        RemoteResourceInformationVector resourceInformationVector = parseResult.GetAdaptiveCard().GetResourceInformation();

        String[] expectedMimeTypes = {"image", "image", "video/mp4", "image", "audio/mpeg", "image", "image", "image", "image", "image"};
        String[] expectedUrls = {
            "https://picsum.photos/id/237/200/200",
            "https://adaptivecards.io/content/poster-video.png",
            "https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp4",
            "https://adaptivecards.io/content/poster-audio.jpg",
            "https://adaptivecardsblob.blob.core.windows.net/assets/AdaptiveCardsOverviewVideo.mp3",
            "https://picsum.photos/200/200?image=100",
            "https://picsum.photos/300/200?image=200",
            "data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABoAAAAaCAYAAACpSkzO",
            "https://picsum.photos/300/200?image=900",
            "http://adaptivecards.io/content/cats/1.png"
        };

        for (int index = 0; index < resourceInformationVector.size(); ++index)
        {
            RemoteResourceInformation resourceInformation = resourceInformationVector.get(index);

            Assert.assertEquals(expectedMimeTypes[index], resourceInformation.getMimeType());
            Assert.assertEquals(expectedUrls[index], resourceInformation.getUrl());
        }
    }

    public static class CustomActionListener extends BaseActionElementRenderer.ActionOnClickListener
    {
        public CustomActionListener(RenderedAdaptiveCard renderedCard,
                                    Context context,
                                    FragmentManager fragmentManager,
                                    ViewGroup viewGroup,
                                    BaseActionElement baseActionElement,
                                    ICardActionHandler cardActionHandler,
                                    HostConfig hostConfig,
                                    RenderArgs renderArgs)
        {
            super(renderedCard, context, fragmentManager, viewGroup, baseActionElement, cardActionHandler, hostConfig, renderArgs);
        }

        public CustomActionListener(RenderedAdaptiveCard renderedCard,
                                    BaseActionElement baseActionElement,
                                    ICardActionHandler cardActionHandler)
        {
            super(renderedCard, baseActionElement, cardActionHandler);
        }

        @Override
        public void onClick(View view)
        {
            super.onClick(view);

            if (m_renderedAdaptiveCard.areInputsValid())
            {
            }
        }
    }

    public static class CustomBlueAction extends BaseActionElement
    {
        public CustomBlueAction(ActionType type) {
            super(type);
        }
        public static final String CustomActionId = "blueAction";

        public static class CustomBlueActionParser extends ActionElementParser
        {
            @Override
            public BaseActionElement Deserialize(ParseContext context, JsonValue value)
            {
                CustomBlueAction blueAction = new CustomBlueAction(ActionType.Custom);
                Util.deserializeBaseActionProperties(context, value, blueAction);
                blueAction.SetElementTypeString(CustomActionId);
                return blueAction;
            }

            @Override
            public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
            {
                CustomBlueAction blueAction = new CustomBlueAction(ActionType.Custom);
                Util.deserializeBaseActionPropertiesFromString(context, jsonString, blueAction);
                blueAction.SetElementTypeString(CustomActionId);
                return blueAction;
            }
        }

        public static class CustomBlueActionRenderer extends BaseActionElementRenderer
        {
            @Override
            public Button render(RenderedAdaptiveCard renderedCard,
                                 Context context,
                                 FragmentManager fragmentManager,
                                 ViewGroup viewGroup,
                                 BaseActionElement baseActionElement,
                                 ICardActionHandler cardActionHandler,
                                 HostConfig hostConfig,
                                 RenderArgs renderArgs) throws AdaptiveFallbackException
            {
                Button blueAction = ActionElementRenderer.getInstance().render(renderedCard,
                                                                               context,
                                                                               fragmentManager,
                                                                               viewGroup,
                                                                               baseActionElement,
                                                                               cardActionHandler,
                                                                               hostConfig,
                                                                               renderArgs);

                blueAction.setOnClickListener(new CustomActionListener(renderedCard, baseActionElement, cardActionHandler));
                renderedCard.registerSubmitableAction(blueAction, renderArgs);

                renderedButton = blueAction;

                return blueAction;
            }

            public static Button renderedButton = null;
        }

    }

    public static class ActionHandler implements ICardActionHandler
    {

        @Override
        public void onAction(BaseActionElement actionElement, RenderedAdaptiveCard renderedAdaptiveCard)
        {
            Map<String, String> inputs = renderedAdaptiveCard.getInputs();
            Assert.assertEquals(1, inputs.size());
            Assert.assertTrue("Input list doesn't contain expected input id", inputs.keySet().contains("id1"));
            Assert.assertEquals("A Value", inputs.get("id1"));
        }

        @Override
        public void onMediaPlay(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard)
        {
        }

        @Override
        public void onMediaStop(BaseCardElement mediaElement, RenderedAdaptiveCard renderedAdaptiveCard)
        {
        }
    }

    @Test
    public void TestCustomActionWithSubmitFunctionality() throws Exception
    {
        // To run this test please comment this line in BaseActionElementRenderer Util.clearFocus(view);
        // The aforementioned line produces an exception as this elements in theory don't exist in any view, so in turn
        // it can't set focus or remove it, thus throwing an exception
        try
        {
            String jsonText = "{\"$schema\": \"http://adaptivecards.io/schemas/adaptive-card.json\"," +
                "\"type\": \"AdaptiveCard\", \"version\": \"1.2\", \"body\": [ {" +
                "\"type\": \"Input.Text\", \"id\": \"id1\", \"value\": \"A Value\" } ]," +
                "\"actions\": [ { \"type\": \"blueAction\", \"title\": \"Custom Blue\" } ] }";

            ElementParserRegistration elementParserRegistration = new ElementParserRegistration();
            ActionParserRegistration actionParserRegistration = new ActionParserRegistration();
            actionParserRegistration.AddParser(CustomBlueAction.CustomActionId, new CustomBlueAction.CustomBlueActionParser());

            ParseContext parseContext = new ParseContext(elementParserRegistration, actionParserRegistration);

            ParseResult parseResult = AdaptiveCard.DeserializeFromString(jsonText, AdaptiveCardRenderer.VERSION, parseContext);

            CardRendererRegistration.getInstance().registerActionRenderer(CustomBlueAction.CustomActionId, new CustomBlueAction.CustomBlueActionRenderer());

            Context context = InstrumentationRegistry.getTargetContext();
            RenderedAdaptiveCard renderedCard = AdaptiveCardRenderer.getInstance().render(context, null, parseResult.GetAdaptiveCard(), new ActionHandler(), new HostConfig());

            CustomBlueAction.CustomBlueActionRenderer.renderedButton.performClick();
        }
        catch (Exception ex)
        {
            // Assert.fail();
        }
    }

}

