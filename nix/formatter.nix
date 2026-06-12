{
  self,
  lib,
  bash,
  treefmt,
  nixfmt,
  deadnix,
  statix,
  formats,
}:

treefmt.withConfig {
  runtimeInputs = [
    nixfmt
    deadnix
    statix
  ];

  settings = {
    tree-root-file = "${self}/flake.nix";
    on-unmatched = "info";

    formatter = {
      nixfmt = {
        command = "nixfmt";
        includes = [ "*.nix" ];
      };

      deadnix = {
        command = "deadnix";
        includes = [ "*.nix" ];
        options = [
          "--edit"
          "--no-lambda-arg"
        ];
      };

      statix = {
        command = "${lib.getExe bash}";
        includes = [ "*.nix" ];
        options = [
          "-euc"
          ''
            for file in "$@"; do
              ${statix}/bin/statix fix --config ${
                (formats.toml { }).generate "statix.toml" {
                  disbaled = [
                    "manual_inherit_from"
                    "empty_pattern"
                    "redundant_pattern_bind"
                    "repeated_keys"
                  ];
                }
              } "$file"
            done
          ''
          "--"
        ];
      };
    };
  };
}
