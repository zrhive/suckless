{ self, config, lib, ... }:
{
  options.suckless =
    let
      inherit (lib) mkDefault mkEnableOption mkOption types literalExpression;
      inherit (config.suckless) tools;
      packages = self.packages.{pkgs.stdenv.hostPlatform};
    in
    {
      enable = mkEnableOption "Enable suckless modules.";

      tools = mkOption {
        type = types.attrsOf (types.submodules ({ name, ... }:
          {
            options = {
              enable = mkEnableOption "Enable ${name}.";
              package = mkOption {
                type = types.package;
                description = "Package to install.";
              };
              command = mkOption {
                type = types.nullOr (types.either types.lines types.str);
                default = null;
                description = "Commands to execute for the tool.";
              };
            };
          }
        ));
        example = literalExpression ''
          suckless = {
            dwm.enable = true;
            dmenu = {
              enable = true;
              package = pkgs.dmenu;
            };
          };
        '';
        default = {
          dmenu.package = mkDefault packages.dmenu;
          dwm.package = mkDefault packages.dwm;
          st.package = mkDefault packages.st;
          slstatus.package = mkDefault packages.slstatus;
        };
        description = "Suckless tools config.";
      };

      #: PLACEHOLDERS
      packages = mkOption {
        type = types.nullOr (types.listOf types.package);
        default = [];
        readOnly = true;
        description = "A placeholder to compile the packages.";
      };

      extraCommands = mkOption {
        type = types.nullOr types.lines;
        default = null;
        readOnly = true;
        description = "Extra commands during session initialization.";
      };
    };

  config =
    let
      inherit (lib) mkIf any attrValues
        optional optionalString concatMap concatMapStringsSep;

      inherit (config.suckless) tools;
      toolList = attrValues config.suckless.tools;
      anyToolEnabled = any (tool: tool.enable) toolList;

      packages = concatMap (tool: optional tool.enable tool.package) toolList;
      extraCommands = concatMapStringsSep "\n" (tool: tool.command) toolList;
    in
    mkIf (config.suckless.enable || anyToolEnabled) {
      suckless = {
        inherit packages extraCommands;

        tools.slstatus.command = optionalString (
          tools.slstatus.enable && tools.dwm.enable
        ) "${getExe tools.slstatus.package}";
      };
    }
}
