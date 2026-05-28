{
  description = "suckless configuration that sucks less";

  inputs = {
    self.submodules = true;
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  };

  outputs = { self, nixpkgs }: let
    suckless = import ./.;
    util = import ./nix/lib.nix;

    inherit (nixpkgs) lib;
    systems = lib.systems.flakeExposed;
    eachSystem = f: lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
  in
  {
    nixosModules = {
      default = ./nix/nixos.nix { inherit self; };
      flexipatch = {
        imports = [ self.nixosModules.default ];
        suckless.tools = {
          dwm.enable = true;
          slstatus.enable = true;
          dmenu.enable = true;
          st.enable = true;
        };
      };
    };

    homeModules = {
      default = ./nix/home.nix { inherit self; };
      flexipatch = {
        imports = [ self.homeModules.default ];
        suckless.tools = {
          dwm.enable = true;
          slstatus.enable = true;
          dmenu.enable = true;
          st.enable = true;
        };
      };
    };

    packages = eachSystem (pkgs: import ./nix/package.nix { inherit self pkgs; }
      // {
        test = {
          dmenu = (pkgs.dmenu.overrideAttrs { src = "${self}/flexipatch/dmenu"; }).override {};
        };
      }
    );

    overlays.default = final: prev: let
      packages = import ./nix/package.nix { pkgs = final; };
    in { inherit (packages) suckless flexipatch; };

    devShell = eachSystem (pkgs: pkgs.mkShell {
      packages = [ pkgs.nixfmt pkgs.statix pkgs.deadnix ];
    });
  };
}
