{
  description = "suckless configuration that sucks less";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      suckless = import ./.;

      lib = nixpkgs.lib;
      systems = lib.systems.flakeExposed;
      eachSystem = f: lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      nixosModules = {
        default = suckless.module;

        suckless = {
          imports = [ self.nixosModules.default ];
          nixpkgs.overlays = [ self.overlays.default ];
          suckless = {
            dwm = lib.mkDefault true;
            slstatus = lib.mkDefault true;
            dmenu = lib.mkDefault true;
            st = lib.mkDefault true;
          };
        };
      };

      overlays.default = _: prev: suckless.packages { pkgs = prev; };
      packages = eachSystem (pkgs: suckless.packages { inherit pkgs; });

      devShells = eachSystem (pkgs: {
        default = pkgs.mkShell {
          packages = builtins.attrValues { inherit (pkgs) git nixfmt; };
        };
      });
    };
}
