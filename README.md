# libimagequant

This is a fork of the [BSD-2-Clause](COPYRIGHT) licensed
[libimagequant v2.4.1](https://github.com/ImageOptim/libimagequant/releases/tag/2.4.1).

This repo adopts "SameVer" versioning where every release maintains
backwards compatibility with and therefore gets the same
[v2.4.1](https://github.com/lovell/libimagequant/releases/tag/v2.4.1)
version number.

## Changes

* Supports building and cross-compiling via [meson](https://mesonbuild.com/)
* Adds a facade for the `liq_image_quantize` function
* Increases default speed to `5`
* Other small performance improvements
* Applies third-party [patches](patches)

https://github.com/lovell/libimagequant/compare/1a35b21...v2.4.1

## Building

```sh
meson setup _build --buildtype=release --strip
ninja -C _build
```
