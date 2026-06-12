{
  description = "suckless configuration that sucks less";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

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
      packages = eachSystem (pkgs: import ./nix/packages.nix { inherit self pkgs; });

      nixosModules = {
        default = ./nix/modules/nixos.nix;
        suckless = self.nixosModules.default;
        flexipatch = {
          imports = [
            self.nixosModules.default
            (import ./nix/modules { inherit self; })
          ];
        };
      };

      homeModules = {
        default = ./nix/modules/home.nix;
        suckless = self.homeModules.default;
        flexipatch = {
          imports = [
            self.homeModules.default
            (import ./nix/modules { inherit self; })
          ];
        };
      };

      overlays.default =
        final: _:
        let
          packages = final: self.packages.${final.stdenv.hostPlatform.system};
        in
        {
          dmenu = (packages final).flexipatch-dmenu;
          dwm = (packages final).flexipatch-dwm;
          st = (packages final).flexipatch-st;
          slstatus = (packages final).suckless-slstatus;
        };

      formatter = eachSystem (pkgs: pkgs.callPackage ./nix/formatter.nix { inherit self; });

      devShells = eachSystem (pkgs: {
        default = pkgs.mkShellNoCC {
          packages = self.formatter.${pkgs.stdenv.hostPlatform.system}.runtimeInputs;
        };
      });
    };
}
