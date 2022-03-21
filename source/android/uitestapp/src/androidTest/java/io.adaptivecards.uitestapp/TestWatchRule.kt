package io.adaptivecards.uitestapp

import org.junit.rules.TestWatcher
import org.junit.runner.Description

public class TestWatchRule : TestWatcher() {

    protected override fun starting(description: Description)
    {
        print("Starting test run");
    }

    protected override fun failed(e: Throwable?, description: Description?)
    {
        super.failed(e, description);
        print((description?.testClass?.simpleName ?: "") + " - " + (description?.methodName ?: ""));
    }
}
