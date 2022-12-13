package io.adaptivecards

import java.io.Serializable

data class TypeAheadSearchLaunchParams(
    //choicesData: ChoicesData,
    val staticChoices: List<String>? = null,
    val title: String,
    val searchIconParams: SearchIconParams,
    val crossIconParams: CrossIconParams,
    val startSearchingIconParams: StartSearchingIconParams,
    val noResultIconParams: NoResultIconParams,
    val errorIconParams: ErrorIconParams
) : Serializable