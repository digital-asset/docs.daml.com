# Working on the documentation

This folder manages the full build of technical documentation from the following repos:

* [Daml docs](https://github.com/digital-asset/daml/tree/main/docs)
* [Canton docs](https://github.com/DACH-NY/canton/tree/main/docs)
* [Daml-Finance docs](https://github.com/digital-asset/daml-finance/tree/main/docs)

:bulb: Docs in this repo build the main TOC with pointers to pages from the above repos.

The process for updating the docs TOCs has some potential pitfalls. Follow the instructions in the main README *carefully* and in order.

- [Setting up this repo locally](https://github.com/digital-asset/docs.daml.com#setting-up-this-repo-locally)
- [Build and view the docs locally](https://github.com/digital-asset/docs/2.6.0/README.md#live-preview)
- [How to commit changes to the docs](https://github.com/digital-asset/docs/2.6.0/README.md#how-to-commit-changes-to-the-docs)

:arrow_right: If you encounter any issues, reach out to #product-docs on Slack.

## Live preview

Run the `live-preview` script to render a local view of the site.

```zsh
live-preview
```

The html files are in `workdir/build/gen`. Rerun the script to view any edits to `docs/` files or the top-level ToC (`_toc.yml`).

:warning: If you make changes to docs managed by the other repos, you have to commit them there. In this repository, you can only make changes to the top-level ToC (`_toc.yml`) or some section introduction pages in the `docs` folder.

:warning: If you do make a change to the TOCs in this repo, you then have to duplicate the change in the relevant satellite repo (except for the daml repo, which does not have a local ToC).

### Full build

To build the PDF docs or the exact HTML files that we publish to [docs.daml.com](https://docs.daml.com), run the full build locally:

```zsh
build
```

The HTML files will be in `workdir/build/sphinx-target/html`; you can view them
by doing something like:

```zsh
$ cd workdir/build/sphinx-target/html
$ python -m http.server 8000 --bind 127.0.0.1
```

Then pointing your web browser to [http://localhost:8000](http://localhost:8000).

It also produces a PDF, and a tarball containing all of the HTML, under `workdir/target`.

## How to commit changes to the docs

:warning: This repo ignores any pre-2.0.0 docs; those will still be published using their existing release process. It is unlikely you will come across this. If you do, reach out to #team-daml.

Every commit to `main` in this repo publishes to a versioned prefix on the S3 repo (e.g. `/2.1.0`), specified under the `prefix` key in the `versions.json` file.

### Making changes to the next, unreleased version

1. Make the changes to docs in the Daml, Daml Finance, or Canton repo, create a PR, and merge into main.

:warning: You will have to set up and build the repo you are working on before making changes and viewing locally. Make sure you follow the build instructions carefully as they may differ to here.

2. For Daml and Canton, a snapshot is generated every 24 hours that includes the PR.
3. The `versions.json` file in the root defines the current snapshot rendering on live.

```json
{
  "daml": "2.1.0-snapshot.20220311.9514.0.ab6e085f",
  "canton": "20220315",
  "daml_finance": "1.0.4",
  "prefix": "2.1.0"
}
```

4. To update the `versions.json` file to the latest snapshots, run the following:

```sh
bump
```

:information_desk_person: DEPRECATED: For interested parties, the `deps` function renders a list of recent snapshot updates with the latest at the end of the list. Run `deps list daml` or `deps list canton` to see them.

5. Changes to `main` are reflected immediately on the live (versioned) website. When a new or updated version is built it pulls all of the docs changes submitted for that prefix. For example, the url resulting from building the documentation based on the `versions.json` file above is https://docs.daml.com/2.1.0.

:loudspeaker: Although `versions.json` should reflect the latest unreleased doc versions, around release time it may not. At these times, make sure you know which release you want your change to go into; i.e. the current unreleased (staging) version or the current unreleased (non-staging-yet) future version, it is probably the former which means going through the backporting exercise described in the next section.

### Making changes to current or past versions *from 2.0.0 onwards*

1. Follow step 1 as above; unless there is a good reason to *only* make the change in the older version.

2. Once you have pushed to main, look at the end of the PR for the resulting short commit hash. For example, in the case of `katmurp merged commit b3efb02 into main`, the short commit reference is `b3efb02`.

3. Get the release branch name you want to target from the relevant docs repo. For example, `release/2.5.x`.

4. Check there are no local changes with `git status`, then:

```zsh
git checkout release/2.5.x
git checkout -b backport-docs-fix
git cherry-pick b3efb02
git push
```

5. Ask on the `#team-daml` Slack channel, mentioning @gary, for someone to help you manually create a snapshot. They will take it from there.

### For each docs release

When there is a change to the root website, the entire site needs to be reindexed for searching. This includes any time a new version of the docs is released. Until the reindexing is done, the site search engine may still bring up deleted and moved pages in search results. Then when a viewer clicks that search result, a 404 error is displayed. Google search will eventually catch up without intervention. Following are the steps to reindex the site search:

1. Log into SiteSearch360 (https://www.sitesearch360.com/).
2. At the bottom of the sidebar menu, select **Index**.
3. Scroll down to see a blue button and a red button.
4. Click the red button for **Empty Entire Index**. It take a couple of minutes to process.
5. When that has completed, click the blue button for **Re-index All Configured Sources**. This may take about a half hour.
6. When this has completed, the site search should work as expected.

## Questions

If you have any questions or comments about these instructions, please reach out to the `#product-docs` channel and/or @katharine/@gary on Slack.

Thank you :blush:
