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
    * Android pipeline produces artifacts that must be manually uploaded to a public repository
    * iOS pipeline is fully automated to publish, but requires the package version number to be entered at runtime
        * iOS packages are not signed
    * .NET piplines are fully automated to publish
    * Web rendering library must be manually audited, fixed, and published
    * Website pipeline, contingent on the aforementioned audit, is fully automated to release
* Release notes are manually compiled
    * List of issues that were fixed since last stable release is compiled for each platform. Ideally, this involves only going through issues tagged with the current milestone. In reality, some issues are fixed without changing milestones, while some fixes are issue-less PRs, which must all be manually checked
    * Notes must be written with issue URLs linked, to trigger bot comment on issues (notifies users who are waiting for fix to be available)
    * Non-blocking issues that arose during smoke are manually added to release notes' known issues

Additionally, the repository contains libraries contributed and maintained by the community, which we do not currently validate or publish in any way.

## Problem

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

## Proposal(s)

### Visualizer Builds
* .NET UWP, .NET WPF
    * Pipeline must output an artifact (ideally, publish to App Center) that is properly signed to allow smoke-testing visualizer without building from source

### SDK Publishing

* Android
    * Pipeline must upload artifacts to Sonatype staging repository
    * Pipeline must publish to maven central
        * Publish stage should be gated on manual approval (similar to website release pipeline), to reduce risk of inadvertent release
* Web
    * Create JS release pipeline, which must publish packages to npm
        * Pipeline must detect which packages have been updated OR allow configuring at runtime
* (all)
    * Pipelines must create and push Github release tags after successful publish

### Dependency Auditing

* Web
    * Reconcile different systems for detecting vulnerable dependencies (lerna/npm audit, Component Governance, Github dependabot)
    * Automation (dependabot, Github app, and/or ADO pipeline) should create PR's to fix vulnerabilities when detected, so the repository is compliant ahead of release-time
        * Migrate off of deprecated dependabot to allow for more precise configuration
        * Non-trivial dependency updates cannot be performed by any bots. Introduce a process to ensure these are assigned to a dev when detected, rather than allowed to languish until release.
* (community)
    * Inquire whether community-maintained sources that are not built/published by us need to adhere to component governance
        * If so, implement process and/or automation to fix vulnerabilities in these, too

### Microsoft Signing

* Android
    * [✓] Pipeline must securely sign with a corporate-managed certificate
* Web
    * Inquire current signing practices by other Microsoft-published npm packages for signing, as npm has no first-party support for author-signatures
        * Follow existing practices, or work with compliance team(s) to establish best practice

### Release Notes

* Pipeline should use release tags to determine last released commit for each package
* Pipeline should generate list of PR's and Issue's that constitute all the changes since the last release
    * PR numbers in commit messages should be used to associate each commit to a PR
    * Issue numbers in PR descriptions should be used to associate the commit to an Issue, if present
    * Pipeline may comment on each identified issue/PR to indicate that the fix is now published
* Pipeline should publish release notes, with above identified lists for each platform

## Looking Further

### TODO