{ self }:

let
  packages = final: self.packages.${final.stdenv.hostPlatform.system};
in
{
  default = final: prev: {
    dmenu = (packages final).flexipatch-dmenu;
    dwm = (packages final).flexipatch-dwm;
    st = (packages final).flexipatch-st;
    slstatus = (packages final).suckless-slstatus;
  };

  #: SUCKLESS
  suckless = final: prev: {
    inherit (packages final)
      suckless-dmenu
      suckless-dwm
      suckless-st
      suckless-slstatus
      ;
  };

  #: FLEXIPATCH
  flexipatch = final: prev: {
    inherit (packages final)
      flexipatch-dmenu
      flexipatch-dwm
      flexipatch-st
      ;
  };
}
