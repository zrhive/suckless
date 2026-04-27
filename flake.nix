{
  description = "suckless configuration that sucks less";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

  outputs =
    { self, nixpkgs }:
    let
      suckless = import ./.;

      lib = nixpkgs.lib;
      systems = [ "x86_64-linux" ];
      eachSystem = f: nixpkgs.lib.genAttrs systems (system: f nixpkgs.legacyPackages.${system});
    in
    {
      nixosModules = {
        default = suckless.module;

        suckless =
          { ... }:
          {
            imports = [ suckless.module ];
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
