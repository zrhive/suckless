{ self, config, lib, ... };
{
  import = [ (./options.nix { inherit self config lib; }) ];

  environment.systemPackages = config.suckless.packages;

  services.xserver =
    let
      inherit (lib) mkDefault;
      inherit (config.suckless) tools;
    in
    {
      enable = true;

      windowManager.dwm = {
        enable = mkDefault tools.dwm.enable;
        package = mkDefault tools.dwm.package;
        extraSessionCommands = mkDefault config.suckless.extraCommands;
      };
    };
}
