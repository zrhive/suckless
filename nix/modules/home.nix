{ config, lib, ... }:

let
  inherit (lib) mkDefault;
  inherit (config.suckless) tools packages extraCommands;
in
{
  imports = [ ./options.nix ];

  home.packages = packages;

  xsession = {
    enable = mkDefault tools.dwm.enable;
    initExtra = mkDefault extraCommands;

    windowManager.command = lib.optionalString tools.dwm.enable ''
      ${lib.getExe tools.dwm.package}
    '';
  };
}
