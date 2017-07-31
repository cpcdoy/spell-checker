# spell-checker
## Description

This projects aims at doing high performance fuzzy search in large data-sets using custom data structure.
This projects implements a hybrid Trie (previously a DAWG), which is written on RAM and Disk depending on usage

In the end the TextMiningCompiler compiles the whole trie on disk in a file and the TextMiningApp can use that index file to do a fast fuzzy search.

## Build

This project is using the CMake build system.

### In-Source build

```sh
cmake .
make
```

### Out-of-source build

```sh
mkdir build && cd build
cmake .
make
```

## Design

The compiler was originally designed using a Directed Acyclic Word Graph (DAWG or MA-FSA), but the algorithm was found to use too much memory (> 1Go) and we had trouble merging some nodes.

After this, we designed a Hybrid Trie, that works on RAM and disk, that uses 40Mb RAM, when loaded with the 41M words text file.

That Hybrid Trie has a maximum depth (e.g. 4) and after that, the trie dump the word' suffix on disk. A directory (e.g. "dict.bin/") is created with each file having an id.

When searching, the trie is very fast when the word is in RAM (i.e. size < max_trie_depth) but if the word is too long, we then continue searching on disk which can take a long time.

Finally, when using the TextMiningCompiler, we only compile the trie in RAM to disk, which is dumped into the dict.bin (for exemple).
