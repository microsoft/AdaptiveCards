// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import androidx.test.espresso.Espresso
import androidx.test.espresso.ViewInteraction
import androidx.test.espresso.action.ViewActions
import androidx.test.espresso.assertion.ViewAssertions
import androidx.test.espresso.matcher.RootMatchers
import androidx.test.espresso.matcher.ViewMatchers
import io.adaptivecards.renderer.TagContent
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput
import org.hamcrest.Matchers

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

    internal fun findInputInValidatedContainer(validatedContainerTagId : String) : ViewInteraction {
        return Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent(validatedContainerTagId)))));
    }

    internal fun clearTextInInput(input : ViewInteraction) {
        input.perform(ViewActions.scrollTo(), ViewActions.click(), ViewActions.clearText());
    }

    internal fun setTextInInput(input : ViewInteraction, text : String) {
        input.perform(ViewActions.scrollTo(), ViewActions.click(), ViewActions.clearText(), ViewActions.typeText(text));
    }

    internal fun selectPopupOption(optionText : String) {
        Espresso.onData(Matchers.`is`(optionText)).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());
    }

    internal fun clickOnElementWithText(text : String) {
        Espresso.onView(ViewMatchers.withText(text)).perform(ViewActions.click())
    }

    internal fun assertInputValuePairExists(inputId : String, value : String) {
        Espresso.onData(Matchers.`is`(RetrievedInput(inputId, value))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }
}
