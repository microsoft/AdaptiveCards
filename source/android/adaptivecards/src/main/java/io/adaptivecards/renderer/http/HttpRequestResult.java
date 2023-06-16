// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.http;

public class HttpRequestResult<RESULT>
{
    public HttpRequestResult(Exception excep)
    {
        m_excep = excep;
        m_success = false;
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
        return m_success;
    }

    private Exception m_excep = null;
    private RESULT m_result = null;
    private boolean m_success = true;
}
