{
  self,
  stdenv,
  mkShellNoCC,
  writeShellScriptBin,
  prek,
}:

let
  #: accessible via: `$ hooks-install`
  installHooks = writeShellScriptBin "hooks-install" ''
    prek install --prepare-hooks
  '';

  #: accessible via: `$ hooks-runall`
  runHooks = writeShellScriptBin "hooks-runall" ''
    git add .
    prek run --all-files --show-diff-on-failure
  '';
in
mkShellNoCC {
  packages = [
    self.formatter.${stdenv.hostPlatform.system}
    installHooks
    runHooks
    prek
  ];
}
