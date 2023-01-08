Leopold FC980C replacement controller firmware
==============================================

This repository provides [QMK firmware][QMK] configuration files, which as of
this writing have not been incorporated into the main QMK repository.

Building QMK configurations that are not part of the main repository is a bit of
a nuisance as the official configurator cannot be used and the setup for local
builds requires additional manual steps. Because of this, a premade firmware
binary is provided, but the recommendation for the user to build their own
firmware. No effort is made to keep the binary up to date.

[QMK]: https://qmk.fm/

Building QMK
------------

QMK is a fast moving project and a such it is not guaranteed that using the
firmware config in this repository will work with the latest main branch of QMK.
Because of that, this repository include the main QMK repository as a submodule
pinned to the specific version verified to work with the config.

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
your normal QMK repository.

Flashing the firmware
---------------------

Flashing is done the same it is done for flashing QMK using `make` or the QMK
CLI.

The bootloader can be entered by keeping the BOOT0 button pressed while plugging
the keyboard in.
