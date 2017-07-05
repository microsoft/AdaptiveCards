package com.microsoft.adaptivecards.adaptivecardssample;

import android.content.Context;
import android.support.v4.app.DialogFragment;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.ShowCardAction;
import com.microsoft.adaptivecards.renderer.AdaptiveCardRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;

/**
 * Created by bekao on 7/4/2017.
 */

public class ShowCardFragment extends DialogFragment
{
    public void initialize(Context context, FragmentManager fragmentManager, ShowCardAction showCardAction, IShowCardActionHandler showCardActionHandler, ISubmitActionHandler submitActionHandler, HostConfig hostConfig)
    {
        m_context = context;
        m_fragmentManager = fragmentManager;
        m_showCardAction = showCardAction;
        m_showCardActionHandler = showCardActionHandler;
        m_submitActionHandler = submitActionHandler;
        m_hostConfig = hostConfig;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState)
    {
        ViewGroup viewGroup = (ViewGroup) AdaptiveCardRenderer.getInstance().render(m_context, m_fragmentManager, m_showCardAction.GetCard(), m_showCardActionHandler, m_submitActionHandler, m_hostConfig);
        getDialog().setTitle(m_showCardAction.GetTitle());

        Button closeButton = new Button(m_context);
        closeButton.setText("Close");
        closeButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                dismiss();
            }
        });

        closeButton.setLayoutParams(new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT));
        viewGroup.addView(closeButton);
        return viewGroup;
    }

    private Context m_context;
    private FragmentManager m_fragmentManager;
    private ShowCardAction m_showCardAction;
    private IShowCardActionHandler m_showCardActionHandler;
    private ISubmitActionHandler m_submitActionHandler;
    private HostConfig m_hostConfig;
}
