{
   description = "Nix dev flake smolbox";
   inputs = {
      nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
      flake-utils.url = "github:numtide/flake-utils";
   };

   outputs = { self, nixpkgs, flake-utils }:
      flake-utils.lib.eachDefaultSystem (system:
         let
         pkgs = import nixpkgs {
            inherit system;
         };
         in {
            devShells.default = pkgs.mkShell {
               name = "dev";

               packages = with pkgs; [
                  clang
                  clang-tools
                  llvmPackages.bintools
                  gdb
                  gnumake
                  pkg-config
                  # musl
                  glibc
               ];

               shellHook = ''
                  export CC=clang
                  export CXX=clang++
               '';
            };
         }
    );
}
