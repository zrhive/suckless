{
  description = "suckless configuration that sucks less";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { nixpkgs, ... }:
    let
      systems = [ "x86_64-linux" ];
      eachSystem = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});

      suckless-packages =
        { pkgs }:
        {
          dwm = pkgs.dwm.overrideAttrs (old: {
            src = ./dwm;
            buildInputs = old.buildInputs ++ [ pkgs.libxcursor ];
          });
          st = pkgs.st.overrideAttrs (old: {
            src = ./st;
            buildInputs = old.buildInputs ++ [ pkgs.libxcursor ];
          });
          dmenu = pkgs.dmenu.overrideAttrs { src = ./dmenu; };
          slstatus = pkgs.slstatus.overrideAttrs { src = ./slstatus; };
        };
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

      overlays.default = final: _: suckless-packages { pkgs = final; };

      packages = eachSystem (pkgs: suckless-packages { inherit pkgs; });

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
