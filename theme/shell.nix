let
  pkgs = import ./nix/nixpkgs.nix;
in
pkgs.mkShell {
  buildInputs = with pkgs; [
    bash
    curl
    jq
    nodejs-18_x
    ruby
    sass
  ];
}
