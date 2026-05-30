{ self, pkgs }:

pkgs.mkShellNoCC {
  packages = [
    self.formatter.${pkgs.stdenv.hostPlatform.system}

    (pkgs.writeShellScriptBin "hooks-install" ''
      prek install --prepare-hooks
    '')

    (pkgs.writeShellScriptBin "hooks-runall" ''
      git add .
      prek run --all-files --show-diff-on-failure
    '')

    pkgs.prek
  ];
}
