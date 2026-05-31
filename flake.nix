{
  description = "suckless configuration that sucks less";

  inputs = {
    self.submodules = true;
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      inherit (nixpkgs) lib;
      systems = lib.systems.flakeExposed;
      eachSystem = f: lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      nixosModules = {
        default = ./nix/modules/nixos.nix;
        suckless = self.nixosModules.default;
        flexipatch = self.nixosModules.default // ./nix/common.nix { inherit self; };
      };

      homeModules = {
        default = ./nix/modules/home.nix;
        suckless = self.homeModules.default;
        flexipatch = self.homeModules.default // ./nix/common.nix { inherit self; };
      };

      overlays.default = final: _prev: {
        inherit (self.packages.${final.stdenv.hostPlatform.system}) suckless flexipatch;
      };

      packages = eachSystem (pkgs: import ./nix/packages.nix { inherit self pkgs; });

      formatter = eachSystem (pkgs: pkgs.callPackage ./nix/formatter.nix { inherit self; });

      devShell = eachSystem (pkgs: pkgs.callPackage ./nix/shell.nix { inherit self; });
    };
}
