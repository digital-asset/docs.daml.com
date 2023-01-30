let
  pkgs = import ./nix/nixpkgs.nix;
in
pkgs.mkShell {
  SSL_CERT_FILE = "${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt";
  buildInputs = with pkgs; [
    awscli
    bash
    curl
    jq
    git
    nix
  ];
}
