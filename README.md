# libimagequant

This is a fork of the [BSD-2-Clause](COPYRIGHT) licensed
[libimagequant v2.4.1](https://github.com/ImageOptim/libimagequant/releases/tag/2.4.1).

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
