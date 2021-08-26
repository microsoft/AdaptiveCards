# Pipelines

## Pull Request Validation and Continuous Integration

These pipelines are run on the latest commit of every pull request with a protected base branch (i.e. `main`, `release/*`, or `feature/*`). The repo is configured to only allow merging into these branches when all checks pass. They are also run after every commit merged into protected branches.

They should ensure the code builds successfully and passes all written tests. The JS pipeline additionally pushes the built site to an endpoint.

* `.pipelines/android-ci.yml`
    * Unit tests
    * UI tests
* `.pipelines/uwp-ci.yml`
    * Unit tests
    * UI tests
* Pipelines -> PR Validation -> AdaptiveCards-iOS-CI
	* Unit tests
* Pipelines -> PR Validation -> Adaptivecards-.NET-PR
	* (tests not currently being run)
* Pipelines -> Daily Builds -> AdaptiveCards-NodeJS-Daily
	* (tests not currently being run)
    * Before merge, publishes to https://adaptivecardsci.z5.web.core.windows.net/pr/####
    * After merge, publishes to https://adaptivecards-ci.azurewebsites.net/

## Daily Package Pipelines

These pipelines are run on the latest commit of `main` every night.

They should build and publish a new nightly version of each platform to our [private ADO feed](https://microsoft.visualstudio.com/AdaptiveCards/_packaging?_a=feed&feed=AdaptiveCards).

* `.pipelines/android-daily.yml`
	* Published to private feed
* Pipelines -> Daily Builds -> AdaptiveCards-NodeJS-Daily
	* Publishes to private feed
* Pipelines -> Daily Builds -> AdaptiveCards-UWP-Daily
	* (only publishes as a Pipeline artifact)
* Pipelines -> Daily Builds -> AdaptiveCards-.NET-Daily
	* (only publishes as a Pipeline artifact)
* (no daily build configured for iOS)

## Daily App Pipelines

These pipelines are run on the latest commit of `main` every night.

They should build and publish a new nightly version of each visualizer app.

* Pipelines -> Apps -> Android Visualizer
	* Publishes to App Center ([Adaptive Cards Android Visualizer](https://appcenter.ms/orgs/Adaptive-Cards/apps/Adaptive-Cards-Android-Visualizer))
* Pipelines -> Apps -> AdaptiveCards-iOS-Publish-App
	* Publishes to App Center ([Adaptive Cards iOS Visualizer](https://appcenter.ms/orgs/Adaptive-Cards/apps/Adaptive-Cards-iOS-Visualizer))
* Pipelines -> Apps -> WPF Visualizer Prerelease
	* (only publishes as a Pipeline artifact)
* Pipelines -> Apps -> UWP Visualizer Nightly-x86
	* (only publishes as a Pipeline artifact)
* (CI site serves as JS visualizer)

## Release Pipelines

These pipelines are run manually to publicly release a package.

While they can be triggered off `main`, current practice is to create a `release/*` branch ahead of release (see ReleaseChecklist.md). The pipeline will build, test, and publish the desired packages to the platform's main public repository.

* `.pipelines/android-release.yml`
* `.pipelines/ios-release.yml`
* `.pipelines/js-release.yml`
	* Provide an array (YML syntax) of JS packages you wish to release
	* Set dry run to `false`
* Pipelines -> Official Builds -> AdaptiveCards-.NET-Release-ESRP
	* Set `PerformNugetPush` to `true`
* Pipelines -> Official Builds -> AdaptiveCards-UWP-Release-ESRP
	* Set `PerformNugetPush` to `true`
