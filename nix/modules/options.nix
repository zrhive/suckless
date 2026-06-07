{ config, lib, ... }:
{
  options.suckless =
    let
      inherit (lib) mkEnableOption mkOption types;
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
                  type = types.package;
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
        default = { };
        description = "Suckless tools config.";
      };

      #: PLACEHOLDERS
      packages = mkOption {
        type = types.listOf types.package;
        default = [ ];
        description = "A placeholder to compile the packages.";
      };

      extraCommands = mkOption {
        type = types.lines;
        default = "";
        description = "Extra commands during session initialization.";
      };
    };

  config =
    let
      inherit (config.suckless) tools;
    in
    {
      suckless = {
        packages = lib.concatMap (tool: lib.optional tool.enable tool.package) (lib.attrValues tools);

        extraCommands = lib.concatMapStringsSep "\n" (tool: lib.optionalString tool.enable tool.command) (
          lib.attrValues tools
        );

        tools.slstatus.command = lib.optionalString (
          tools.slstatus.enable && tools.dwm.enable
        ) "${lib.getExe tools.slstatus.package}";
      };
    };
}
