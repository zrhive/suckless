{
  description = "suckless configuration that sucks less";

  inputs = {
    # self.submodules = true;
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs =
    { self, nixpkgs }:
    let
      eachSystem =
        function:
        nixpkgs.lib.genAttrs nixpkgs.lib.systems.flakeExposed (
          system: function nixpkgs.legacyPackages.${system}
        );
    in
    {
      nixosModules = {
        default = ./nix/modules/nixos.nix;
        suckless = self.nixosModules.default;
        flexipatch = {
          imports = [
            self.nixosModules.default
            (import ./nix/modules/common.nix { inherit self; })
          ];
        };
      };

      homeModules = {
        default = ./nix/modules/home.nix;
        suckless = self.homeModules.default;
        flexipatch = {
          imports = [
            self.homeModules.default
            (import ./nix/modules/common.nix { inherit self; })
          ];
        };
      };

      overlays = import ./nix/overlays.nix { inherit (self) packages; };
      packages = eachSystem (pkgs: import ./nix/packages.nix { inherit self pkgs; });
      devShells = eachSystem (pkgs: import ./nix/shell.nix { inherit self pkgs; });
      formatter = eachSystem (pkgs: pkgs.callPackage ./nix/formatter.nix { inherit self; });
    };
}
