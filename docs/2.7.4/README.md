# Working on the documentation

This folder manages the full build of technical documentation from the following repos:

* [Daml docs](https://github.com/digital-asset/daml/tree/main/docs)
* [Canton docs](https://github.com/DACH-NY/canton/tree/main/docs)
* [Daml-Finance docs](https://github.com/digital-asset/daml-finance/tree/main/docs)

:bulb: Docs in this repo build the main TOC with pointers to pages from the above repos.

The process for updating the docs TOCs has some potential pitfalls. Follow the instructions in the main README *carefully* and in order.

- [Setting up this repo locally](https://github.com/digital-asset/docs.daml.com#setting-up-this-repo-locally)
- [Build and view the docs locally](#live-preview)
- [How to commit changes to the docs](#how-to-commit-changes-to-the-docs)

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

## How to commit changes to this version of the docs

1. Make the changes to docs in the Daml, Daml Finance, or Canton repo, create a PR, and merge into main.

:warning: You will have to set up and build the repo you are working on before making changes and viewing locally. Make sure you follow the build instructions carefully as they may differ to here.

2. For Daml and Canton, a snapshot is generated every 24 hours that includes the PR.
3. The `versions.json` file in this folder defines the dependencies used by this version of the docs:

```json
{
  "daml": "2.6.0-snapshot.20230123.11292.0.b3f84bfc",
  "canton": "20230124",
  "daml_finance": "1.0.4",
  "canton_drivers": "0.1.9"
}
```

4. To update the `versions.json` file to the latest snapshots, run the following (in this folder):

```sh
bump
```

:information_desk_person: DEPRECATED: For interested parties, the `deps` function renders a list of recent snapshot updates with the latest at the end of the list. Run `deps list daml` or `deps list canton` to see them.

5. Changes to `main` are reflected immediately on the live (versioned) website. When a new or updated version is built it pulls all of the docs changes submitted for each prefix (version). For example, the url resulting from building the documentation in the `docs/2.7.0` folder is https://docs.daml.com/2.7.0.
