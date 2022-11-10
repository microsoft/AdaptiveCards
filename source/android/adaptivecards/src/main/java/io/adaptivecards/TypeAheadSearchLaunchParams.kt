package io.adaptivecards

import java.io.Serializable

data class TypeAheadSearchLaunchParams(
    //choicesData: ChoicesData,
    // interface for communication with host
    val staticChoices: List<String>? = null
) : Serializable