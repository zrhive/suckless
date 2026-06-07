{ config, lib, ... }:
{
  options.suckless =
    let
      inherit (lib)
        mkEnableOption
        mkOption
        types
        literalExpression
        ;
    in
    {
      enable = mkEnableOption "Enable suckless modules.";

      tools = mkOption {
        type = types.attrsOf (
          types.submodule (
            { name, ... }:
            {
              options = {
                enable = mkEnableOption "Enable ${name}.";
                package = mkOption {
                  type = types.nullOr types.package;
                  default = null;
                  description = "Package to install.";
                };
                command = mkOption {
                  type = types.lines;
                  default = "";
                  description = "Commands to execute for the tool.";
                };
              };
            }
          )
        );
        example = literalExpression ''
          tools = {
            dwm.enable = true;
            dmenu = {
              enable = true;
              package = pkgs.dmenu;
            };
          };
        '';
        default = { };
        description = "Suckless tools config.";
      };

      #: PLACEHOLDERS
      packages = mkOption {
        type = types.listOf types.package;
        default = [ ];
        readOnly = true;
        description = "A placeholder to compile the packages.";
      };

      extraCommands = mkOption {
        type = types.lines;
        default = "";
        readOnly = true;
        description = "Extra commands during session initialization.";
      };
    };

  config =
    let
      tools = config.suckless.tools;
      toolList = lib.attrValues tools;
      anyToolEnabled = lib.any (tool: tool.enable) toolList;
    in
    lib.mkIf (config.suckless.enable || anyToolEnabled) {
      suckless = {
        packages = lib.concatMap (tool: lib.optional tool.enable tool.package) toolList;
        extraCommands = lib.concatMapStringsSep "\n" (tool: tool.command) toolList;

        tools.slstatus.command = lib.optionalString (
          tools.slstatus.enable && tools.dwm.enable
        ) "${lib.getExe tools.slstatus.package}";
      };
    };
}
