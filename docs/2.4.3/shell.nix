let
  pkgs = import (import ./nix/sources.nix).nixpkgs {};
  sphinx-copybutton = pkgs.python3Packages.buildPythonPackage rec {
      pname = "sphinx-copybutton";
      version = "0.2.12";

      src = pkgs.python3Packages.fetchPypi {
        inherit pname version;
        sha256 = "0p1yls8pplfg59wzmb96m3pjcyr3202an1rcr5wn2jwqhqvqi4ll";
      };
      doCheck = false;
      buildInputs = [pkgs.python3Packages.sphinx];
  };
  sphinx-exts = pkgs.python3Packages.sphinx.overridePythonAttrs (attrs: rec {
    propagatedBuildInputs = attrs.propagatedBuildInputs ++ [sphinx-copybutton];
  });
  texlive = pkgs.texlive.combine {
    inherit (pkgs.texlive)
      bera
      capt-of
      collection-fontsrecommended
      collection-luatex
      datetime
      enumitem
      environ
      epigraph
      eqparbox
      eulervm
      fancyhdr
      fmtcount
      fncychap
      footmisc
      footnotebackref
      framed
      latexmk
      lipsum
      mathpartir
      mathpazo
      mnsymbol
      multirow
      needspace
      palatino
      scheme-small
      tabulary
      threeparttable
      tikzsymbols
      titlesec
      tocbibind
      todonotes
      transparent
      trimspaces
      varwidth
      wrapfig
      xargs
    ;
  };
in
pkgs.mkShell {
  LOCALE_ARCHIVE_2_27 = if pkgs.stdenv.hostPlatform.libc == "glibc"
                        then "${pkgs.glibcLocales}/lib/locale/locale-archive"
                        else null;
  SSL_CERT_FILE = "${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt";
  buildInputs = [
    pkgs.awscli
    pkgs.bash
    pkgs.curl
    pkgs.git
    pkgs.jq
    pkgs.imagemagick
    sphinx-exts
    texlive
    pkgs.pipenv
    pkgs.python39
    pkgs.nix
  ];
}
