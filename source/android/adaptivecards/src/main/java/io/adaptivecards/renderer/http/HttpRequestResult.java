// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.http;

import io.adaptivecards.ResponseType;

public class HttpRequestResult<RESULT>
{
    public HttpRequestResult(Exception excep)
    {
        this(excep, ResponseType.ERROR);
    }

    public HttpRequestResult(Exception excep, @ResponseType String responseType)
    {
        m_excep = excep;
        m_responseType = responseType;
    }

    public HttpRequestResult(RESULT result)
    {
        m_result = result;
    }

    public HttpRequestResult()
    {
    }

    public RESULT getResult()
    {
        return m_result;
    }

    public Exception getException()
    {
        return m_excep;
    }

    public boolean isSuccessful()
    {
        return ResponseType.SUCCESS.equalsIgnoreCase(m_responseType);
    }

    private Exception m_excep = null;
    private RESULT m_result = null;
    private @ResponseType String m_responseType = ResponseType.SUCCESS;
}
