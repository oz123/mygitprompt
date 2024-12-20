My git prompt
=============

Yet another git prompt, written in C for speed and simplicity.

Usage:
------

Download the binary from the release page or compile on your own.
```
latest_version=$(curl --silent "https://api.github.com/repos/oz123/mygitprompt/releases/latest" | grep '"tag_name"' | sed -E 's/.*"([^"]+)".*/\1/')'])"')
wget https://github.com/oz123/mygitprompt/releases/download/${latest_version}/mygitprompt-static-linux-amd64
```

Run:
```
$ install -m 755 mygitprompt-static-linux-amd64 usr/local/bin/mygitprompt 
```
Add it to your PS1 in `.bashrc`, for example in Debian based systems:
```
PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\] $(/usr/local/bin/mygitprompt)\$ '
```

Configuration:
--------------

In the spirit of [suckless](https://suckless.org), configuration is done by editing
the source code.
You don't need to master C to do this. Check `colors.h` and `config.h`.
The later contains a function `show_prompt(GitStatus *sh)` which you can
modify for your own taste.
Some colors are defined in `colors.h` you can add more there.

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

Handle commits ahead or behind in the default theme.
```
[±|two-node → mine ↑6 ✓|]
```

Handle tags:
```
[±|tag:v1.0.8 ✓|] $ 
```

If there is no branche: 

```
git status --porcelain=v1 --branch 
## HEAD (no branch)
```
Try and find tags:

```
$ git describe --tags --exact-match 
v1.0.8
```

Behind commits:
```
[±|main → origin ↓8 ?:4 ✗|] $git status --porcelain --branch 
## main...origin/main [behind 8]
?? TODO
?? bla
?? foo
?? test.sh
```
