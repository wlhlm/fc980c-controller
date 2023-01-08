Leopold FC980C replacement controller firmware
==============================================

This repository provides [QMK firmware][QMK] configuration files, which as of
this writing have not been incorporated into the main QMK repository.

Building QMK configurations that are not part of the main repository is a bit of
a nuisance as the official configurator cannot be used and the setup for local
builds requires additional manual steps. Because of this, premade firmware
binaries is provided, but is is recommended to build their own your firmware. No
effort is made to keep the binaries up to date.

[QMK]: https://qmk.fm/

Building QMK
------------

QMK is a fast moving project and a such it is not guaranteed that using the
firmware config in this repository will work with the latest main branch of QMK.
Because of that, this repository includes the main QMK repository as a submodule
pinned to a specific version verified to work with this config.

For git to download the QMK submodule you either have to clone this repository
recursively

```bash
$ git clone --recursive "https://github.com/wlhlm/fc980c-controller.git"
```

or recursively initialize the submodule if you've already done the clone
non-recursively.

```bash
$ git submodule update --init --recursive
```

After initializing the QMK submodule you can either symlink or copy the contents
of the `keyboard` directory into QMK's `keyboards` directory.

After this the firmware can be built like normal using either `make`

```bash
$ make rot13/fc980c:default
```

or the QMK CLI (just make sure that the CLI uses this QMK submodule rather than
your normal QMK repository by running
`qmk config user.qmk_home=<path/to/submodule>`).

Flashing the firmware
---------------------

Before flashing, the bootloader must be entered. This can be achieved by
keeping the BOOT0 button pressed while plugging the keyboard in.

Flashing is done the same it is done for flashing QMK using `make` or the QMK
CLI.

The premade firmware images can be flashed using the QMK CLI (via
`qmk flash leopold_fc980c_wlhlm_default.bin`), QMK Toolbox, or directly using
`dfu-util`:

```bash
$ dfu-util -d 0483:DF11 -a 0 -s 0x08000000:leave -D leopold_fc980c_wlhlm_default.bin

```
