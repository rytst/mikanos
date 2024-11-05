# EDK2

[Unable to build](https://qiita.com/JugglerShu@github/items/7fdef7962d6c1fe5537c)

- Change `BaseTools/Source/C/Makefiles/header.makefile`
```
 94 BUILD_CFLAGS = -MD -fshort-wchar -fno-strict-aliasing -fwrapv \
 95 # -fno-delete-null-pointer-checks -Wall -Werror \
 96 -fno-delete-null-pointer-checks \
 97 -Wno-deprecated-declarations -Wno-stringop-truncation -Wno-restrict \
 98 -Wno-unused-result -nostdlib -g

```
