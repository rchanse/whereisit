Sat 21 Nov 2020 12:45:30 PM CST     (finally some doc)

Motivation: I keep forgetting where I put stuff and asking myself
 whereis ---

There will be two main tools  'f' and 'g'
f  is to help you find stuff by an acronym that you choose
g  is to find stuff in a list you have by number

'whereis' system

Parts:
1. 1 global variable '$rchjlp' initials Robert C Hansen, Jean-Luc Picard
2. a library which contains the code.  (usually called build-lib.
3. a library which has the running code (usually called exec-lib.

Assumptions:
 a. the build-lib will be in directory   $HOME/whereis
 b. the exec-lib will be in directory    $HOME/fubar
 c. you (or some software) are not otherwise using $rchjlp
( there will be a note below on how to override a. and b.  BUT
  to override c. you will need to copy and rewrite this code.)

I N S T A L L A T I O N:

1. Obtain the code:   git clone https://github.com/rchanse/whereis.git
( I'll assume you did this from $HOME be if you were cautious and
pulled it down to another directory, please move it to  $HOME/whereis)

cd ~/whereis            (get to the build-lib dir.

. ./setvar              (or  source ./setvar
                        This will set global $rchjlp  <<====
                        alt. cmd   '. $PWD/setvar'
                        alt. cmd   '. ~/whereis/setvar'

. ./INSTALL            (or   source ./INSTALL
                        create and populate exec-lib
                        remember the default will  $HOME/fubar dir.

. ~/fubar/engage        (hook the exec-lib into your environment

That's it.

So -- What next??

---------- R E M O V E  the environment (stopping)
. delpath ~/fubar

--------- C H E C K I N G the environment
checksys

---------- setting $rchjlp ----(3 choices)
a. from the console    'export rchjlp=fubar'
b. before INSTALL     '. ~/whereis/rchjlp fubar'           or
                      '. ~/whereis/rchjlp'    respond 'fubar' to prompt
c. after INSTALL      '. ~/fubar/rchjlp fubar'             or
                      '. ~/fubar/rchjlp'      respond 'fubar' to prompt

---------- (Re)Starting the environment
( $rchjlp needs to be set.)
. ~/fubar/engage
or
. ~/fubar/addpath0 ~/fubar

---------- really screwing up the environmen ------
goof up  $rchjlp        export rchjlp=anything_but_exec-lib basenam



Here are some commands you can try (with environment in place

dirinpath ~/fubar                 (will show if fubar members will
                                   conflict with your PATH

showpath                          (show a number list of path-files

meminpath xxx                     ( show if xxx is in your path
     
f .                                (shows a list of preset acronyms
now after you have seen them, try f someacro

-----------------
g q README                       
g 0
now try to go edit with g ##    ## some number between 1 and number
of line in gnamelist
--------------------

locate passwd > ~/tempname
g rep ~/tempname
g 0
g  pick1
---------------------

f acro nano                        (just like f but with nano not vim

Note: you may wish to edit create a nanorc to get a better looking nano

in either  ~/.nanorc         or  ~/.config/nano/nanorc
(my choice is)
set linenumbers
set autoindent
set showcursor
set constantshow
-----------------------------

enter  re_exec  or re_build   and read their help doc

---------------------------------------
  fake out ls
1. make newtest directory     ( from cd    mkdir newtest
2. cd newtest
3. meminpath ls                  (show where usual ls is found
4. in ~/newtest  create a file ls like next two lines
#!/usr/bin/env bash
echo "Not the ls you thought"
save it
make it executable   chmod +x ls
. addpath0 ~/newtest
ls                           k
. delpath ~/newtest
ls                    back to normal
-------------------

using your current pwd  (.   or you could state it explicitly
. addpath0 .               (make first in PATH
. addpath  .               (make last in PATHj
. delpath .                (remove from PATH


-------------------- Making your own environment ( other than
build-lib: whereis  and  exec-lib: fubar

1. Make a copy of the whereis library :  cp -vp ~/whereis/. ~/mybuild
   or   git clone https://github.com/rchanse/whereis.git  mybuild

2. in ~/mybuild you need to edit two members.
    a. builddir - change whereis to mybuild
    b. execdir  - change fubar to myexec

3. now  cd ~/mybuild and install as above replacing fubar with myexec

3a. $rchjlp plays the same role.
--------------------------------------



Stop for a moment  Sat 21 Nov 2020 01:41:45 PM CST



