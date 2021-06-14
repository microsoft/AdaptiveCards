package io.adaptivecards.uitestapp;

import android.widget.DatePicker;

import io.adaptivecards.renderer.TagContent;
import io.adaptivecards.uitestapp.ui.inputs.RetrievedInput;

import org.junit.Assert;
import org.junit.Rule;
import org.junit.Test;
import org.junit.runner.RunWith;

import java.io.IOException;

import androidx.test.espresso.contrib.PickerActions;
import androidx.test.ext.junit.rules.ActivityScenarioRule;
import androidx.test.ext.junit.runners.AndroidJUnit4;
import androidx.test.filters.LargeTest;

import static androidx.test.espresso.Espresso.onData;
import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.assertion.ViewAssertions.matches;
import static androidx.test.espresso.matcher.ViewMatchers.isAssignableFrom;
import static androidx.test.espresso.matcher.ViewMatchers.isDisplayed;
import static androidx.test.espresso.matcher.ViewMatchers.withId;
import static androidx.test.espresso.matcher.ViewMatchers.withTagValue;
import static androidx.test.espresso.matcher.ViewMatchers.withText;
import static org.hamcrest.Matchers.allOf;
import static org.hamcrest.Matchers.hasEntry;
import static org.hamcrest.Matchers.hasItem;
import static org.hamcrest.Matchers.is;

@RunWith(AndroidJUnit4.class)
@LargeTest
public class UiTests
{

    static
    {
        System.loadLibrary("adaptivecards-native-lib");
    }

    @Rule
    public ActivityScenarioRule<RenderCardUiTestAppActivity> mActivityRule =
        new ActivityScenarioRule<>(RenderCardUiTestAppActivity.class);

    @Test
    public void MockTest() throws IOException
    {
        Assert.assertTrue(true);
    }

    @Test
    public void SmokeTestActivityUpdate() throws Exception
    {
        onData(is("ActivityUpdateWithLabels.json")).perform(click());

        TestHelpers.goToRenderedCardScreen();

        onView(withText("SET DUE DATE")).perform(click());

        // Set dueDate
        onView(withTagValue(is(new TagContent("dueDate")))).perform(click(), click());
        onView(isAssignableFrom(DatePicker.class)).perform(PickerActions.setDate(2021, 02, 04));
        onView(withText("OK")).perform(click());

        // Click ok submit action
        onView(allOf(withText("OK"), isDisplayed())).perform(click());

        TestHelpers.goToInputsScreen();

        onData(is(new RetrievedInput("dueDate", "2021-02-04"))).check(matches(isDisplayed()));
    }



}
