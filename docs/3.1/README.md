### Live preview

Run the `live-preview` script to render a local view of the site.

```zsh
live-preview
```

Note that the `live-preview` script takes a few shortcuts. This is fine most of the time, but sometimes the final result can be a bit different.

### Theme

Live preview doesn't reflect changes to the theme. That's because it would
require a full recompilation of the site, which is long and defeats the purpose
of live preview. This makes it impossible to quickly iterate on the theme.

As an alternative, you can run live-preview with theme reload on a small subset
of the site, as described in [the theme's README](../../theme/README.md).

### Full build

To build the PDF docs or the exact HTML files that we publish to [docs.daml.com](https://docs.daml.com), run the full build locally:

```zsh
./bin/build
```

The HTML files are in `workdir/build/sphinx-target/html`; you can view them
by doing something like:

```zsh
$ cd workdir/build/sphinx-target/html
$ python -m http.server 8000 --bind 127.0.0.1
```

Then pointing your web browser to [http://localhost:8000](http://localhost:8000).

### Dependencies

The `versions.json` file in this folder defines the dependencies used by this version of the docs.
For example:

   ```json
   {
     "daml": "2.6.0-snapshot.20230123.11292.0.b3f84bfc",
     "canton": "20230124",
     "daml_finance": "1.0.4",
     "canton_drivers": "0.1.9"
   }
   ```

To update the `versions.json` file to the latest snapshots, run the following (in this folder):

   ```sh
   ./bin/bump
   ```

   The `daml_finance` version is independent of the actual SDK version and is set/updated by the
   financial engineering team. This version is used to source an assembly artifact from
   [jfrog](https://digitalasset.jfrog.io/ui/repos/tree/General/assembly/daml-finance). The purpose
   of having an independent version number is to allow the release of new assembly versions without
   waiting for a new SDK release.
