# Infrastructure Roadmap

## SDK Publishing

* Android
    * Pipeline must upload artifacts to Sonatype staging repository
    * Pipeline must publish to maven central
        * Publish stage should be gated on manual approval (similar to website release pipeline)
* npm
    * Create JS release pipeline, which must publish packages to npm
        * Pipeline must detect which packages have been updated OR allow configuring at runtime
* (all)
    * Pipelines must create and push Github release tags after successful publish

## Dependency Auditing

* npm
    * Reconcile different systems for detecting vulnerable dependencies (lerna/npm audit, Component Governance, Github dependabot)
    * Automation (dependabot, Github app, and/or ADO pipeline) should create PR's to fix vulnerabilities when detected, so the repository is compliant ahead of release-time
* (community)
    * Inquire whether community-maintained sources that are not built/published by us need to adhere to component governance
        * If so, implement process and/or automation to fix vulnerabilities in these, too

## Microsoft Signing

* Android
    * [✓] Pipeline must securely sign with a corporate-managed certificate
* npm
    * Inquire current signing practices by other Microsoft-published npm packages for signing, as npm has no first-party support for author-signatures
        * Follow existing practices, or work with compliance team(s) to establish best practice

## Release Notes

* Pipeline should use release tags to determine last released commit for each package
* Pipeline should generate list of PR's and Issue's that constitute all the changes since the last release
    * PR numbers in commit messages should be used to associate each commit to a PR
    * Issue numbers in PR descriptions should be used to associate the commit to an Issue, if present
    * Pipeline may comment on each identified issue/PR to indicate that the fix is now published
* Pipeline should publish release notes, with above identified lists for each platform

