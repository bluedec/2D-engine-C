{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  packages = with pkgs; [
    gcc
    cmake
    sdl3
    clang-tools
  ];
}
