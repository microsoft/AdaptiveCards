package io.adaptivecards.adaptivecardssample.CustomObjects.Actions;

import android.content.Context;
import android.os.AsyncTask;
import android.support.v4.app.FragmentManager;
import android.view.View;
import android.view.ViewGroup;

import io.adaptivecards.objectmodel.BaseActionElement;
import io.adaptivecards.objectmodel.HostConfig;
import io.adaptivecards.renderer.BaseActionElementRenderer;
import io.adaptivecards.renderer.RenderArgs;
import io.adaptivecards.renderer.RenderedAdaptiveCard;
import io.adaptivecards.renderer.actionhandler.ICardActionHandler;

public class CustomActionListener extends BaseActionElementRenderer.ActionOnClickListener
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
            view.setEnabled(false);

            WaitTask waitTask = new WaitTask(view);
            waitTask.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, null);
        }
    }

    private class WaitTask extends AsyncTask<Void, Void, Void>
    {
        private View m_view;

        public WaitTask(View view)
        {
            m_view = view;
        }

        @Override
        protected Void doInBackground(Void... voids)
        {
            try
            {
                Thread.sleep(1000);
            }
            catch (InterruptedException e)
            {
                e.printStackTrace();
            }

            return null;
        }

        @Override
        protected void onPostExecute(Void aVoid)
        {
            m_view.setEnabled(true);
        }
    }
}
