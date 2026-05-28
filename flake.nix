{
  description = "suckless configuration that sucks less";

  inputs = {
    self.submodules = true;
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
    inherit (nixpkgs) lib;
    systems = lib.systems.flakeExposed;
    eachSystem = f: lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
  in
  {
    nixosModules = {
      default = ./nix/nixos.nix;
      suckless = self.nixosModules.default;
      flexipatch = self.nixosModules.default // ./nix/common.nix { inherit self; };
    };

    homeModules = {
      default = ./nix/home.nix;
      suckless = self.homeModules.default;
      flexipatch = self.homeModules.default // ./nix/common.nix { inherit self; };
    };

    packages = eachSystem (pkgs: import ./nix/packages.nix { inherit self pkgs; }
      // {
        test = {
          dmenu = (pkgs.dmenu.overrideAttrs { src = "${self}/flexipatch/dmenu"; }).override {};
        };
      }
    );

    overlays.default = final: _prev: {
      # inherit (import ./nix/packages.nix { pkgs = final; }) suckless flexipatch;
      inherit (self.packages.${final.stdenv.hostPlatform.system}) suckless flexipatch;
    };

    devShell = eachSystem (pkgs: pkgs.mkShell {
      packages = [ pkgs.nixfmt pkgs.statix pkgs.deadnix ];
    });
  };
}
