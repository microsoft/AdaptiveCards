package com.microsoft.adaptivecards.renderer.action;

import android.content.Context;
import android.os.AsyncTask;
import android.text.TextUtils;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import com.microsoft.adaptivecards.renderer.http.HttpRequestHelper;
import com.microsoft.adaptivecards.renderer.http.HttpRequestResult;
import com.microsoft.adaptivecards.renderer.inputhandler.IInputHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.IShowCardActionHandler;
import com.microsoft.adaptivecards.renderer.actionhandler.ISubmitActionHandler;
import com.microsoft.adaptivecards.objectmodel.BaseActionElement;
import com.microsoft.adaptivecards.objectmodel.HostConfig;
import com.microsoft.adaptivecards.objectmodel.HttpAction;
import com.microsoft.adaptivecards.renderer.BaseActionElementRenderer;

import java.util.HashMap;
import java.util.Map;
import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.Locale;

/**
 * Created by bekao on 6/26/2017.
 */

public class HttpActionRenderer extends BaseActionElementRenderer
{
    private HttpActionRenderer()
    {
    }

    public static HttpActionRenderer getInstance()
    {
        if (s_instance == null)
        {
            s_instance = new HttpActionRenderer();
        }

        return s_instance;
    }

    protected class HttpButtonOnClickListener implements View.OnClickListener
    {
        public HttpButtonOnClickListener(HttpAction httpAction, Vector<IInputHandler> inputHandlerList)
        {
            m_httpAction = httpAction;
            m_inputHandlerList = inputHandlerList;
        }

        @Override
        public void onClick(View v)
        {
            new HttpRequestTask(m_httpAction, m_inputHandlerList).execute();
        }

        private HttpAction m_httpAction;
        private Vector<IInputHandler> m_inputHandlerList;
    }


    class HttpRequestTask extends AsyncTask<Void, String, HttpRequestResult<byte[]>>
    {
        public HttpRequestTask(HttpAction httpAction, Vector<IInputHandler> inputHandlerList)
        {
            m_httpAction = httpAction;
            m_inputHandlerList = inputHandlerList;
        }

        private String replaceWithBindingData(String text, String patternStr, Map<String, String> data)
        {
            Pattern pattern = Pattern.compile(patternStr);
            Matcher matcher = pattern.matcher(text);
            StringBuffer stringBuffer = new StringBuffer();
            while (matcher.find())
            {
                matcher.appendReplacement(stringBuffer, data.get(matcher.group(1)));
            }
            matcher.appendTail(stringBuffer);
            return stringBuffer.toString();
        }

        @Override
        protected HttpRequestResult<byte[]> doInBackground(Void... voids)
        {
            try
            {
                String urlDataBinded = null;
                String bodyDataBinded = null;

                // data bind url and body for http post
                {
                    HashMap<String, String> data = new HashMap<String, String>();
                    for (IInputHandler inputHandler : m_inputHandlerList)
                    {
                        Exception excep = inputHandler.getData(data);
                        if (excep != null)
                        {
                            return new HttpRequestResult<byte[]>(excep);
                        }
                    }

                    String pattern = "\\{\\{(" + TextUtils.join("|", data.keySet()) + ")\\.Value\\}\\}";
                    urlDataBinded = replaceWithBindingData(m_httpAction.GetUrl(), pattern, data);
                    bodyDataBinded = replaceWithBindingData(m_httpAction.GetBody(), pattern, data);
                }

                if (TextUtils.isEmpty(urlDataBinded))
                {
                    return new HttpRequestResult<byte[]>(new IllegalArgumentException("URL cannot be empty."));
                }

                if (TextUtils.isEmpty(bodyDataBinded))
                {
                    return new HttpRequestResult<byte[]>(new IllegalArgumentException("body cannot be empty."));
                }

                String method = m_httpAction.GetMethod().toUpperCase(Locale.getDefault());
                Map<String, String> requestProperty = null;
                if (method.equals(HttpRequestHelper.HTTP_METHOD_POST))
                {
                    return new HttpRequestResult<byte[]>(HttpRequestHelper.post(urlDataBinded, requestProperty, bodyDataBinded));
                }
                else if (method.equals(HttpRequestHelper.HTTP_METHOD_GET))
                {
                    return new HttpRequestResult<byte[]>(HttpRequestHelper.get(urlDataBinded, requestProperty));
                }
                else if (method.equals(HttpRequestHelper.HTTP_METHOD_PUT))
                {
                    return new HttpRequestResult<byte[]>(HttpRequestHelper.put(urlDataBinded, requestProperty, bodyDataBinded));
                }
                else
                {
                    throw new IllegalArgumentException("Unsupported HTTP method: " + m_httpAction.GetMethod());
                }
            }
            catch (Exception excep)
            {
                return new HttpRequestResult<byte[]>(excep);
            }
        }

        @Override
        protected void onPostExecute(HttpRequestResult result)
        {
            super.onPostExecute(result);
        }

        private HttpAction m_httpAction;
        private Vector<IInputHandler> m_inputHandlerList;
    }

    @Override
    public Button render(
            Context context,
            ViewGroup viewGroup,
            BaseActionElement baseActionElement,
            Vector<IInputHandler> inputHandlerList,
            IShowCardActionHandler showCardActionHandler,
            ISubmitActionHandler submitActionHandler,
            HostConfig hostConfig)
    {
        HttpAction httpAction = null;
        if (baseActionElement instanceof HttpAction)
        {
            httpAction = (HttpAction) baseActionElement;
        }
        else if ((httpAction = HttpAction.dynamic_cast(baseActionElement)) == null)
        {
            throw new InternalError("Unable to convert BaseActionElement to HttpAction object model.");
        }

        Button button = renderButton(context, viewGroup, httpAction, hostConfig);
        button.setOnClickListener(new HttpButtonOnClickListener(httpAction, inputHandlerList));
        return button;
    }

    private static HttpActionRenderer s_instance = null;
}
