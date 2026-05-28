{ config, lib, ... }:
{
  import = [ ./options.nix ];

  home.packages = config.suckless.packages;

  xsession = let
    inherit (lib) mkDefault;
    inherit (config.suckless) tools;

  in {
    enable = mkDefault true;

    initExtra = mkDefault config.suckless.extraCommands;
    windowManager.command = mkDefault (
      lib.optionalString tools.dwm "${lib.getExe tools.dwm.package}"
    );
  };
}
