# twitter-ds

A benchmark of BST and AVL trees, written in C++.

## Author

Daniel Omiya (41995449) @gwyddie

## Used technologies

- C++17
- [fast-cpp-csv-parser](https://github.com/ben-strasser/fast-cpp-csv-parser)
- [graphviz](https://gitlab.com/graphviz/graphviz)

## How to run it

    $ make      # compiling sources
    $ build/app # running app

## Generating tree visualization

To generate representations of the trees as images, use the following target:

    $ make graph IN=$dot_file

Note that all `.dot` files are written to the `reports/` directory.

---

> _That's all, folks!_
