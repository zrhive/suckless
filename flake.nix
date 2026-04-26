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
        suckless = import ./suckless.nix;
      };

      packages = eachSystem (pkgs: {
        dwm = pkgs.dwm.overrideAttrs (old: {
          src = ./dwm;
          buildInputs = old.buildInputs ++ [ pkgs.libxcursor ];
        });

        st = pkgs.st.overrideAttrs (old: {
          src = ./st;
          buildInputs = old.buildInputs ++ [ pkgs.libxcursor ];
        });

        dmenu = pkgs.dmenu.overrideAttrs { src = ./dmenu; };
        slstatus = pkgs.st.overrideAttrs { src = ./slstatus; };
      });

      # overlays.default = ;

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
