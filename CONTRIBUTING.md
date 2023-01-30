# Contribution Guidelines

[fork]: /fork
[pr]: /compare
[code-of-conduct]: CODE_OF_CONDUCT.md

Hi there! We're thrilled that you'd like to contribute to this project. Your help is essential for keeping it great.

Please note that this project is released with a [Contributor Code of Conduct][code-of-conduct]. By participating in this project you agree to abide by its terms.

## Issues and PRs

If you have suggestions for how this project could be improved, or want to report a bug, open an issue! We'd love all and any contributions. If you have questions, too, we'd love to hear them.

We'd also love PRs. If you're thinking of a large PR, we advise opening up an issue first to talk about it, though! Look at the links below if you're not sure how to open a PR.

## Submitting a pull request

1. [Fork][fork] and clone the repository.
2. Make sure the tests pass on your machine: `mkdir build && cd build && cmake .. -DSATURNITY_TESTS=ON && cmake --build . --target unit_test && ./unit_test`.
3. Create a new branch: `git checkout -b my-branch-name`.
4. Make your change, add tests, and make sure the tests still pass.
5. Make sure to use `clang-format-16` & `clang-tidy-16` to format your code.
6. Push to your fork and [submit a pull request][pr]. (Please make a good description of your PR)
7. Pat your self on the back and wait for your pull request to be reviewed and merged.
8. For a Pull Request to be merged:
    * CI workflow must succeed
    * A project member must review and approve it

Here are a few things you can do that will increase the likelihood of your pull request being accepted:

- Write and update tests.
- Keep your changes as focused as possible. If there are multiple changes you would like to make that are not dependent upon each other, consider submitting them as separate pull requests.
- Write a [good commit message](http://tbaggery.com/2008/04/19/a-note-about-git-commit-messages.html). (Follow gitmoji for commit messages.)

Work in Progress pull requests are also welcome to get feedback early on, or if there is something blocked you.

## Resources

- [How to Contribute to Open Source](https://opensource.guide/how-to-contribute/)
- [Using Pull Requests](https://help.github.com/articles/about-pull-requests/)
- [GitHub Help](https://help.github.com)