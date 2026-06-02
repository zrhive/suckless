{ config, lib, ... }:

let
  inherit (lib) mkDefault;
  inherit (config.suckless) tools packages extraCommands;
in
{
  import = [ ./options.nix ];

  environment.systemPackages = packages;

  services.xserver = {
    enable = true;
    windowManager.dwm = {
      enable = mkDefault tools.dwm.enable;
      package = mkDefault tools.dwm.package;
      extraSessionCommands = mkDefault extraCommands;
    };
  };
}
