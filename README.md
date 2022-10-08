# docs.daml.com

First time here? Look at the [Setup](#setup) section below.

## Aspiration

This repo should be in charge of everything that appears on
https://docs.daml.com.

Long-term:

- Most human-written documentation should be in this repo, to ease its
  maintenance and development.
- This repo should, to the extent possible, test code snippets & samples _using
  the corresponding published artifacts_ (e.g. the 2.0.0 compiler for the 2.0.0
  docs).
- It is not yet clear exactly how we want to manage multiple versions of the
  docs (that is, how to maintain the ability to change and evolve past
  versions). This will mostly depend on team preferences.

This repo is explicitly ignoring any pre-2.0.0 docs; those will still be
published using their existing release process.

## Current state (2022-04-21)

Every commit to `main` publishes to a versioned prefix on the S3 repo (e.g.
`/2.1.0`). How to handle `/` and multiple versions are still up for debate, and
thus still follow the preexisting process: the daml repo [cron] copies
over a versioned folder to root on stable release publication.

[cron]: https://github.com/digital-asset/daml/blob/main/ci/cron/src/Docs.hs

Documentation itself is still mostly hosted in the daml and canton repos. We
seem to have a green light on moving the daml one, so that should happen soon.

## Making changes to the documentation

### Making changes to the next, unreleased version
1. Make the changes to the docs files in the [damlRepo] or the [Canton] repo, include in a PR and merge into main
2. Take a snapshot that the PR is included in (snapshots are created each night so the first snapshot that PR is included in will likely be the next day)
3. In the [damlDocs] repo, update the LATEST file to include the snapshot version which includes the changed PR & make sure that the 'prefix' value points to the release that you want to target e.g. '2.1.0' or 2.2.0' etc.
4. Create a PR to update the LATEST file & merge it into the main branch.
5. When the new version ('2.1.0' or 2.2.0' etc.) is built it will pull all of the docs changes submitted for that prefix.

### Making changes to the current version, or past versions *from 2.0.0 onwards*
1. Branch the version of the release that you want to change in the Daml or Canton repo (link to each will be included), include in a PR and merge back into that version release
2. Ask on the #team-daml Slack channel, mentioning @gary, for someone to help you manually create a snapshot
3. In the [damlDocs] repo, update the LATEST file to include the snapshot version which includes the changed PR & make sure that the 'prefix' value points to the release that you want to target e.g. '2.0.0'
4. Create a PR to update the LATEST file & merge it into the branch for that release (branches do not exist yet as of 30th March 2022)
5. The pages will update automatically once that snapshot is created

[damlRepo]: https://github.com/digital-asset/daml
[damlDocs]: https://github.com/digital-asset/docs.daml.com
[Canton]: https://github.com/DACH-NY/canton


## Making a release

Changes to `main` are immediately reflected on the live (versioned) website.
The `LATEST` file contains a `prefix` entry, and the result of building `main`
is automatically pushed under that prefix.

For example, if `LATEST` looks like:

```json
{
  "daml": "2.1.0-snapshot.20220311.9514.0.ab6e085f",
  "canton": "20220315",
  "prefix": "2.1.0"
}
```

then the result of building the documentation based on SDK
`2.1.0-snapshot.20220311.9514.0.ab6e085f` and Canton `20220315` will be pushed
to https://docs.daml.com/2.1.0, and should be live "immediately" (the build &
push process takes about 10 minutes).

Note that at this point the release process pushes the new files, overwriting
existing ones, but does not at the moment delete anything (i.e. if a file no
longer exists in a new version, there will still be a copy of the old version
of that file).

## Building locally

When working on the documentation, you'll want to see the results of your work
locally before opening a pull request.

To do that, switch to the `docs` directory in the repository:

```
cd docs
```

Download the documentation tarballs from the daml and canton repos:

```
./download.sh
```

## Preview

For local development, use the `live-preview.sh` script. The files for the
unified documentation will be in the `docs/workdir/build` folder; changes to
those files should be immediately reflected.

Remember that once you are happy with your changes, you have to
mirror them as PRs on the daml/canton repositories.

Only changes to the top-level `index.rst` files can be made directly in this
repository.

```
./live-preview.sh
```

## Full build

To view the PDF docs or the exact HTML files that we publish to
[docs.daml.com](https://docs.daml.com), you can also run the full build
locally:

```
mkdir docs_output
./build.sh
```

This leaves you with two files:

```
$ ls docs/workdir/target
html-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.tar.gz
pdf-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.pdf
$
```

To view the html docs, extract them and launch a webserver, e.g. via Python and
point your browser at `http://localhost:8000`

```
tar xf docs/workdir/target/html-docs-$(jq -r '.daml' LATEST).tar.gz
cd html
python3 -m http.server 8000 --bind 127.0.0.1
```

## Setup

### direnv

This repo assumes the use of [direnv] for local development, along with a
working [Nix] installation. In particular, the `.envrc.private` file can be
used to set the following environment variables:

[direnv]: https://github.com/direnv/direnv
[Nix]: https://nixos.org/download.html

- `ARTIFACTORY_USERNAME`: Required to access intermediate build artifacts. You
  can find your username by navigating to [your Artifactory profile
  page][artifactory] and copying the name that follows the "User Profile:" marker
  in the top left (usually firstname.lastname).
- `ARTIFACTORY_PASSWORD`: Required to access intermediate build artifacts.
  Despite the name, this is actually your Identity Token, **not** your password. You
  can generate your Identity Token on [your Artifactory profile page][artifactory], as the
  first field under "Authentication Settings".

Create .envrc.private file at the root (make sure it is ignored in .gitignore), it should look like:

```
export ARTIFACTORY_USERNAME=fist.last
export ARTIFACTORY_PASSWORD=Reference Token of Identity Token
```

If you have any trouble with Artifactory authentication, please ask on Slack in
`#org-security`. Every employee should have a working Artifactory account, with
read access to the appropriate repos. Specifically, do check that you can see
the `assembly` repo in the Artifactory UI, and ask for `readers` access if you
can't.

[artifactory]: https://digitalasset.jfrog.io/ui/admin/artifactory/user_profile

### Cloning the repo

Once you have installed direnv and nix, you can clone the repo and switch to it:

```
git clone git@github.com:digital-asset/docs.daml.com.git
cd assembly
```

If you setup direnv correctly, the first time you do this you will be
asked to run `direnv allow` so do exactly that.

After that every time you switch to the repository, you will see output similar to the following:

```
$ cd daml-projects/docs.daml.com
direnv: loading ~/daml-projects/docs.daml.com/.envrc
direnv: using nix
direnv: export +AR +AR_FOR_TARGET +AS +AS_FOR_TARGET +CC +CC_FOR_TARGET +CONFIG_SHELL +CXX +CXX_FOR_TARGET +DETERMINISTIC_BUILD +HOST_PATH +IN_NIX_SHELL +JAVA_HOME +LD +LD_FOR_TARGET +LOCALE_ARCHIVE_2_27 +NIX_BINTOOLS +NIX_BINTOOLS_FOR_TARGET +NIX_BINTOOLS_WRAPPER_TARGET_HOST_x86_64_unknown_linux_gnu +NIX_BINTOOLS_WRAPPER_TARGET_TARGET_x86_64_unknown_linux_gnu +NIX_BUILD_CORES +NIX_BUILD_TOP +NIX_CC +NIX_CC_FOR_TARGET +NIX_CC_WRAPPER_TARGET_HOST_x86_64_unknown_linux_gnu +NIX_CC_WRAPPER_TARGET_TARGET_x86_64_unknown_linux_gnu +NIX_CFLAGS_COMPILE +NIX_CFLAGS_COMPILE_FOR_TARGET +NIX_ENFORCE_NO_NATIVE +NIX_HARDENING_ENABLE +NIX_INDENT_MAKE +NIX_LDFLAGS +NIX_LDFLAGS_FOR_TARGET +NIX_STORE +NM +NM_FOR_TARGET +OBJCOPY +OBJCOPY_FOR_TARGET +OBJDUMP +OBJDUMP_FOR_TARGET +PYTHONHASHSEED +PYTHONNOUSERSITE +PYTHONPATH +RANLIB +RANLIB_FOR_TARGET +READELF +READELF_FOR_TARGET +SIZE +SIZE_FOR_TARGET +SOURCE_DATE_EPOCH +SSL_CERT_FILE +STRINGS +STRINGS_FOR_TARGET +STRIP +STRIP_FOR_TARGET +TEMP +TEMPDIR +TMP +TMPDIR +_PYTHON_HOST_PLATFORM +_PYTHON_SYSCONFIGDATA_NAME +buildInputs +builder +configureFlags +depsBuildBuild +depsBuildBuildPropagated +depsBuildTarget +depsBuildTargetPropagated +depsHostHost +depsHostHostPropagated +depsTargetTarget +depsTargetTargetPropagated +doCheck +doInstallCheck +name +nativeBuildInputs +nobuildPhase +out +outputs +patches +phases +propagatedBuildInputs +propagatedNativeBuildInputs +shell +shellHook +stdenv +strictDeps +system ~PATH ~XDG_DATA_DIRS
```

If you encounter any issues ask in #team-daml on Slack.
