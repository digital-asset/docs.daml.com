# docs.daml.com

This repo manages the full build of technical documentation into https://docs.daml.com from the following repos:

* Daml docs: https://github.com/digital-asset/daml/tree/main/docs
* Canton docs: https://github.com/DACH-NY/canton/tree/main/docs

:bulb: Docs in this repo build the main TOC with pointers to pages from the above repos.

The process for updating the docs TOCs has some potential pitfalls. Follow the instructions in this README *carefully* and in order.

- [Setting up this repo locally](https://github.com/digital-asset/docs.daml.com#setting-up-this-repo-locally)
- [Build and view the docs locally](https://github.com/digital-asset/docs.daml.com#build-and-view-the-docs-locally)
- [How to commit changes to the docs](https://github.com/digital-asset/docs.daml.com#how-to-update-the-docs)

:arrow_right: If you encounter any issues, reach out to #team-daml on Slack.

## Setting up this repo locally

### Prerequisites

* Install [direnv](https://github.com/direnv/direnv/blob/master/docs/installation.md) for the environment variables.
* Install the [Nix](https://nixos.org/download.html) package manager, multi-user option. 

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

## Build and view the docs locally

`cd` to the `docs` directory in the repository:

```zsh
cd docs
```

### Download docs

Run the following script to download the documentation tarballs from the Daml and Canton repos:

```zsh
./download.sh
```

### Live preview

Run the `live-preview.sh` script to render a local view of the site. The html files are in `docs/workdir/build`. Rerun the script to view any edits to `docs/index/` files.

:warning: If you make changes to docs managed by the other repos, you have to commit them there. You can only make changes to the top-level `index.rst` files, containing the master TOC, that live in this repository. 

:warning: If you do make a change to the TOCs in this repo, you then have to duplicate the change in the relevant satellite repo.

```zsh
./live-preview.sh
```

### Full build

To build the PDF docs or the exact HTML files that we publish to [docs.daml.com](https://docs.daml.com), run the full build locally:

```zsh
./build.sh
```

This produces the following:

```zsh
$ ls docs/workdir/target
html-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.tar.gz
pdf-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.pdf
$
```

To view the html docs, extract them and launch a webserver, e.g. via Python, and point your browser at `http://localhost:8000`.

```zsh
tar xf docs/workdir/target/html-docs- # then tab to pick up the file name
cd html
python3 -m http.server 8000 --bind 127.0.0.1
```

## How to commit changes to the docs

:warning: This repo ignores any pre-2.0.0 docs; those will still be published using their existing release process. It is unlikely you will come across this. If you do, reach out to #team-daml.

Every commit to `main` in this repo publishes to a versioned prefix on the S3 repo (e.g. `/2.1.0`).

### Making changes to the next, unreleased version

1. Make the changes to docs in the Daml or Canton repo, create a PR, and merge into main.

:warning: You will have to set up and build the repo you are working on before making changes and viewing locally. Make sure you follow the build instructions carefully as they may differ to here.

2. A snapshot is generated every 24 hours that includes the PR.
3. To get the snapshot details, run the `deps` tool from the root.

```zsh
deps list daml # lists daml snapshots
deps list canton # lists canton snapshots
deps use <canton-version> # tells you about the dependency between canton and daml
```

For example:

```zsh
% deps list daml
2.0.0
2.0.0-snapshot.20220117.8897.0.36a93ef0
2.0.0-snapshot.20220119.8939.0.ebd3827c
2.0.0-snapshot.20220124.8981.0.a150737d
```

```zsh
% deps list canton
1.0.0-20220207
1.0.0-rc7
1.0.0-rc8
1.0.0-snapshot.20220126
1.0.0-snapshot.20220128
```

4. Update the `LATEST` file to include the snapshot version containing the changed PR. 

```json
{
  "daml": "2.1.0-snapshot.20220311.9514.0.ab6e085f",
  "canton": "20220315",
  "prefix": "2.1.0"
}
```

5. Create a PR to update the `LATEST` file and merge it into the main branch.

6. Changes to `main` are reflected immediately on the live (versioned) website. When a new or updated version is built it pulls all of the docs changes submitted for that prefix. For example, the url resulting from building the documentation based on the `LATEST` file above is https://docs.daml.com/2.1.0.

:warning: The release process pushes new files, overwriting existing ones, but does not at the moment delete anything; i.e. if a file no longer exists in a new version, there will still be a copy of the old version of that file.

### Making changes to current or past versions *from 2.0.0 onwards*

1. Follow step 1 as above.
2. You will have to ask on the #team-daml Slack channel, mentioning @gary, for someone to help you manually create a snapshot.
3. Follow the rest of the steps as above.

## Questions

If you have any questions or comments about these instructions, please reach out to the #product-docs team/@katharine on Slack.

Thank you :blush: