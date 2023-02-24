// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.typeaheadsearch

import java.io.Serializable

data class TypeAheadSearchLaunchParams(
    val selectedTitle: String,
    val choicesDataType: String,
    val dataset: String,
    val valueList: List<String>,
    val titleList: List<String>,
    val backgroundColor: Int,
    val foregroundColor: Int
) : Serializable