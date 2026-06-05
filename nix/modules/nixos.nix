{ config, lib, ... }:

let
  inherit (lib) mkDefault;
  inherit (config.suckless) tools packages extraCommands;
in
{
  imports = [ ./options.nix ];

  environment.systemPackages = packages;

  services.xserver = {
    enable = mkDefault true;
    windowManager.dwm = {
      enable = mkDefault tools.dwm.enable;
      package = mkDefault tools.dwm.package;
      extraSessionCommands = mkDefault extraCommands;
    };
  };
}
