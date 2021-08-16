# Adaptive Card UWP Test App

Regression tester that loops through all card payloads and determines which rendered cards have changed.

## How to use

1. First clone AdaptiveCards if you haven't yet
2. Open the UWP AdaptiveCards.sln in Visual Studio (one directory up)
3. Build and deploy `AdaptiveCardTestApp`
4. Select the payloads you want to test (recommend testing all, it only takes about 2 minutes, but you can use Ctrl+A once you've focused the checkbox to uncheck/check all)
5. Click the `Start test` button
6. The first time you do this, you'll have to pick the `Expected` folder. In the file picker, open the `AdaptiveCardTestApp` folder on your machine and select the `Expected` folder. This folder contains all the expected test results. If you picked the wrong folder, you'll have to uninstall the app and then re-deploy in order to re-pick the Expected folder.
7. Let the tests run.
8. View the results!
9. To make a new file the expected result, click the Accept button. You can also accept all changes at the top.