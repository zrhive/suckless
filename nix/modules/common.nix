{ self }:
{ lib, pkgs, ... }:
{
  suckless.tools =
    let
      inherit (lib) mkDefault;
      packages = self.packages.${pkgs.stdenv.hostPlatform.system};
    in
    {
      dmenu.package = mkDefault packages.dmenu;
      dwm.package = mkDefault packages.dwm;
      st.package = mkDefault packages.st;
      slstatus.package = mkDefault packages.slstatus;
    };
}
