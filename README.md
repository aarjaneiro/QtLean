![logo](src/assets/logo.png)

##### Table of Contents

- [QtLean](#qtlean)
- [Current Features](#current-features)
- [Building and Installing](#building-and-installing)
- [Common Install Problems](#common-install-problems)
  - [Python Config Errors](#python-config-errors)
- [Usage](#usage)

# QtLean

A Qt interface and build system for QuantConnect's Lean.

## Pictures

- Main UI

  ![ui](images/mainui.png)


- Configuration editor

  ![config](images/config.png)

## Current Features

1. JSON TreeView editor.
2. Automatic Mono + Python setup.

## TODO

1. Add charting.

## Dependencies

- Python 3.6
- Mono
- Nuget
- QT 6

## Building and Installing

The project can be built by running:

```shell
mkdir build && cd build
cmake ..
make

```

and installed to /usr/ by running:

```shell
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make install
```

## Common Install Problems:

- Configuration files are not able to be saved!
  - If you installed using `sudo make install`, run:

```shell
sudo chown $USER:$USER -R ~/.QtLean
```

- Python libraries cannot be found!
  - See the section "Python Config Errors". Otherwise...
  - Try installing using a Python 3.6 Conda environment.
  - Try installing Python 3.6 independently of Conda (that is, using your package manager or
    from https://www.python.org/downloads/release/python-368/).

### Python Config Errors

**If your Python is unable to be configured via CMake, run the following in your Lean root directory** and then modify
the generated PythonConfig.h file in your build directory with the result:
[py_configure.sh](https://raw.githubusercontent.com/aarjaneiro/Lean/0c7fc24c316fbc6e05ff0d2ec07863c1d7a491e1/py_configure.sh)

## Usage

__Note, it is best to run QtLean from the console. Such must be done in order to see console output!__

From your build directory, clone Lean (`git clone http://github.com/QuantConnect/Lean`), cd into the Lean subdirectory
and execute

```shell
../QtLean
```

If QtLean is installed, it can be called from any Lean directory by executing:

```shell
QtLean
```

