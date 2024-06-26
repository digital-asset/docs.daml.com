### Live preview

Run the `live-preview` script to render a local view of the site.

```zsh
bin/live-preview
```

Note that the `live-preview` script takes a few shortcuts. This is fine most of the time, but sometimes the final result can be a bit different.

### Full build

To build the PDF docs or the exact HTML files that we publish to [docs.daml.com](https://docs.daml.com), run the full build locally:

```zsh
bin/build
```

The HTML files are in `workdir/build/sphinx-target/html`; you can view them by doing something like:

```zsh
$ cd workdir/build/sphinx-target/html
$ python -m http.server 8000 --bind 127.0.0.1
```

Then pointing your web browser to [http://localhost:8000](http://localhost:8000).

### Dependencies

The `versions.json` file in this folder defines the dependencies used by this version of the docs. For example:

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
bin/bump
```
