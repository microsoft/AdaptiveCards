// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.http;

public class HttpRequestResult<RESULT>
{
    public HttpRequestResult(Exception exception)
    {
        m_exception = exception;
        m_success = false;
    }

    public HttpRequestResult(Exception exception, String errorMessage)
    {
        this(exception);
        error_message = errorMessage;
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
        return m_exception;
    }

    public boolean isSuccessful()
    {
        return m_success;
    }

    private Exception m_exception = null;
    private RESULT m_result = null;
    private boolean m_success = true;
    private String error_message = null;
}
