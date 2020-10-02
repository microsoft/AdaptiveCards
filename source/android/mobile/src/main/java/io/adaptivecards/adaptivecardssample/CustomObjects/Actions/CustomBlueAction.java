package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import android.annotation.SuppressLint;
import android.content.Context;
import android.support.v4.app.FragmentManager;
import android.view.ContextThemeWrapper;
import android.view.ViewGroup;
import android.widget.Button;

import io.adaptivecards.adaptivecardssample.R;
import io.adaptivecards.objectmodel.ActionElementParser;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.renderer.AdaptiveFallbackException;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.action.ActionElementRenderer;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class CustomBlueAction extends BaseActionElement
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

            blueAction.setAllCaps(false);
            blueAction.setBackgroundResource(R.drawable.custom_button_style);

            renderedCard.registerSubmitableAction(blueAction, renderArgs);
            return blueAction;
        }
    }

}
