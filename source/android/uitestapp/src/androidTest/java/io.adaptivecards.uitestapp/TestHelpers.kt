// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import android.util.Log
import androidx.test.espresso.DataInteraction
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
    val TAG = "UITESTING";

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
        val METHOD_NAME = "SelectPopupOption";

        val optionDataInteraction : DataInteraction = Espresso.onData(Matchers.`is`(optionText)).inRoot(RootMatchers.isPlatformPopup());
        Log.i(TAG, "$METHOD_NAME - Found data $optionText");

        optionDataInteraction.perform(ViewActions.scrollTo());
        Log.i(TAG, "$METHOD_NAME - Scrolled to element");

        optionDataInteraction.check(ViewAssertions.matches(ViewMatchers.isDisplayed()));
        Log.i(TAG, "$METHOD_NAME - Asserted element is displayed");

        optionDataInteraction.perform(ViewActions.click());
        Log.i(TAG, "$METHOD_NAME - Clicked on option $optionText");
    }

    internal fun pickItemInFilteredChoiceSet(inputName : String, hint : String, choiceSetOption : String)
    {
        val METHOD_NAME = "PickItemInFilteredChoiceSet";

        var selectionWasSuccessful : Boolean = false;
        var retries : Int = 0;

        while (!selectionWasSuccessful && retries < 5) {
            Log.i(TAG, "$METHOD_NAME - Try #$retries")

            try {
                setTextInInput(findInputInValidatedContainer(inputName), hint)
                Log.i(TAG, "$METHOD_NAME - Set value to $hint")

                selectPopupOption(choiceSetOption)
                Log.i(TAG, "$METHOD_NAME - Set option to $choiceSetOption")

                selectionWasSuccessful = true;
            } catch (e: Exception) {
                e.printStackTrace();

                Thread.sleep(500);
            }

            retries++;
        }
    }

    internal fun clickOnElementWithText(text : String) {
        Espresso.onView(ViewMatchers.withText(text)).perform(ViewActions.click())
    }

    internal fun assertInputValuePairExists(inputId : String, value : String) {
        Espresso.onData(Matchers.`is`(RetrievedInput(inputId, value))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }
}
