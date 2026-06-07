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

    # Set to lightdm false by default, avoid
    # conflict with other display manager config
    displayManager.lightdm.enable = lib.mkDefault false;
  };
}
