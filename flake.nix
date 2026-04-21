{
  description = "suckless configuration that sucks less";

  outputs = { self }: {
    nixosModules = {
      suckless = import ./.;
      default = self.nixosModules.suckless;
    };
  };
}
