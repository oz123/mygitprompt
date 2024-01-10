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

Now that we added the data structure and we do a reasonable job parsing the file status. But what about counting our
commits a head?
```
 [±|main ↑1 U:3 ?:4 ✗|] 
```
This is produced from the following:
```
$ git status --branch --porcelain=v1
## main...origin/main [ahead 1]
 M .vscode/tasks.json
 M mygitprompt.c
 M mygitprompt.code-workspace
?? .vscode/settings.json
?? bar
?? foo
?? mygitprompt
```

This can also be a prompt with the number of commits behind:

```
[±|main ↓1 U:1 ?:5 ✗|] 

## main...origin/main [behind 1]
 M README.md
 ?? .README.md.swp
 ?? .vscode/settings.json
 ?? bar
 ?? foo
 ?? mygitprompt
```

Or it could be a prompt like this, with both added or behind:
[±|main ↑1 ↓1 ?:5 ✗|]
```
 git status --porcelain=v1 --branch 
## main...origin/main [ahead 1, behind 1]
 ?? .README.md.swp
 ?? .vscode/settings.json
 ?? bar
 ?? foo
 ?? mygitprompt
```

TODO: we still need to handle commits ahead or behind in the default theme.
```
[±|two-node → mine ↑6 ✓|]
```
