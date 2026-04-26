{
  description = "suckless configuration that sucks less";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { nixpkgs }:
    let
      systems = [ "x86_64-linux" ];
      eachSystem = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      nixosModules = {
        default = import ./.;
        suckless =
          { lib, ... }:
          {
            imports = [ ./. ];
            suckless =
              let
                inherit (lib) mkDefault;
              in
              {
                dwm = mkDefault true;
                slstatus = mkDefault true;
                dmenu = mkDefault true;
                st = mkDefault true;
              };
          };
      };

      overlays.default = _: prev: {
        dwm = prev.dwm.overrideAttrs (old: {
          src = ./dwm;
          buildInputs = old.buildInputs ++ [ prev.libxcursor ];
        });
        st = prev.st.overrideAttrs (old: {
          src = ./st;
          buildInputs = old.buildInputs ++ [ prev.libxcursor ];
        });
        dmenu = prev.dmenu.overrideAttrs { src = ./dmenu; };
        slstatus = prev.slstatus.overrideAttrs { src = ./slstatus; };
      };

      packages = eachSystem (pkgs: {
        inherit (pkgs)
          dwm
          slstatus
          dmenu
          st
          ;
      });

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
