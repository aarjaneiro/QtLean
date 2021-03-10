![logo](src/assets/logo.png)

# QtLean

A Qt interface and build system for QuantConnect's Lean (WIP).

Pictures
--------

- Main UI

  ![ui](images/mainui.png)


- Configuration editor
  
  ![config](images/config.png)

Current Features
-----------------

1. JSON TreeView editor.

TODO
----

1. Add interfacing with mono via embedding.
2. Add fully automatic Python configuration via cmake.
3. Add charting.

Dependencies
------------

- Python 3.6
- Mono
- Nuget
- QT 6

Building
--------
The project can be built by running:

```shell
mkdir build && cd build
cmake ..
make

```


If you run into issues, note that one can execute `make {OPTION}` for any of the following options:

````
... all (the default if no target is provided)
... clean
... depend
... edit_cache
... rebuild_cache
... copy_config_files
... qtlean_autogen
... qtlean
... qtlean_autogen/mocs_compilation.o
... qtlean_autogen/mocs_compilation.i
... qtlean_autogen/mocs_compilation.s
... src/QJsonModel.o
... src/QJsonModel.i
... src/QJsonModel.s
... src/TreeEditor.o
... src/TreeEditor.i
... src/TreeEditor.s
... src/main.o
... src/main.i
... src/main.s
````
