{
  config,
  lib,
  pkgs,
  ...
}:
let
  inherit (lib) mkEnableOption mkIf mkMerge;

  dwm = pkgs.dwm.overrideAttrs (old: {
    src = ./dwm;
    buildInputs = old.buildInputs ++ [ pkgs.libxcursor ];
  });

  st = pkgs.st.overrideAttrs (old: {
    src = ./st;
    buildInputs = old.buildInputs ++ [ pkgs.libxcursor ];
  });

  dmenu = pkgs.dmenu.overrideAttrs { src = ./dmenu; };
  slstatus = pkgs.st.overrideAttrs { src = ./slstatus1; };

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
