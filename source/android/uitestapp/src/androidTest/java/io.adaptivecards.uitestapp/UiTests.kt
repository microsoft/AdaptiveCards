// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import android.widget.DatePicker
import org.junit.runner.RunWith
import org.junit.Rule
import io.adaptivecards.uitestapp.RenderCardUiTestAppActivity
import kotlin.Throws
import androidx.test.espresso.Espresso
import androidx.test.espresso.ViewAction
import androidx.test.espresso.ViewAssertion
import androidx.test.espresso.ViewInteraction
import org.hamcrest.Matchers
import androidx.test.espresso.action.ViewActions
import io.adaptivecards.uitestapp.TestHelpers
import androidx.test.espresso.matcher.ViewMatchers
import io.adaptivecards.renderer.TagContent
import androidx.test.espresso.contrib.PickerActions
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput
import androidx.test.espresso.assertion.ViewAssertions
import androidx.test.espresso.matcher.RootMatchers
import androidx.test.ext.junit.rules.ActivityScenarioRule
import androidx.test.ext.junit.runners.AndroidJUnit4
import androidx.test.filters.LargeTest
import org.junit.Assert
import org.junit.Test
import java.io.IOException
import android.R.attr.y

import android.R.attr.x
import androidx.test.platform.app.InstrumentationRegistry.getInstrumentation
import androidx.test.uiautomator.UiDevice


@RunWith(AndroidJUnit4::class)
@LargeTest
class UiTests {
    companion object {
        init {
            System.loadLibrary("adaptivecards-native-lib")
        }
    }

    @get:Rule
    val mActivityRule: ActivityScenarioRule<RenderCardUiTestAppActivity> = ActivityScenarioRule<RenderCardUiTestAppActivity>(RenderCardUiTestAppActivity::class.java)

    @Test
    @Throws(IOException::class)
    fun MockTest() {
        Assert.assertTrue(true)
    }

    @Test
    @Throws(Exception::class)
    fun SmokeTestActivityUpdate() {
        Espresso.onData(Matchers.`is`("ActivityUpdateWithLabels.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()
        Espresso.onView(ViewMatchers.withText("SET DUE DATE")).perform(ViewActions.click())

        // Set dueDate
        Espresso.onView(ViewMatchers.withTagValue(Matchers.`is`(TagContent("dueDate")))).perform(ViewActions.scrollTo(), ViewActions.click(), ViewActions.click())
        Espresso.onView(ViewMatchers.isAssignableFrom(DatePicker::class.java)).perform(PickerActions.setDate(2021, 2, 4))
        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        // Click ok submit action
        Espresso.onView(Matchers.allOf(ViewMatchers.withText("OK"), ViewMatchers.isDisplayed())).perform(ViewActions.scrollTo(), ViewActions.click())
        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("dueDate", "2021-02-04"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun RenderedMarkdownStartsWithRightNumber() {
        Espresso.onData(Matchers.`is`("TextBlock.Markdown.NumberStart.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        Espresso.onView(ViewMatchers.withText("1. First item in the list;")).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
        Espresso.onView(ViewMatchers.withText("2. Second item in the list;")).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
        Espresso.onView(ViewMatchers.withText("3. Third item in the list;")).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))

        Espresso.onView(ViewMatchers.withText("10. The tenth thing\n11. The list is still going!\n12. Should be 12!")).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetCanFindSubstrings() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "rr" to try to find parrot
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click(),
            ViewActions.clearText(), ViewActions.typeText("rr"));

        Espresso.onData(Matchers.`is`("Crimson Shining Parrot")).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());

        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("chosenAnimal", "Crimson Shining Parrot"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetIgnoresCase() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "rr" to try to find parrot
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click(),
            ViewActions.clearText(), ViewActions.typeText("RR"));

        Espresso.onData(Matchers.`is`("Crimson Shining Parrot")).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());

        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("chosenAnimal", "Crimson Shining Parrot"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetCanFindPrefix() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "braz" to try to find brazillian
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click(),
            ViewActions.clearText(), ViewActions.typeText("braz"));

        Espresso.onData(Matchers.`is`("Brazilian Tulipwood")).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());

        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("chosenAnimal", "Brazilian Tulipwood"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetCanFindSuffix() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "cuda" to try to find barracuda
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click(),
            ViewActions.clearText(), ViewActions.typeText("cuda"));

        Espresso.onData(Matchers.`is`("Blackspot barracuda")).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());

        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("chosenAnimal", "Blackspot barracuda"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetShowsAllElementsWhenEmpty() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click(),
            ViewActions.clearText());

        Espresso.onData(Matchers.`is`("CORAL")).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());

        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("chosenAnimal", "Alaska tree coral"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetShowsAllElementsOnClick() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click(),
            ViewActions.clearText());

        // Click on a random point to dismiss the choices popup
        val device: UiDevice = UiDevice.getInstance(getInstrumentation())
        device.click(1, 20)

        // Click again on the choiceset
        Espresso.onView(ViewMatchers.withParent(ViewMatchers.withTagValue(Matchers.`is`(TagContent("chosenAnimal"))))).perform(
            ViewActions.scrollTo(), ViewActions.click());

        Espresso.onData(Matchers.`is`("Zebra White")).inRoot(RootMatchers.isPlatformPopup()).perform(ViewActions.scrollTo(), ViewActions.click());

        Espresso.onView(ViewMatchers.withText("OK")).perform(ViewActions.click())

        TestHelpers.goToInputsScreen()
        Espresso.onData(Matchers.`is`(RetrievedInput("chosenAnimal", "Zebra White"))).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
    }
}
