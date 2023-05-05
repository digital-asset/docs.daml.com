# docs.daml.com

## Building locally

When working on the documentation, you'll want to see the results of your work
locally before opening a pull request.

To do that, switch to the `docs` directory in the repository:

```
cd docs
```

To build the docs you need to know the corresponding Daml SDK Canton
releases you want to build the documentation for. You can find the
version used by CI in the `LATEST` file.

With that version, you can then download the docs of Canton and the
Daml repo using the following commands:

```
mkdir download
./download.sh <sdkversion> <cantonversion> download
```

## Preview

For local development, you usually are best served with the live
preview script. This will generate a `build` directory and any changes
in that directory will be picked up directly without having to restart
the web server. Do keep in mind though that you have to mirror the
changes you make to the Daml & Canton repos once you are happy with
them. Only changes to the top-level `index.rst` files can be made
directly in this repository.

```
./live-preview.sh <sdkversion> <cantonversion> download
```

## Full build

If you want to view the PDF docs or the exact HTML files that we
publish to https://docs.daml.com, you can also run the full build
locally:

```
mkdir docs_output
./build.sh <sdkversion> <cantonversion> download docs_output
```

This leaves you with two files:

```
$ ls docs_output
html-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.tar.gz
pdf-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.pdf
$
```

To view the html docs, extract them and launch a webserver, e.g. via Python and
point your browser at `http://localhost:8000`

```
tar xf docs_output/html-docs-2.0.0-snapshot.20211220.8736.0.040f1a93.tar.gz
cd html
python3 -m http.server 8000 --bind 127.0.0.1
```
