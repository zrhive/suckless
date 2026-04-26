{
  description = "suckless configuration that sucks less";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs =
    { nixpkgs }:
    let
      systems = [ "x86_64-linux" ];
      eachSystem = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      nixosModules = {
        default = import ./.;
        suckless = import ./suckless.nix;
      };

      devShells = eachSystem (pkgs: {
        default = pkgs.mkShell {
          buildInputs = builtins.attrValues {
            inherit (pkgs)
              nixfmt

              gcc
              pkg-config
              libx11
              ;
          };
        };
      });
    };
}
