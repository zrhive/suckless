{ lib, ... }:
let
  inherit (lib) mkDefault;
in
{
  imports = [ ./. ];

  suckless = {
    dwm = mkDefault true;
    slstatus = mkDefault true;
    dmenu = mkDefault true;
    st = mkDefault true;
  };
}
