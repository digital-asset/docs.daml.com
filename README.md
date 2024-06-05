# docs.daml.com

This repo manages the [docs.daml.com](https://docs.daml.com) website.

In the `docs` folder you will find a folder for each version that is
supported by the docs team. Making changes to versions that are not in the docs
folder is not supported.

Whenever a PR is merged into this repo, the live docs website is updated
with the repo. This means that:

- Every version in the `docs` folder that has changed compared to what is
  currently on the website is rebuilt and pushed to the website.
- The root of the website is updated, if needed, to match the contents of the
  version pointed at by the `root` file.
- The dropdown on the website is modified to contain only the versions listed
  in the `dropdown_versions` file.

How to build (and work on) each version is documented in the corresponding
`docs/<version>README.md` file.

To change which version appears on the root of the website, make a PR that
changes the `root` file to the appropriate version number.

To change which versions appear in the dropdown on the website, change the
`dropdown_versions` file.

## Setting up this repo locally

### Prerequisites

* Install [direnv](https://github.com/direnv/direnv/blob/master/docs/installation.md) for the environment variables.
* Install the [Nix](https://nixos.org/download.html) package manager, multi-user option.

`direnv` and `Nix` will work together to provide you with an appropriate,
working environment for each version of the documentation.

:warning: Make sure you select Mac OS on the left menu for the correct Nix installation command.

* [JFrog access](https://digitalasset.jfrog.io/ui/admin/artifactory/user_profile)
  You need a JFrog account to access the build artifacts. Check you can see the `assembly` directory in the list of Artifacts. If you don't have it, ask `#org-security` for `readers` access.

### Clone the repo

Clone this repo and `cd` into it:

```zsh
git clone git@github.com:digital-asset/docs.daml.com.git
cd docs.daml.com
```

The first time you access the repo, run `direnv allow` as instructed. After that, and once your environment variables are set up properly, every time you switch to this repository - and, incidentally, all the others too - you will see output similar to the following:

```zsh
$ cd daml-projects/docs.daml.com
direnv: loading ~/daml-projects/docs.daml.com/.envrc
direnv: using nix
direnv: export +AR +AR_FOR_TARGET +ARTIFACTORY_USERNAME +ARTIFACTORY_PASSWORD ...
```

The bottom list is longer, but you must see `ARTIFACTORY_USERNAME` and `ARTIFACTORY_PASSWORD` in it.

:warning: The first time you do this, you won't see these variables, as you won't have had added them yet.

:warning: Don't be tempted to give up when `direnv` tells you it's taking a while. Be patient.

### Environment variables

Create or edit the `.envrc.private` file in the root directory to contain the following:

```plaintext
export ARTIFACTORY_USERNAME=firstname.lastname
export ARTIFACTORY_PASSWORD=Long_string_of_gibberish_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUV
```

- `ARTIFACTORY_USERNAME`:
  Find your username in [JFrog](https://digitalasset.jfrog.io/ui/admin/artifactory/user_profile); usually `firstname.lastname`.
- `ARTIFACTORY_PASSWORD`:
  This is your **API Key**, *NOT* your password. Find your API key at the bottom of **Authentication Settings** in [your JFrog profile](https://digitalasset.jfrog.io/ui/user_profile).

These credentials will be used by every version under the `docs` folder. You
only need to set them up once, at the top level of the repo.

> :warning: You need to have read access to the assembly repo on Artifactory.
> If you don't, please send an email to help@ to request access.

# Releases

When a new Daml Enterprise release is made, the documentation needs to be
updated accordingly. Because the root website (`https://docs.daml.com`) shows
the same content as the "current minor" (e.g. 2.8 as of 2024-05-28), we need to
discusse separately the cases where the new release is for the current minor
from the cases where the new release is for an older minor.

## New patch for previous minor

For a non-current minor, rename the corresponding folder, update the versions,
and update the `/dropdown_versions` file.

For example, if you are releasing Daml Enterprise 2.7.6 while the current minor
is `2.8`, you need to:

1. Rename the `docs/2.7.5` folder to `docs/2.7.6` (i.e. `git mv docs/2.7.5
   docs/2.7.6`).
2. Update the `2.7.5` line in `dropdown_versions` to say `2.7.6` instead.
3. Update the `docs/2.7.6/versions.json` file to say `2.7.6` where it used to
   say `2.7.5`.

## New patch for current minor

For the current minor, follow the same steps as in the previous section, with
one additional operation: udpate the `root` file to point to the new version.
For example, if you are publishing `2.8.6` when `2.8` is the current minor, you
should:

1. Rename the `docs/2.8.5` folder to `docs/2.8.6` (i.e. `git mv docs/2.8.5
   docs/2.8.6`).
2. Update the `2.8.5` line in `dropdown_versions` to say `2.8.6` instead. This
   should be the first line.
3. Update the `docs/2.8.6/versions.json` file to say `2.8.6` where it used to
   say `2.8.5`.
4. Update the `root` file to contain `2.8.6` instead of `2.8.5`.

## Publishing a new minor

To publish a new minor for which the folder already exists, add an entry to
`dropdown_versions` and, if relevant, update `root`.

## Creating a new minor

Creating a new minor is typically done by copying the previous one and updating
`versions.json`.

## Reindexing

When there is a change to the root website, the entire site needs to be reindexed for searching. This includes any time a new version of the docs is released. Until the reindexing is done, the site search engine may still bring up deleted and moved pages in search results. Then when a viewer clicks that search result, a 404 error is displayed. Google search will eventually catch up without intervention. Following are the steps to reindex the site search:

1. Log into SiteSearch360 (https://www.sitesearch360.com/).
2. At the bottom of the sidebar menu, select **Index**.
3. Scroll down to see a blue button and a red button.
4. Click the red button for **Empty Entire Index**. It takes a couple of minutes to process.
5. When that has completed, click the blue button for **Re-index All Configured Sources**. This may take about a half hour.
6. When this has completed, the site search should work as expected.

## Questions

If you have any questions or comments about these instructions, please reach out to the `#product-docs` channel, mentioning @Yves, on Slack.

Thank you :blush:
