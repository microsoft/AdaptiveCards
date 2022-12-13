package io.adaptivecards

import androidx.annotation.StringDef

/**
 *  Represents different invoke names for task module
 **/
@StringDef(
    TypeAheadResponseType.ERROR,
    TypeAheadResponseType.NO_INTERNET_CONNECTION,
    TypeAheadResponseType.NO_RESULT,
    TypeAheadResponseType.SHOW_RESULT
)
@Retention(AnnotationRetention.SOURCE)
annotation class TypeAheadResponseType {
    companion object {
        const val ERROR = "error"
        const val NO_INTERNET_CONNECTION = "noInternetConnection"
        const val NO_RESULT = "noResult"
        const val SHOW_RESULT = "showResults"
    }
}