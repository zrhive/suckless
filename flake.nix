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
        flexipatch = {
          imports = [
            self.nixosModules.default
            (./nix/modules/common.nix { inherit self; })
          ];
        };
      };

      homeModules = {
        default = ./nix/modules/home.nix;
        suckless = self.homeModules.default;
        flexipatch = {
          imports = [
            self.homeModules.default
            (./nix/modules/common.nix { inherit self; })
          ];
        };
      };

      overlays = import ./nix/overlays.nix { inherit (self) packages; };
      packages = eachSystem (
        pkgs:
        import ./nix/packages.nix { inherit self pkgs; }
        // {
          test = (pkgs.dwm.overrideAttrs { src = ./flexipatch/dwm; }).override { };
        }
      );

      formatter = eachSystem (pkgs: pkgs.callPackage ./nix/formatter.nix { inherit self; });
      devShells = eachSystem (pkgs: import ./nix/shell.nix { inherit self pkgs; });
    };
}
