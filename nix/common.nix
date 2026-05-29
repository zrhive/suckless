{
  self,
  lib,
  pkgs,
  ...
}:

let
  inherit (lib) mkDefault;
  packages = self.packages.${pkgs.stdenv.hostPlatform.system};
in
{
  suckless.tools = {
    dmenu.package = mkDefault packages.dmenu;
    dwm.package = mkDefault packages.dwm;
    st.package = mkDefault packages.st;
    slstatus.package = mkDefault packages.slstatus;
  };
}
