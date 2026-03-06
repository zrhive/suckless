{
		description = "suckless configuration that sucks less";

		outputs = { self }: {
				nixosModules.default = import ./.;
		};
}
