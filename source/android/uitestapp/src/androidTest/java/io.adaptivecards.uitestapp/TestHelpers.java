package io.adaptivecards.uitestapp;

import io.adaptivecards.uitestapp.R;

import static androidx.test.espresso.Espresso.onView;
import static androidx.test.espresso.action.ViewActions.click;
import static androidx.test.espresso.matcher.ViewMatchers.withId;

public class TestHelpers
{

    protected static void goToTestCasesScreen()
    {
        onView(withId(R.id.navigation_test_cases)).perform(click());
    }

    protected static void goToRenderedCardScreen()
    {
        onView(withId(R.id.navigation_rendered_card)).perform(click());
    }

    protected static void goToInputsScreen()
    {
        onView(withId(R.id.navigation_inputs)).perform(click());
    }

}
