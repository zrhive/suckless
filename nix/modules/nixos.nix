{ config, lib, ... }:

let
  inherit (config.suckless) tools;
  inherit (lib)
    mkDefault
    attrValues
    concatMap
    concatMapStringsSep
    optional
    optionalString
    ;

  packages = concatMap (tool: optional tool.enable tool.package) (attrValues tools);

  extraCommands = concatMapStringsSep "\n" (tool: optionalString tool.enable tool.command) (
    attrValues tools
  );
in
{
  imports = [ ./options.nix ];

  environment.systemPackages = packages;

  services.xserver.windowManager.dwm = {
    enable = mkDefault tools.dwm.enable;
    package = mkDefault tools.dwm.package;
    extraSessionCommands = mkDefault extraCommands;
  };
}
