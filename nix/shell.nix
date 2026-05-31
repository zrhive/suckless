{ self, pkgs }:
{
  default = pkgs.mkShellNoCC {
    packages = [
      #: formatter
      self.formatter.${pkgs.stdenv.hostPlatform.system}

      #: accessible via: `$ hooks-install`
      (pkgs.writeShellScriptBin "hooks-install" ''
        prek install --prepare-hooks
      '')

      #: accessible via: `$ hooks-runall`
      (pkgs.writeShellScriptBin "hooks-runall" ''
        git add .
        prek run --all-files --show-diff-on-failure
      '')

      #: git hooks runner
      pkgs.prek
    ];
  };
}
