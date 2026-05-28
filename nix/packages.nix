{ self, pkgs }:

let
  packages = self.packages.${pkgs.stdenv.hostPlatform.system};
  suckless = "${self}/suckless";
  flexipatch = "${self}/flexipatch";
in
{
  /**
    Initially used the sources under `suckless` category as
    the default for packages. The sources are sourced from
    `suckless.org`. Configured and patched by `@zhyie`, the
    packaged sources results in broken and messy overall.
    Though, the @zhyie's configuration of the said sources
    remain available. Only exception is the `slstatus`,
    which do not have a flexipatch, but still works for her.
  */
  inherit (packages.flexipatch) dmenu dwm st;
  inherit (packages.suckless) slstatus;

  /** SUCKLESS */
  suckless = {
    #: DMENU
    dmenu = pkgs.dmenu.overrideAttrs { src = "${suckless}/dmenu"; };
    #: DWM
    dwm = pkgs.dwm.overrideAttrs { src = "${suckless}/dwm"; };
    #: SLSTATUS
    slstatus = pkgs.slstatus.overrideAttrs { src = "${suckless}/slstatus"; };
    #: ST
    st = pkgs.st.overrideAttrs { src = "${suckless}/st"; };
  };

  /** FLEXIPATCH */
  flexipatch = {
    #: DMENU
    dmenu = (pkgs.dmenu.overrideAttrs { src = "${flexipatch}/dmenu"; }).override {};

    #: DMENU
    dwm = (pkgs.dwm.overrideAttrs { src = "${flexipatch}/dwm"; }).override {};

    #: ST
    st = (pkgs.st.overrideAttrs { src = "${flexipatch}/st"; }).override {
      #: LIBS REQUIRED FOR THE PATCHES
      extraLibs = [
        #: For alpha patch
        pkgs.libxrender
        #: For themed cursor patch
        pkgs.libxcursor
        #: For ligatures patch
        pkgs.harfbuzz
        #: For SIXEL patch
        pkgs.imlib2
      ];
    };
  };
}
