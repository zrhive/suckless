{ config, lib, ... }:
{
  imports = [ ./options.nix ];

  environment.systemPackages = config.suckless.packages;

  services.xserver.windowManager.dwm = {
    enable = lib.mkDefault config.suckless.tools.dwm.enable;
    package = lib.mkDefault config.suckless.tools.dwm.package;
  };
}
