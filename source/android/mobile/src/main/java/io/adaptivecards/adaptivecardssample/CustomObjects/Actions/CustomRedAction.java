package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import android.app.Activity;
import android.content.Context;
import android.graphics.PorterDuff;
import android.support.v4.app.FragmentManager;
import android.view.ViewGroup;
import android.widget.Button;

import org.json.JSONException;
import org.json.JSONObject;

import io.adaptivecards.adaptivecardssample.R;
import io.adaptivecards.objectmodel.ActionElementParser;
import io.adaptivecards.objectmodel.ActionType;
import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.objectmodel.JsonValue;
import io.adaptivecards.objectmodel.ParseContext;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.Util;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class CustomRedAction extends BaseActionElement
{

    public CustomRedAction(ActionType type) {
        super(type);
    }

    public String getBackwardString()
    {
        return m_backwardsString;
    }

    public void setBackwardString(String s)
    {
        m_backwardsString = new String();
        for(int i = s.length() - 1; i >= 0; i--)
        {
            m_backwardsString += s.charAt(i);
        }
    }

    public static class CustomRedActionParser extends ActionElementParser
    {
        @Override
        public BaseActionElement Deserialize(ParseContext context, JsonValue value)
        {
            CustomRedAction element = new CustomRedAction(ActionType.Custom);
            Util.deserializeBaseActionProperties(context, value, element);

            element.SetElementTypeString(CustomRedAction.CustomActionId);
            element.SetId("backwardActionDeserialize");
            String val = value.getString();
            try {
                JSONObject obj = new JSONObject(val);
                element.setBackwardString(obj.getString("backwardString"));
            } catch (JSONException e) {
                e.printStackTrace();
                element.setBackwardString("deliaF");
            }
            return element;
        }

        @Override
        public BaseActionElement DeserializeFromString(ParseContext context, String jsonString)
        {
            CustomRedAction element = new CustomRedAction(ActionType.Custom);
            Util.deserializeBaseActionPropertiesFromString(context, jsonString, element);

            element.SetElementTypeString(CustomRedAction.CustomActionId);
            element.SetId("backwardActionDeserialize");
            try {
                JSONObject obj = new JSONObject(jsonString);
                element.setBackwardString(obj.getString("backwardString"));
            } catch (JSONException e) {
                e.printStackTrace();
                element.setBackwardString("deliaF");
            }
            return element;
        }
    }

    public static class CustomRedActionRenderer extends BaseActionElementRenderer
    {
        public CustomRedActionRenderer(Activity activity)
        {
            m_activity = activity;
        }

        @Override
        public Button render(RenderedAdaptiveCard renderedCard,
                             Context context,
                             FragmentManager fragmentManager,
                             ViewGroup viewGroup,
                             BaseActionElement baseActionElement,
                             ICardActionHandler cardActionHandler,
                             HostConfig hostConfig,
                             RenderArgs renderArgs)
        {
            Button backwardActionButton = new Button(context);
            renderedCard.registerSubmitableAction(backwardActionButton, renderArgs);

            CustomRedAction customAction = (CustomRedAction) baseActionElement.findImplObj();

            backwardActionButton.getBackground().setColorFilter(m_activity.getResources().getColor(R.color.redActionColor), PorterDuff.Mode.SRC_ATOP);
            backwardActionButton.setText(customAction.getBackwardString());
            backwardActionButton.setAllCaps(false);
            backwardActionButton.setOnClickListener(new BaseActionElementRenderer.ActionOnClickListener(renderedCard, baseActionElement, cardActionHandler));

            viewGroup.addView(backwardActionButton);

            return backwardActionButton;
        }

        private Activity m_activity;
    }

    private String m_backwardsString;
    public static final String CustomActionId = "redAction";
}
