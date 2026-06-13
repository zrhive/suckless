{ config, lib, ... }:
{
  options.suckless = {
    enable = lib.mkEnableOption "Enable suckless modules.";

    tools = lib.mkOption {
      type = lib.types.attrsOf (
        lib.types.submodule (
          { name, ... }:
          {
            options = {
              enable = lib.mkEnableOption "Enable ${name}.";

              package = lib.mkOption {
                type = lib.types.package;
                description = "Package to install.";
              };

              command = lib.mkOption {
                type = lib.types.lines;
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
    packages = lib.mkOption {
      type = lib.types.listOf lib.types.package;
      default = [ ];
      description = "A placeholder to compile the packages.";
    };

    extraCommands = lib.mkOption {
      type = lib.types.lines;
      default = "";
      description = "Extra commands during session initialization.";
    };
  };

  # config = lib.mkIf config.suckless.enable {
  #   suckless = {
  #     packages = lib.concatMap (tool: lib.optional tool.enable tool.package) (
  #       lib.attrValues config.suckless.tools
  #     );

  #     extraCommands = lib.concatMapStringsSep "\n" (tool: lib.optionalString tool.enable tool.command) (
  #       lib.attrValues config.suckless.tools
  #     );
  #   };
  # };
}
