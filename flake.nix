{
  description = "suckless configuration that sucks less";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      suckless = import ./.;

      lib = nixpkgs.lib;
      systems = lib.systems.flakeExposed;
      # pkgs = system: nixpkgs.legacyPackages.${system}.extend self.overlays.default;
      # eachSystem = f: lib.genAttrs systems (system: f pkgs);
      eachSystem = f: lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      nixosModules = {
        default = suckless.module;

        suckless = {
          imports = [ self.nixosModules.default ];
          nixpkgs.overlays = [ self.overlays.default ];
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

      overlays.default = final: _: suckless.packages { pkgs = final; };
      packages = eachSystem (pkgs: suckless.packages { inherit pkgs; });

      devShells = eachSystem (pkgs: {
        default = pkgs.mkShell {
          packages = [ pkgs.nixfmt ];
        };
      });
    };
}
