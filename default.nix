{ config, lib, pkgs, ... }: with pkgs;

let
  inherit (lib) mkEnableOption mkIf mkMerge;

  dwm       = pkgs.dwm.overrideAttrs { src = ./dwm; };
  slstatus  = pkgs.slstatus.overrideAttrs { src = ./slstatus; };
  dmenu     = pkgs.dmenu.overrideAttrs { src = ./dmenu; };
  st        = pkgs.st.overrideAttrs { src = ./st; };
  cfg       = config.suckless;
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
        package = dwm;
      };
    })

    (mkIf cfg.dmenu {
      environment.systemPackages = [ dmenu ];
    })

    (mkIf cfg.st {
      environment.systemPackages = [ st ];
    })

    (mkIf cfg.slstatus {
      environment.systemPackages = [ slstatus ];
      services.xserver.windowManager.dwm = {
        extraSessionCommands = "${slstatus}/bin/slstatus &";
      };
    })
  ];
}
