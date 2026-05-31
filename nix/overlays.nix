{ packages }:
{
  default =
    final: prev:
    let
      pack = packages.${final.stdenv.hostPlatform.system};
    in
    {
      dmenu = pack.flexipatch-dmenu;
      dwm = pack.flexipatch-dwm;
      st = pack.flexipatch-st;
      slstatus = pack.suckless-slstatus;
    };

  /**
    SUCKLESS
  */
  suckless = final: prev: {
    inherit (packages.${final.stdenv.hostPlatform.system})
      suckless-dmenu
      suckless-dwm
      suckless-slstatus
      suckless-st
      ;
  };

  /**
    FLEXIPATCH
  */
  flexipatch = final: prev: {
    inherit (packages.${final.stdenv.hostPlatform.system})
      flexipatch-dmenu
      flexipatch-dwm
      flexipatch-slstatus
      flexipatch-st
      ;
  };
}
