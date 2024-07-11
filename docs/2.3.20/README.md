# docs.daml.com

This is an old version. Make changes only as necessary.

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

### Theme

Live preview doesn't reflect changes to the theme. That's because it would
require a full recompilation of the site, which is long and defeats the purpose
of live preview. This makes it impossible to quickly iterate on the theme.

As an alternative, you can run live-preview with theme reload on a small subset
of the site, as described in [the theme's README](../../theme/README.md).

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
