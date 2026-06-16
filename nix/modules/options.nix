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
            };
          }
        )
      );
      default = { };
      description = "Suckless tools config.";
    };

    #: PLACEHOLDER
    packages = lib.mkOption {
      type = lib.types.listOf lib.types.package;
      default = [ ];
      description = "A placeholder to compile the packages.";
    };
  };

  config = lib.mkIf config.suckless.enable {
    suckless.packages = lib.concatMap (tool: lib.optional tool.enable tool.package) (
      lib.attrValues config.suckless.tools
    );
  };
}
