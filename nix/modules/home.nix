{ config, lib, ... }:
{
  imports = [ ./options.nix ];

  home = { inherit (config.suckless) packages; };

  xsession = {
    enable = lib.mkDefault config.suckless.tools.dwm.enable;

    windowManager.command = lib.optionalString config.suckless.tools.dwm.enable ''
      ${lib.getExe config.suckless.tools.dwm.package}
    '';
  };
}
