// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.
package io.adaptivecards.uitestapp

import android.widget.DatePicker
import org.junit.runner.RunWith
import io.adaptivecards.uitestapp.RenderCardUiTestAppActivity
import kotlin.Throws
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
import java.io.IOException
import android.R.attr.y

import android.R.attr.x
import android.content.Context
import android.util.Log
import android.view.View
import android.widget.LinearLayout
import androidx.test.core.app.ApplicationProvider
import androidx.test.espresso.*
import androidx.test.espresso.Espresso.*
import androidx.test.espresso.base.DefaultFailureHandler
import androidx.test.espresso.util.HumanReadables
import androidx.test.platform.app.InstrumentationRegistry.getInstrumentation
import androidx.test.uiautomator.UiDevice
import org.hamcrest.Matcher
import org.junit.*
import org.junit.rules.Timeout
import java.util.concurrent.TimeUnit


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

    // Add a timeout of 1 minute for every test
    @get:Rule
    var mTimeout = Timeout(60, TimeUnit.SECONDS)

    @Before
    @Throws(Exception::class)
    fun setUp() {

    }

    private class CustomFailureHandler(targetContext: Context, activityRule: ActivityScenarioRule<RenderCardUiTestAppActivity>) : FailureHandler {
        private val delegate: FailureHandler
        private val mActivityRule: ActivityScenarioRule<RenderCardUiTestAppActivity>

        init {
            delegate = DefaultFailureHandler(targetContext)
            mActivityRule = activityRule
        }

        override fun handle(error: Throwable, viewMatcher: Matcher<View>) {
            mActivityRule.scenario.onActivity {
                var cardLayout : View

                cardLayout = try {
                    it.findViewById(R.id.test_cases_list_view)
                } catch (e: java.lang.Exception) {
                    it.findViewById(R.id.layout_cardContainer)
                }

                val viewHierarchy: String = HumanReadables.getViewHierarchyErrorMessage(cardLayout, null, "", null)

                Log.e("Error view hierarchy", viewHierarchy)
            }

            delegate.handle(error, viewMatcher)
        }
    }

    @Test
    @Throws(IOException::class)
    fun MockTest() {
        setFailureHandler(CustomFailureHandler(
            ApplicationProvider.getApplicationContext<Context>(), mActivityRule))

        onData(Matchers.`is`("ActivityUpdateWithLabels.json")).check(ViewAssertions.matches(ViewMatchers.isDisplayed()))
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
        TestHelpers.setTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"), "rr")

        TestHelpers.selectPopupOption("Crimson Shining Parrot")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Crimson Shining Parrot")
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetIgnoresCase() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "rr" to try to find parrot
        TestHelpers.setTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"), "RR")

        TestHelpers.selectPopupOption("Crimson Shining Parrot")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Crimson Shining Parrot")
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetCanFindPrefix() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "braz" to try to find brazillian
        TestHelpers.setTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"), "braz")

        Thread.sleep(1000)

        TestHelpers.selectPopupOption("Brazilian Tulipwood")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Brazilian Tulipwood")
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetCanFindSuffix() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text and write "cuda" to try to find barracuda
        TestHelpers.setTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"), "cuda")

        TestHelpers.selectPopupOption("Blackspot barracuda")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Blackspot barracuda")
    }

    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetShowsAllElementsWhenEmpty() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset, delete all text
        TestHelpers.clearTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"))

        TestHelpers.selectPopupOption("CORAL")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Alaska tree coral")
    }

    // For some reason this test method is not working on the pipeline but does work locally,
    // more investigation will be performed
    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetShowsAllElementsOnClick() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset and delete all text
        val chosenAnimalContainer : ViewInteraction = TestHelpers.findInputInValidatedContainer("chosenAnimal")
        TestHelpers.clearTextInInput(chosenAnimalContainer)

        // Click on a random point to dismiss the choices popup
        val device: UiDevice = UiDevice.getInstance(getInstrumentation())
        device.click(1, 100)

        // Click again on the choiceset
        chosenAnimalContainer.perform(ViewActions.scrollTo(), ViewActions.click());

        TestHelpers.selectPopupOption("Zebra White")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Zebra White")
    }

    // For some reason this test method is not working on the pipeline but does work locally,
    // more investigation will be performed
    @Test
    @Throws(Exception::class)
    fun TestFilteredChoiceSetMaintainsAllChoices() {
        Espresso.onData(Matchers.`is`("Input.ChoiceSet.Filtered.json")).perform(ViewActions.click())
        TestHelpers.goToRenderedCardScreen()

        // Click on the filtered choiceset and type "parrot"
        TestHelpers.setTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"), "parrot");

        // Select and option to remove popup
        TestHelpers.selectPopupOption("Mexican Parrotlet")

        Thread.sleep(3000)

        // Click again on the choiceset and type "stygobromid", as there's only one result it
        // should have not appeared in the "parrot" query but it should still show up to verify
        // that options are not accidentally deleted when searching
        TestHelpers.setTextInInput(TestHelpers.findInputInValidatedContainer("chosenAnimal"), "stygobromid");

        TestHelpers.selectPopupOption("Alabama stygobromid")

        TestHelpers.clickOnElementWithText("OK")

        TestHelpers.goToInputsScreen()
        TestHelpers.assertInputValuePairExists("chosenAnimal", "Alabama stygobromid")
    }
}
