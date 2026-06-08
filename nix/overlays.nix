{ self }:

let
  packages = self.packages.${final.stdenv.hostPlatform.system};
in
{
  default = final: prev: {
    dmenu = packages.flexipatch-dmenu;
    dwm = packages.flexipatch-dwm;
    st = packages.flexipatch-st;
    slstatus = packages.suckless-slstatus;
  };

  #: SUCKLESS
  suckless = final: prev: {
    inherit (packages)
      suckless-dmenu
      suckless-dwm
      suckless-st
      suckless-slstatus
      ;
  };

  #: FLEXIPATCH
  flexipatch = final: prev: {
    inherit (packages)
      flexipatch-dmenu
      flexipatch-dwm
      flexipatch-st
      ;
  };
}
