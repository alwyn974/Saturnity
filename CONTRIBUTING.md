# Contribution Guidelines

<!-- Links -->
[fork]: /fork
[pr]: /compare
[disscussion]: /discussions
[releases]: /releases
[code-of-conduct]: CODE_OF_CONDUCT.md
[table-of-contents]: #table-of-contents
[docs]: https://alwyn974.github.io/Saturnity/
[issues]: https://github.com/alwyn974/Saturnity/issues
[wiki]: https://alwyn974-rtype.gitbook.io/Saturnity
[contribute-opensource]: https://egghead.io/series/how-to-contribute-to-an-open-source-project-on-github
[make-pr]: http://makeapullrequest.com/
[fto]: http://www.firsttimersonly.com
[fork-pr-process]: https://gist.github.com/Chaser324/ce0505fbed06b947d962

First off, thanks for taking the time to contribute! ❤️

Welcome! We love receiving contributions from our community, so thanks for stopping by! </br>
There are many ways to contribute, see the [Table of Contents][table-of-contents] for different ways to help and details about how this project handles them. </br>

Please make sure to read the relevant section before making your contribution. It will make it a lot easier for us maintainers and smooth out the experience for all involved. The community looks forward to your contributions. 🎉

This document describes our development process. Following these guidelines shows that you respect the time and effort of the developers managing this project. In return, you will be shown respect in addressing your issue, reviewing your changes, and incorporating your contributions.

## Table of Contents

1. [Code of Conduct](#code-of-conduct)
2. [Important Resources](#important-resources)
3. [Questions](#questions)
4. [Feature Requests](#feature-requests)
5. [Improving Documentation](#improving-documentation)
6. [Reporting Bugs](#reporting-bugs)
7. [Contributing Code](#contributing-code)
    1. [Getting Started](#getting-started)
    2. [Finding an Issue!](#finding-an-issue)
    3. [Development Process](#development-process)
    4. [Building the Project](#building-the-project)
    5. [Testing](#testing)
    6. [Style Guidelines](#style-guidelines)
       1. [Code Formatting Rules](#code-formatting)
       2. [Branch Names](#branch-names)
       3. [Whitespace Cleanup](#whitespace-cleanup)
       4. [Git Commit Guidelines](#git-commit-guidelines)
8. [Pull Request Guidelines](#pull-request-process)
    1. [Addressing Feedback](#addressing-feedback)

## Code of Conduct

By participating in this project, you agree to abide by our [Code of Conduct][code-of-conduct]. We expect all contributors to follow the [Code of Conduct][code-of-conduct] and to treat fellow humans with respect.

## Important Resources

- docs: https://alwyn974.github.io/Saturnity/ (Doxygen)
- bugs: https://github.com/alwyn974/Saturnity/issues
- wiki: https://alwyn974-rtype.gitbook.io/saturnity (Gitbook)

## Questions

> If you want to ask a question please, read the **documentation** and **wiki** first.

Before asking a question, search among the [issues] already existing, some could help you. </br>
If you have found a suitable issue and still need clarification, you can write your question in this issue. </br>
It is also advisable to search for answers on the Internet first.

If you then still feel the need to ask a question and need clarification, we recommend the following:

- Open an [Issue][issues] using the question template.
- Provide as much context as you can about what you're running into.
- Provide project and platform versions (IDE, compiler, operating system), depending on what seems relevant.

We will then take care of the [issue][issues] as soon as possible.

## Feature Requests

Please create a new [GitHub issue][issues] for any major changes and enhancements that you wish to make. 
Please provide the feature you would like to see, why you need it, and how it will work. 
Discuss your ideas transparently and get community feedback before proceeding.

If you want to add a feature, feel free to create the [issue][issues] before and then link it to your [Pull Request][pr].

Major Changes that you wish to contribute to the project should be discussed first in an [GitHub issue][issues] that clearly outlines the changes and benefits of the feature.

Small Changes can directly be crafted and submitted to the GitHub Repository as a [Pull Request][pr]. See the section about [Pull Request Submission Guidelines](#pull-request-process), and for detailed information the core development documentation.

> **Note**
> Please use the issue template when submitting an issue.

## Reporting Bugs

**If you find a security vulnerability, do NOT open an issue. Email contact@alwyn974.re instead.**

Before you submit your issue, please [search the issue archive][issues] - maybe your question or issue has already been identified or addressed.
 
If you find a bug in the source code, you can help us by [submitting an issue to our GitHub issue tracker][issues]. Even better, you can submit a [Pull Request][pr] with a fix.

> **Note**
> Please use the issue template when submitting an issue.

## Improving Documentation

Should you have a suggestion for the documentation, you can open an [issue][issues] and outline the problem or improvement you have - however, creating the doc fix yourself is much better!

If you want to help improve the [docs][docs] or the [wiki][wiki], it's a good idea to let others know what you're working on to minimize duplication of effort. 
Create a new [issue][issues] (or comment on a related existing one) to let others know what you're working on.
If you're making a small change (typo, phrasing) don't worry about filing an issue first.

For large fixes, please build and test the documentation before submitting the [PR][pr] to be sure you haven't accidentally introduced any layout or formatting issues.

```bash
doxygen ./Doxyfile
xdg-open ./doc/html/index.html # Linux, open the doc/html/index.html in your browser instead
```

## Contributing Code

> ### Legal Notice
> When contributing to this project, you must agree that you have authored 100% of the content, that you have the necessary rights to the content and that the content you contribute may be provided under the project license.
> In case you want to add assets that require adding credits, please add the credits directly in the game.

Unsure where to begin contributing to Saturnity? You can start by looking through these help-wanted issues: 
- Help wanted issues - issues which should be a bit more involved than beginner issues.

Working on your first open source project or pull request? Here are some helpful tutorials:

- [How to Contribute to an Open Source Project on GitHub][contribute-opensource]
- [Make a Pull Request][make-pr]
- [First Timers Only][fto]

### Getting Started

Install these dependencies:

- CMake at least 3.17
- C++20 compiler (GCC 10, Clang 10, MSVC 19.26)

> **Note**
> The dependencies in this project are self-contained, so you don't need to install them globally.

You will need to [fork] the main repository to work on your changes. 
Simply navigate to our GitHub page and click the "[Fork][fork]" button at the top. 
Once you've forked the repository, you can clone your new repository and start making edits.

In git it is best to isolate each topic or feature into a "topic branch". 
While individual commits allow you control over how small individual changes are made to the code, branches are a great way to group a set of commits all related to one feature together, or to isolate different efforts when you might be working on multiple topics at the same time.

While it takes some experience to get the right feel about how to break up commits, a topic branch should be limited in scope to a single issue

```bash
# Checkout the main branch - you want your new branch to come from main
git checkout main

# Create a new branch named newfeature (give your branch its own simple informative name)
git branch feature/newfeature

# Switch to your new branch
git checkout feature/newfeature
```

For more information on the **GitHub fork** and **pull-request processes**, [please see this helpful guide][fork-pr-process].

### Finding an Issue

The list of outstanding feature requests and bugs can be found on our on our [GitHub issue tracker][issues].
Pick an unassigned issue that you think you can accomplish and add a comment that you are attempting to do it.

- `👌good first issue` labeled issues are deemed to be good low-hanging fruit for newcomers to the project
- `🆘 help wanted` labeled issues may be more difficult than `starter` and may include new feature development
- `📚 documentation` labeled issues must only touch documentation or the wiki
- `🚧 W.I.P` labeled issues are issues that are currently being worked on
- `✨ feature` labeled issues are feature requests that need to be implemented
- `🐛 bug` labeled issues are bugs that need to be fixed
- `🔃duplicate` labeled issues are duplicates of other issues
- `🚫 wontfix` labeled issues are issues that will not be fixed
- `🚫 invalid` labeled issues are issues that are invalid

### Development Process

This project follows the most likely the [git flow](http://nvie.com/posts/a-successful-git-branching-model/) branching model of product development:
- Feature: **feature/feature-name** (Used to develop a new feature)
- Fix: **fix/fix-name** (Used to fix an issue)
- Test: **test/test-name** (Should be used for testing something, or for testing a feature)
- Dev: **dev** (Latest development version)

You should be using the **main** branch for the most stable release; please review [release notes][releases] regularly.
If you want to keep up with the latest changes, we work in the `dev` branch.
If you are using `dev`, keep an eagle-eye on commits.

### Building the Project

If you want to build the project, clone the **main** or **dev** branch

```bash
cmake -B build -S .
cmake --build build --config Release # or Debug
```

### Testing

If you add code you need to add tests! We’ve learned the hard way that code without tests is undependable.
If your pull request reduces our test coverage because it lacks tests then it will be rejected.

#### Add test
To add tests, create a new cpp file in the `tests` directory.
You should use the `google-test` library to create your tests.

```cpp
#include <gtest/gtest.h>

TEST(Example, ExampleTest)
{
    EXPECT_EQ(1, 1);
}
```

And add it to the `tests/CMakeLists.txt` file

```cmake
add_executable(${BINARY_NAME} ${SOURCES_FILES} MainTest.cpp
    # Add your test file here
    TestExample.cpp
)
```

#### Run tests
```bash
cmake -B build -S . -DSATURNITY_BUILD_TESTS=ON
cmake --build build --target unit_test
./build/unit_test
```

### Style Guidelines

#### Code Formatting

Please follow the **.clang-format** & **.clang-tidy** files in the root directory of the project. </br>
You can run it through the `lint.sh` script` (Only on Linux)

```bash
./lint.sh

Running clang-format...
Formatting [1/3] include/saturnity/Saturnity.hpp
Formatting [2/3] main.cpp
Formatting [3/3] src/Saturnity.cpp
Some files need to be formatted
Do you want to format it? [y/N] y
Formatting [1/3] include/saturnity/Saturnity.hpp
Formatting [2/3] main.cpp
Formatting [3/3] src/Saturnity.cpp
```

#### Branch Names

As said in [Development Process](#development-process), you should use the following branch names:
- Feature: **feature/feature-name** (Used to develop a new feature)
- Fix: **fix/fix-name** (Used to fix an issue)
- Test: **test/test-name** (Should be used for testing something, or for testing a feature)
- Dev: **dev** (Latest development version)
- Main: **main** (Latest stable version)

Examples:
```md
feature/serialization
feature/udp-protocol
fix/issue-1
fix/packet-serialization
test/boost-framework
test/serialization
```

#### Whitespace Cleanup

Don’t mix code changes with whitespace cleanup! If you are fixing whitespace, include those changes separately from your code changes.
If your request is unreadable due to whitespace changes, it will be rejected.

> Please submit whitespace cleanups in a separate pull request.

#### Git Commit Guidelines

Most likely you will want to follow the [gitmoji](https://gitmoji.dev/) commit guidelines.

- The first line of the commit, should be a short description (50 chars or fewer) of the change.
- The other lines can be as detailed as you want, and should include more detailed explanations, links to issues, etc.

> Warning
> Each line of the commit message should have an emoji at the beginning of it.

Examples:
```md
🐛 Fix Issue #1
➕ Add boost library
✨ Add serialization feature
```

## Pull Request Process

When you are ready to generate a pull request, either for preliminary review, or for consideration of merging into the project you must first push your local topic branch back up to GitHub:

> **Note**
> If you are working on a fork, you will need to push your branch to your fork on GitHub. 
> Please follow the [Branch names](#branch-names) section.

```bash
git push origin feature/newfeature
```

Once you've committed and pushed all of your changes to GitHub, go to the page for your fork on GitHub, select your development branch, and click the pull request button.
If you need to make any adjustments to your pull request, just push the updates to your branch. 
Your pull request will automatically track the changes on your development branch and update.

1. Ensure any install or build dependencies are removed before the end of the layer when doing a build.
2. Make sure the tests pass on your machine
3. Update any relevant documentation.
4. Increase the version numbers in any examples files and the [README.md](./README.md) to the new version that this
   Pull Request would represent. The versioning scheme we use is [SemVer](http://semver.org/).
5. Pat your self on the back and wait for your pull request to be reviewed and merged. 
6. For a Pull Request to be merged:
   - CI workflow must succeed
   - A project member must review and approve it

### Addressing Feedback

Once a PR has been submitted, your changes will be reviewed and constructive feedback may be provided. Feedback isn't meant as an attack, but to help make sure the highest-quality code makes it into our project. Changes will be approved once required feedback has been addressed.

If a maintainer asks you to "rebase" your PR, they're saying that a lot of code has changed, and that you need to update your fork so it's easier to merge.

To update your forked repository, follow these steps:

```bash
# Fetch upstream main and merge with your repo's main branch
git fetch upstream
git checkout main
git merge upstream/main

# If there were any new commits, rebase your development branch
git checkout feature/newfeature
git rebase main
```

If too much code has changed for git to automatically apply your branches changes to the new **main**, you will need to manually resolve the merge conflicts yourself.

Once your new branch has no conflicts and works correctly, you can override your old branch using this command:

```bash
git push -f
```

Note that this will overwrite the old branch on the server, so make sure you are happy with your changes first!
