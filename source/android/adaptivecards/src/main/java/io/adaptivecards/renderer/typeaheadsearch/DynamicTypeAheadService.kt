// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.renderer.typeaheadsearch

object DynamicTypeAheadService {
    private var choicesResolver: IChoicesResolver? = null

    fun setIChoicesResolver(resolver: IChoicesResolver?) {
        choicesResolver = resolver
    }

    fun removeIChoicesResolver() {
        choicesResolver = null
    }

    fun getChoicesResolver(): IChoicesResolver? {
        return choicesResolver
    }
}
