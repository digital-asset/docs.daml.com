let
  pkgs = import ./nix/nixpkgs.nix;
in
pkgs.mkShell {
  SSL_CERT_FILE = "${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt";
  NODE_EXTRA_CA_CERTS = "${pkgs.cacert}/etc/ssl/certs/ca-bundle.crt";
  buildInputs = with pkgs; [
    bash
    curl
    jq
    nodejs-18_x
  ];
}
