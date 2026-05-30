{
  self,

  treefmt,
  nixfmt,
  deadnix,
  statix,

  formats,
  writeShellScriptBin,
}:

let
  statixFix = writeShellScriptBin "statix-fix" ''
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
      } -- "$file"
    done
  '';

  runtimeInputs = [
    nixfmt
    deadnix
    statixFix
  ];

  settings = {
    tree-root-file = "${self}/flake.nix";
    on-unmatched = "info";
    formatter = {
      nixfmt = {
        includes = [ "*.nix" ];
        command = "nixfmt";
      };
      deadnix = {
        includes = [ "*.nix" ];
        command = "deadnix";
        options = [
          "--edit"
          "--no-lambda-arg"
        ];
      };
      statix = {
        includes = [ "*.nix" ];
        command = "statix-fix";
      };
    };
  };
in
treefmt.withConfig { inherit runtimeInputs settings; }
