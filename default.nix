{
  config,
  lib,
  pkgs,
  ...
}:
let
  inherit (lib) mkEnableOption mkIf mkMerge;
  cfg = config.suckless;
in
{
  options.suckless = {
    dwm = mkEnableOption "dwm";
    slstatus = mkEnableOption "slstatus";
    dmenu = mkEnableOption "dmenu";
    st = mkEnableOption "st";
  };

  config = mkMerge [
    (mkIf cfg.dwm {
      services.xserver.windowManager.dwm = {
        enable = true;
        package = pkgs.dwm;
      };
    })

    (mkIf cfg.dmenu {
      environment.systemPackages = [ pkgs.dmenu ];
    })

    (mkIf cfg.st {
      environment.systemPackages = [ pkgs.st ];
    })

    (mkIf cfg.slstatus {
      environment.systemPackages = [ pkgs.slstatus ];
      services.xserver.windowManager.dwm = {
        extraSessionCommands = "${pkgs.slstatus}/bin/slstatus &";
      };
    })
  ];
}
