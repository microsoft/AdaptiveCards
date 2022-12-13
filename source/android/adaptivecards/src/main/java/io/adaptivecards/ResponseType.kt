package io.adaptivecards

import androidx.annotation.StringDef

/**
 *  Represents different response types for HttpRequestResponse
 **/
@StringDef(
    ResponseType.ERROR,
    ResponseType.NO_INTERNET_CONNECTION,
    ResponseType.SUCCESS,
)
@Retention(AnnotationRetention.SOURCE)
annotation class ResponseType {
    companion object {
        const val ERROR = "error"
        const val NO_INTERNET_CONNECTION = "noInternetConnection"
        const val SUCCESS = "success"
    }
}