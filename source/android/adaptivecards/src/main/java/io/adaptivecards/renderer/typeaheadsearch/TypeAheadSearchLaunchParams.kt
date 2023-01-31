package io.adaptivecards.renderer.typeaheadsearch

import java.io.Serializable

data class TypeAheadSearchLaunchParams(
    val selectedTitle: String,
    val choicesDataType: String,
    val dataset: String,
    val valueList: List<String>,
    val titleList: List<String>,
    val screeTitle: String,
    val searchIconParams: SearchIconParams,
    val crossIconParams: CrossIconParams,
    val tickIconParams: TickIconParams,
    val backIconParams: BackIconParams,
    val startSearchingIconParams: StartSearchingStateParams,
    val noResultIconParams: NoResultStateParams,
    val errorIconParams: ErrorStateParams
) : Serializable