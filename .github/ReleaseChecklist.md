# Prepare Project

1. Ensure that each platform has the desired version number
	* For JS, check the `version` property in the `package.json` of desired release packages
	* For iOS, check the `spec.version` property in `source/ios/tools/AdaptiveCards.podspec`
	* For Android, check `acVersion` in ` source/android/adaptivecards/gradle.properties`
	* For UWP/.NET, check `VersionMajor`, `VersionMinor`, and `NuGetPackVersion` in `/custom.props`
	* If any version is different from desired, create and merge a PR to update it in `main` before continuing.
	* Follow [semver.org](https://semver.org/) to version every package individually. 
	
  - [ ] Follow semantic versioning, preferring to revise minor versions for non-breaking changes (eg 2.1.0) and upgrading major versions for major breaking changes. Eg "2.0.0" for renderer binaries. NOTE: Each shipping artifact has its own versioning sequence (eg Templating SDK binaries should have their owning versioning scheme and not try to match the sequence of the renderer SDK binaries); Similarly, different platform implementations, esp ones that don't share a common code stack, may be expected to diverge even in their major versioning sequences from the other platform binaries, but our goal should be to keep these variances and releases in check and coordinate releases more broadly if and where possible. NOTE: AdaptiveCards Schema version number is yet another versioning metadata that has no bearing on the versioning of the released binaries/artifacts themselves (so for eg a 1.3 AdaptiveCards (schema) version may be implemented in Renderer versions 2.0.0 binaries/SDK)

2. Create a `release/*` branch. The `main` branch can now be used to merge PR's intended for a *future* release. Any additional PR's intended for the *impending* release should now target the newly created `release/*` branch.
	* Any PR's that go into `release/*` after this point should also be cherry-picked into `main`

3. Create a PR against `main` to move packages (only the ones intended to be released) to the *next* version (increment the least significant version specifier) for the *next* release.

  - [ ] Visit the project's releases page (e.g. `open https://github.com/microsoft/AdaptiveCards/releases`)
    - [ ] Create a new release object for the git tag using the format `<milestone>` eg `2020.07`
    - [ ] Ensure the title is of the format `AdaptiveCards <milestone>` eg `AdaptiveCards 2020.07`; Note: please adhere to these naming rules strictly to allow for post-processing of the generated release note (once published) by our bots for issue annotations with the release announce.
    - [ ] Ensure the release is based off of the release/`milestone` branch 
    - [ ] Add a brief description for the release, followed by a changelog of issues organized by Artifact head (Eg Website, Designer, Templating, Renderer) and then further broken up by platforms where applicable
    - [ ] For each feature breakdown, do include the links to the respective store download locations for the latest shipping versions (*See [this](https://github.com/microsoft/AdaptiveCards/releases/tag/2020.07) for an example*)
    - [ ] Ensure all issues and pull requests (where issues are not available) tagged "AdaptiveCardsv<sprint>" are included in the changelog in long-form syntax with the full HTTP URL (and not github short-hand notation via #<issueNum> or #<PRNum>, except to call out Known Issues below)
    - [ ] Include a `Known Issues` subsection with links to the issues in github short-hand notation (*not* full HTTP URL)- This is a fabricbot "ignore list" quirk we are leveraging to avoid annotating issues that are linked in the release notes but not actually fixed.
    - [ ] Call out any `Breaking Changes` or `Notable Bug Fixes` based on the "Breaking Changes" etc label filters on the bugs
    - [ ] Include a Smoke Testing Results section here with a pointer to our samples locations used for testing
    - [ ] Repeat this process for servicing release/1.2 series. We'll need to create a separate release draft for the servicing release to release/1.2 at this point in time
# Create, & publish new Packages
  - [ ] Kick off the respective release pipelines for .NET/UWP/iOS/Android renderer packages; Before publishing these please ensure that we smoke test our basic scenarios samples

	* [.pipelines/android-release.yml](https://microsoft.visualstudio.com/AdaptiveCards/_build?definitionId=56539)
	* [.pipelines/ios-release.yml](https://microsoft.visualstudio.com/AdaptiveCards/_build?definitionId=71528)
	* [.pipelines/js-release.yml](https://microsoft.visualstudio.com/AdaptiveCards/_build?definitionId=69110)
		* Provide a YML-syntax array of JS packages you wish to release (the pipeline should default to an array with all the packages we publish, so simply remove unwanted ones)
		* Set dry run to `false`
	* [Pipelines -> Official Builds -> AdaptiveCards-.NET-Release-ESRP](https://microsoft.visualstudio.com/AdaptiveCards/_build?definitionId=63716)
		* Set `PerformNugetPush` to `true`
	* [Pipelines -> Official Builds -> AdaptiveCards-UWP-Release-ESRP](https://microsoft.visualstudio.com/AdaptiveCards/_build?definitionId=63421)
		* Set `PerformNugetPush` to `true`

  - [ ] Publish new packages for the JS renderer and website (*if needed*); Deploy website changes to a test endpoint ahead of the final publish to adaptivecards.io
# Publish the release
