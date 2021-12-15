// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import android.util.Log
import androidx.test.espresso.Espresso
import androidx.test.espresso.Espresso.onView
import androidx.test.espresso.ViewInteraction
import androidx.test.espresso.action.ViewActions
import androidx.test.espresso.assertion.ViewAssertions
import androidx.test.espresso.matcher.RootMatchers
import androidx.test.espresso.matcher.ViewMatchers
import androidx.test.espresso.matcher.ViewMatchers.isDisplayed
import androidx.test.espresso.matcher.ViewMatchers.isRoot

import io.adaptivecards.renderer.TagContent
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput
import org.hamcrest.CoreMatchers.anything
import org.hamcrest.Matchers
import java.util.concurrent.TimeUnit

object TestHelpers {
    internal fun goToTestCasesScreen() {
        onView(ViewMatchers.withId(R.id.navigation_test_cases)).perform(ViewActions.click())
    }

    internal fun goToRenderedCardScreen() {
        onView(ViewMatchers.withId(R.id.navigation_rendered_card)).perform(ViewActions.click())
    }

    internal fun goToInputsScreen() {
        onView(ViewMatchers.withId(R.id.navigation_inputs)).perform(ViewActions.click())
    }

    internal fun findInputInValidatedContainer(validatedContainerTagId : String) : ViewInteraction {
        // wait during 15 seconds for a view
        onView(isRoot()).perform(waitTagId(validatedContainerTagId, TimeUnit.SECONDS.toMillis(15)));

        return onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent(validatedContainerTagId)))));
    }

    internal fun clearTextInInput(input : ViewInteraction) {
        input.perform(ViewActions.scrollTo(), ViewActions.click(), ViewActions.clearText());
    }

    internal fun setTextInInput(input : ViewInteraction, text : String, inputAlreadyHasFocus : Boolean = false) {
        input.perform(ViewActions.scrollTo())
        if (!inputAlreadyHasFocus)
        {
            input.perform(ViewActions.click())
        }

        input.perform(ViewActions.clearText(), ViewActions.typeText(text));
    }

    internal fun selectPopupOption(optionText : String) {
        var success = false
        var e2 = Exception("Failed to click");
        for (i in 0 .. 5) {
            try {
                Espresso.onData(anything())
                    .atPosition(0)
                    .inRoot(RootMatchers.isPlatformPopup())
                    .check(ViewAssertions.matches(isDisplayed()));

                Espresso.onData(Matchers.`is`(optionText))
                    .inRoot(RootMatchers.isPlatformPopup())
                    .perform(ViewActions.scrollTo(), ViewActions.click())

                Thread.sleep(1000);

                success = true
                return
            }
            catch (e: Exception) {
                e2 = e;
                Log.println(Log.ERROR, "Not found", e.toString());
                Thread.sleep(1000);
            }
        }

        if (!success){
            throw e2;
        }
    }

    internal fun clickOnElementWithText(text : String) {
        Espresso.onView(ViewMatchers.withText(text)).perform(ViewActions.click())
    }

    internal fun assertInputValuePairExists(inputId : String, value : String) {
        Espresso.onData(Matchers.`is`(RetrievedInput(inputId, value))).check(ViewAssertions.matches(isDisplayed()))
    }
}
