package io.adaptivecards.renderer.typeaheadsearch

import java.io.Serializable

data class TypeAheadSearchLaunchParams(
    val choicesDataType: String,
    val dataset: String,
    val staticChoices: List<String>? = null,
    val title: String,
    val searchIconParams: SearchIconParams,
    val crossIconParams: CrossIconParams,
    val tickIconParams: TickIconParams,
    val backIconParams: BackIconParams,
    val startSearchingIconParams: StartSearchingStateParams,
    val noResultIconParams: NoResultStateParams,
    val errorIconParams: ErrorStateParams
) : Serializable