{ self }:
{ lib, pkgs, ... }:

let
  inherit (lib) mkDefault;
  packages = self.packages.${pkgs.stdenv.hostPlatform.system};
in
{
  suckless.tools = {

    #: DMENU
    dmenu.package = mkDefault packages.dmenu;

    #: DWM
    dwm.package = mkDefault packages.dwm;

    #: ST
    st.package = mkDefault packages.st;

    #: SLSTATUS
    slstatus = {
      package = mkDefault packages.slstatus;
      command = mkDefault "slstatus &";
    };

  };
}
