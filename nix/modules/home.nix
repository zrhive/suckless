{ config, lib, ... }:

let
  inherit (lib) mkDefault;
  inherit (config.suckless) tools packages extraCommands;
in
{
  import = [ ./options.nix ];

  home.packages = packages;

  xsession = {
    enable = mkDefault true;
    initExtra = mkDefault extraCommands;
    windowManager.command = lib.optionalString tools.dwm.enable "${lib.getExe tools.dwm.package}";
  };
}
