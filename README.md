# To generate build files run the following commands in your terminal

```bash
mkdir build
cmake -G "Unix Makefiles" -S src -B build
cmake --build build
```

Copy paste this command to run them all at once ([source](https://unix.stackexchange.com/questions/61139/extract-triple-backtick-fenced-code-block-excerpts-from-markdown-file)):

`sed -n '/^```/,/^```/ p' < README.md | sed '/^```/ d' | bash`

