let
  pkgs = import ./nix/nixpkgs.nix;
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
  SSL_CERT_FILE = "${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt";
  NODE_EXTRA_CA_CERTS = "${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt";
  buildInputs = with pkgs; [
    awscli
    bash
    curl
    git
    imagemagick
    jq
    nodejs-18_x
    openssh
    pipenv
    python39
    ruby
    sass
    texlive
  ];
}
