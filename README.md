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
  You need a JFrog account for accessing the build artifacts. Check you can see the `assembly` directory in the list of Artifacts. If you don't have it, ask `#org-security` for `readers` access.

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

The bottom list is longer, but it is important that you see `ARTIFACTORY_USERNAME` and `ARTIFACTORY_PASSWORD` in it.

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
  This is your **API Key**, *NOT* your password. Find your API key at the bottom of **Authentication Settings** in your profile.

These credentials will be used by every version under the `docs` folder. You
only need to set them up once, at the top-level of the repo.
