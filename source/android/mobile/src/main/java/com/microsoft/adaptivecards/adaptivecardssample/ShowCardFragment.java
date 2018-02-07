package com.microsoft.adaptivecards.adaptivecardssample;

import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.support.v4.app.DialogFragment;

import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.LinearLayout;

import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.ShowCardAction;
import com.microsoft.adaptivecards.renderer.AdaptiveCardRenderer;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;

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
        getDialog().getWindow().setSoftInputMode(WindowManager.LayoutParams.SOFT_INPUT_ADJUST_RESIZE);

        View v = inflater.inflate(R.layout.popup_fragment, container);

        ViewGroup viewGroup = (ViewGroup) AdaptiveCardRenderer.getInstance().render(m_context, m_fragmentManager, m_showCardAction.GetCard(), m_showCardActionHandler, m_submitActionHandler, m_hostConfig);
        getDialog().setTitle(m_showCardAction.GetTitle());

        ViewGroup insertPoint = (ViewGroup) v.findViewById(R.id.popup_fragment);
        insertPoint.addView(viewGroup);
        v.setFocusable(true);
        return v;
    }

    @Override
    public void onResume()
    {
        super.onResume();

        Dialog dialog = getDialog();
        if (dialog != null) {
            dialog.getWindow().setLayout(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.WRAP_CONTENT);
        }

    }

    private Context m_context;
    private FragmentManager m_fragmentManager;
    private ShowCardAction m_showCardAction;
    private IShowCardActionHandler m_showCardActionHandler;
    private ISubmitActionHandler m_submitActionHandler;
    private HostConfig m_hostConfig;
}
