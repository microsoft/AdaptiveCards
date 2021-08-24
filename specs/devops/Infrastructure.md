# Release Management

## Current State

AdaptiveCards actively maintains rendering libraries for 5 UI platforms: Android, iOS, .NET WPF, NET UWP, and Web. For 4 of these platforms, there are visualizer apps we use to showcase and validate the rendering libraries' features. For Web, we maintain a website serves this purpose (in addition to a card designer, for quick authoring of cards). Below is an overview of the current development process and the pipelines within it:

Pull Requests

* CI pipelines are defined for each platform to verify the integrity of any PR before merge. These pipelines ensure the rendering libraries and apps build successfully, and pass all written tests.
    * Authors are expected to attach screenshot/clip of rendered fix, for review
* The Web pipeline additionally publishes the build to a unique URL, allowing reviewers to manually verify changes.
* These same pipelines are run on every commit that is added to `main`.

Nightly

* A nightly pipeline is defined for each app (i.e. website and 4 visualizers), which builds the app for manual verification of changes.
    * For iOS and Android, these builds are pushed to App Center.
    * For Web, the build is pushed to a ci url.
    * For .NET, the apps must be accessed from the pipeline's artifacts.
* A nightly pipeline is defined for each rendering library, which publishes packages to an internal Microsoft feed

Monthly

* Typically, a stable release needs to be made for every rendering library and the website on a monthly cadence. Some rendering libraries have multiple component packages, so each changed package needs to be released.
* Ahead of release, each package needs to be independently versioned, so manual PRs are created to modify version numbers defined in config files (i.e. `gradle.properties`, `custom.props`, and `package.json`).
* Smoke testing is manually performed on the latest available apps created by the nightly pipelines, checking for any major visible regressions in `samples/Scenario` cards. When an app is signed off by a tester, the corresponding rendering library is approved for release.
* A release pipeline is defined for 4 platforms and the website.
    * Android pipeline is fully automated to publish
    * iOS pipeline is fully automated to publish
        * iOS packages are not signed
    * .NET piplines are fully automated to publish
    * Web rendering libraryis fully automated to publish
		* JS packages are not signed
    * Website pipeline is fully automated to release
* Release notes are manually compiled
    * List of issues that were fixed since last stable release is compiled for each platform. Ideally, this involves only going through issues tagged with the current milestone. In reality, some issues are fixed without changing milestones, while some fixes are issue-less PRs, which must all be manually checked
    * Notes must be written with issue URLs linked, to trigger bot comment on issues (notifies users who are waiting for fix to be available)
    * Non-blocking issues that arose during smoke are manually added to release notes' known issues

Additionally, the repository contains libraries contributed and maintained by the community, which we do not currently validate or publish in any way.

## Motivation

As long as releases have significant overhead, the planning process becomes encumbered by the release process. There are several points throughout the current process that have room for improvement. Primarily, monthly releases involve significant context-switching by all developers, with many manual steps that take time away from development and open the door for errors.
* Some platforms do not publish consumable apps nightly, requiring a local build to smoke test before release.
* Versioning must be done manually and differently for each platform, which results in several last-minute PRs that must all go through 
* Dependencies are audited and fixed during release, which introduces changes after smoke tests and increases risk
* Release note generated is a highly manual process that not only takes time, but frequently misses some fixes. This has resulted in hosts being unsure of what changes they are consuming in an upgrade, and voicing lack of confidence in a release.

Benefit from any solutions can be gauged against the status quo through a few indicators:
* Number of dev-hours spent between adjacent cycles of active development
* Percent of release process that requires locally checked out repository
* Percent of release process that is vulnerable to human error

To fully benefit from agile development, teams need to be able to unceremoniously ship at the end of every cycle, decoupling release from planning. With that goal in mind, we should periodically re-evaluate the process and these indicators to identify sources of deficiencies.

## Roadmap

### ~~Epic 1. Enable automated publishing~~
~~Estimate: 10-13 points~~

* ~~Modify Android SDK release pipeline to upload signed artifact to Sonatype, and release to Maven Central after approval~~
* ~~Create NodeJS SDK release pipeline to build and publish packages to npm~~
* ~~Modify all pipelines to standardize version string handling~~
    * Open question: checked-in vs. runtime-configured version strings
        * Oversight: checked-in versions must be reviewed vs. runtime versions are susceptible to unchecked typos
        * Convenience: checked-in versions require PR checks to complete vs. runtime versions avoid release overhead
        * History/branching: when building an old commit/branch, checked-in versions indicate version vs. runtime versions have no indication
    * Proposed solution:
        * Version of a release is specified at pipeline runtime (no PR's needed)
        * Final publish of artifact is gated on additional approval, who is expected to check version number
        * Pipeline pushes updated version string into source control after successful publish
	* Final decision:
		* Maintain previous practice of checked-in versioning, following Azure SDK guidance
		* TODO: Create bot (leverage Azure SDK's infra for this, if possible) to bump version post-release
* ~~Modify all release pipelines to push git tags after release~~
* ~~Modify all release pipelines to migrate off of deprecated PackageES build pool~~

Outcome:
Any member should be able to publish any library using only their web browser.

### Epic 2. Lay groundwork for automated UI tests
Estimate: 7-10 points

* CI pipelines should run written tests
	* ~~Android unit tests~~
	* ~~Android UI tests~~
	* ~~UWP unit tests~~
	* ~~UWP UI tests~~
	* ~~iOS unit tests~~
	* iOS UI tests
	* JS unit tests
	* JS UI tests
	* .NET unit tests
	* .NET UI tests

Outcome:
Pending configuration and writing of tests, pipelines should now be ready to report any failing automated UI tests.

### Epic 3. Lower barriers for smoke testing
Estimate: 5-7 points

* Modify UWP and WPF visualizer pipelines to produce executables with valid test certificates
* Modify Android visualizer pipeline to publish app that can be installed directly on work-joined Android devices

Outcome:
Any member should be able to perform smoke testing on any visualizer app using only a test device, without setting up a dev environment.

### Epic 4. Produce compliant artifacts
Estimate: 3-5 points

* Configure timely, automatic upgrades of vulnerable dependencies
    * Automatically file high-priority bugs for vulnerabilities that cannot be fixed by bot
* Investigate signing practices by Microsoft-published npm packages, as npm has no first-party support for author-signatures
    * If no existing guidance, work with compliance teams to establish whether author-signing is required and how to achieve it

Outcome:
Packages should not contain any vulnerable dependencies at time of release, and all released artifacts should satisfy any Microsoft signing requirements.

### Epic 5. Generate release notes
Estimate: 7-9 points

* Create check to ensure that PRs follow standardized title format (i.e. indicate affected platform(s) and fixed issue(s))
* Create automation to enumerate commits since last release, parse their titles, and use them to generating release notes that list fixed issues organized by platform

Outcome:
Monthly release notes should be auto-generated, requiring minimal modification for any special callouts before posting

## Looking further

### Epic ?. Versioning without thinking
Estimate: 7-9 points

* Require PR titles to specify whether the fix is a chore, fix, or feature (and indicate presence of breaking changes)
    * Consider following a standard, such as [conventional-commits](https://www.conventionalcommits.org/en/v1.0.0/)
* Modify release pipelines to infer the new version string based on the semver impact of PRs since last release

Outcome:
Stable release versions should no longer be specified by members during release. The strings are generated based on severity of fixes, ensuring version adheres strictly to semver.