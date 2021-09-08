# Description

My solutions[1] to the first coding assignment from the proceeding udemy course:
https://www.udemy.com/course/network-programming-from-scratch/

# To generate build files run the following commands in your terminal

```bash
mkdir build
cmake -G "Unix Makefiles" -S src -B build
cmake --build build
```

Copy paste this command to run them all at once ([source](https://unix.stackexchange.com/questions/61139/extract-triple-backtick-fenced-code-block-excerpts-from-markdown-file)):

`sed -n '/^```/,/^```/ p' < README.md | sed '/^```/ d' | bash`

## Note on source of work

I solve all of these problems without looking at the instructor solutions and I do not google for
high level solutons/approaches e.g. "how to get broadcast address from ip and mask in C". If I do
get stuck somewhere and need to find a solution I will link the source as a comment in code.

I do, of course, perform typical googling and man page checks on the standard library and the many
idiosyncrasies of C.
