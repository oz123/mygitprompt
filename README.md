My git prompt
=============

Yet another git prompt with emphasis on BASH (which is my default shell).

A project to learn a bit more about C.

Dependencies:
-------------
 * C compiler
 * gnu make
 * meson buildsysem

Start hacking:
--------------
Git clone this repository and run:
```
make init
```

To clean all build files:
```
make clean
```

To clean all meson setup files:
```
make clean-all
```

### parsing git status

The command `git status --porcelain=v1 --branch` retruns a list of files prefixed with a status:
```
$ git status --porcelain=v1 --branch 
## main...origin/main
 M .vscode/tasks.json
M  README.md
A  bar
 M mygitprompt.c
 M mygitprompt.code-workspace
?? .vscode/settings.json
?? foo
?? mygitprompt
```
We want the prompt to output something like this:
```
[±|main S:2 U:3 ?:3 ✗|]
```
We need some data structure to count the different status, and store the parsed output using that structure.