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
  dmenu = packages.flexipatch-dmenu;
  dwm = packages.flexipatch-dwm;
  st = packages.flexipatch-st;
  slstatus = packages.suckless-slstatus;

  /**
    SUCKLESS
  */
  #: DMENU
  suckless-dmenu = pkgs.dmenu.overrideAttrs { src = "${suckless}/dmenu"; };
  #: DWM
  suckless-dwm = (pkgs.dwm.overrideAttrs { src = "${suckless}/dwm"; }).override {
    extraLibs = [
      #: For xcursor patch
      pkgs.libxcursor
    ];
  };
  #: SLSTATUS
  suckless-slstatus = (pkgs.slstatus.overrideAttrs { src = "${suckless}/slstatus"; }).override {
    extraLibs = [
      #: For alpha patch
      pkgs.libxrender
      #: For themed cursor patch
      pkgs.libxcursor
    ];
  };
  #: ST
  suckless-st = pkgs.st.overrideAttrs { src = "${suckless}/st"; };

  /**
    FLEXIPATCH
  */
  #: DMENU
  flexipatch-dmenu = (pkgs.dmenu.overrideAttrs { src = "${flexipatch}/dmenu"; }).override { };

  #: DWM
  flexipatch-dwm = (pkgs.dwm.overrideAttrs { src = "${flexipatch}/dwm"; }).override {
    extraLibs = [
      #: For alpha patch
      pkgs.libxrender
      #: For rounded corners patch
      pkgs.libxext
      #: For swallow patch
      # pkgs.libxcb
      #: For xcursor patch
      # pkgs.libxcursor
    ];

    # patches = [
    #   #: xcursor patch is not included in flexipatch, solve by adding the patch here
    #   (pkgs.fetchpatch {
    #     url = "https://raw.githubusercontent.com/zrhive/suckless/refs/heads/xcursor-patch/nix/dwm-xcursor-20260601.patch";
    #     hash = "sha256-InxLPMplHw6maqlqBlSArjX2d2efCaMru0c06nn4Vy4=";
    #   })
    # ];
  };

  #: ST
  flexipatch-st = (pkgs.st.overrideAttrs { src = "${flexipatch}/st"; }).override {
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
}
