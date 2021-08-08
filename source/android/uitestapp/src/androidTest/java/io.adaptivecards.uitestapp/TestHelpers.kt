// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import androidx.test.espresso.Espresso
import androidx.test.espresso.action.ViewActions
import androidx.test.espresso.matcher.ViewMatchers

object TestHelpers {
    internal fun goToTestCasesScreen() {
        Espresso.onView(ViewMatchers.withId(R.id.navigation_test_cases)).perform(ViewActions.click())
    }

    internal fun goToRenderedCardScreen() {
        Espresso.onView(ViewMatchers.withId(R.id.navigation_rendered_card)).perform(ViewActions.click())
    }

    internal fun goToInputsScreen() {
        Espresso.onView(ViewMatchers.withId(R.id.navigation_inputs)).perform(ViewActions.click())
    }
}
