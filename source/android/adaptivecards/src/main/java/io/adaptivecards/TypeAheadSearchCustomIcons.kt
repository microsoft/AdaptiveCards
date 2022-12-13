package io.adaptivecards

import java.io.Serializable

data class TypeAheadSearchCustomIcons(
    val searchIconParams: SearchIconParams,
    val crossIconParams: CrossIconParams,
    val startSearchingStateParams: StartSearchingStateParams,
    val noResultStateParams: NoResultStateParams,
    val errorStateParams: ErrorStateParams
) : Serializable