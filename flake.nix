{
   description = "Nix dev flake smolbox";
   inputs = {
      nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
      flake-utils.url = "github:numtide/flake-utils";
      linux = {
          url = "git+https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git?shallow=1";
          flake = false;
      };
   };

   outputs = { self, nixpkgs, flake-utils, linux }:
      flake-utils.lib.eachDefaultSystem (system:
         let
         pkgs = import nixpkgs {
            inherit system;
         };
         in {
            packages.default = pkgs.stdenv.mkDerivation {
                pname = "smolbox";
                version = "0.1.0";
                buildInputs = [
                    pkgs.gcc
                    pkgs.gnumake
                    pkgs.pkg-config
                ];


                src = self;

                buildPhase = ''
                    rm -rf lib/linux
                    cp -r ${linux} lib/linux
                    chmod -R u+w lib/linux
                    make
                '';

                installPhase = ''
                    mkdir -p $out/bin
                    cp smolbox $out/bin/
                '';
            };

            devShells.default = pkgs.mkShell {
               name = "dev";

               packages = with pkgs; [
                  clang
                  clang-tools
                  llvmPackages.bintools
                  gdb
                  gnumake
                  pkg-config
                  dpkg
               ];

               shellHook = ''
                  export LDFLAGS="-L${pkgs.musl}/lib"
                  export CC=clang
                  export CXX=clang++
               '';
            };
         }
    );
}
