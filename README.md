# smolbox

smolbox is a rewrite of standard Linux utilities, such as GNU coreutils.

It aims to be as optimized and tiny as possible. This of course comes with compromises.

It is written in C without any libc, meaning completely static, less syscalls, and smaller but faster binaries.

## Building

This project is using the make build system, meaning it's trivial to build.

You will need the packages `gnumake` and a C compiler (`gcc`).

```
make
```

If you want to package for Debian (x86_64):

```
make build-deb
```

**Alternatively you can download pre-built binaries for x86_64 and arm [here](https://github.com/a-rvid/smolbox/actions/workflows/build.yml).** Choose "artifacts" and download the static binary or debian package for your system.

## Optimizations

This project has very strict rules for the code to optimize it.

For instance the `printf` family of functions has been completely excluded, as it adds about 1500 bytes to the code.

While the core target of the project is as small as possible, optimization and runtime speed is not compromised. Syscalls and such have been minimized, which will require some extra code/filesize, like `fputs` adding a few hundred bytes for buffering write syscalls.

This is a multicall binary, meaning that functions are shared between the different commands, and all commands are the same binary. This greatly reduces filesize.

You can rename (or symlink) the multicall binary to the desired command, and the program will think it's executing `pwd` if it's called `pwd`. You can also run `smolbox pwd` and it will print the current working directory.

A great example of how optimizations have paid off is comparing against other implementations. The `pwd` function here calls 2 syscalls, `getcwd` and `write`, while standard coreutils calls around 40 syscalls (some of them are linking-related, the rest doesn't make sense.).

## Compromises

To reduce filesize I've done some major compromises. Error handling and error messages take up quite a lot of filesize, so for some error messages I have decided not to explain all of them.

You'll recieve a error message with a errno number, which you afterwards can google.

I decided to let help messages be a thing, but if you want to disable them you can build with `make tiny`.

## TODO

* error checking prints eg. `pwdNo such file or directory` (implement perror)
