#!/bin/bash

myeditor="vim"                # set the default myeditor
base_dir="etc"                # dir for the assoclist
if [ ! -d $HOME/$basd_dir ]; then
  mkdir $HOME/base_dir
fi

# debugging I left in the debugging echos but you can turn then on/off
# to turn them on   from cmd line  enter  export eth0="ON"
# to turn then back off                   export eth0=anythingbut_ON
# Note: export eth0= cmds may be before invoking f or you can
#  add then within the code to turn debugging on/off in spots.


# function to copy at top and use ech0 (rather than ech1
function ech0 () {     # turn on debugging with  export ech0=ON
  if [ ".$ech0" == ".ON" ]; then
    echo $@
  fi  
}

function nop() {    # a NO-OP to make code more readable later
#  VERY helpful making easier to aid in  if-then-else-fi blocks
#  if condition ; then         remember   if cond ; then
#     nop                                    code
#  else                                   else
#     nop                                 fi      will gen synax error
#  fi
#
  return 0
}

#  Below is the assoc file (name of assoc filename action    file 
assoc_file=$HOME/$base_dir/f_assoclist

# start of whereis code
#   if [ -f $rchbls/f_assoclist ]; then
#     assoc_file=$rchbls/f_assoclist
#   else
#     read -r bld_dir rest < $rchbls/builddir
#     assoc_file=$bld_dir/f_assoclist
#   fi
# end of whereis code

# save cmdline parms for later
p1=$1                         # first parm
read -r p1 p2 p3 p4 prest <<< $@    # parse cmd-line

#  Help info
if [ ".$p1" == "." ] || [ ".$p1" == ".--help" ] ; then
    clear
    echo "parmfile  :>"$assoc_file 
	echo ":::::::::::::::::::::::::::::::::::::::::::::::::::"
	echo "::  f -  quick invocation to file                ::"
	echo "::  f parm1 p2 p3 p4                             ::"
	echo "::    parm1                                      ::"
	echo "::      null   - display this help info          ::"
	echo "::      --help - display this help info          ::"
    echo "::      .      - go edit the assoc list file     ::"
	echo "::      other  - assoc for filename in assoc_file::"
	echo "::    p2 p3 p4 - action to override default editor "
	echo "::               e.g. f x sudo vim > sudo vim f(x) "
	echo "::                                               ::"
	echo ":: format of assoc file    3 values              ::"
	echo "::   field1 assoc  the associate to search for   ::"
	echo "::   field2 filename to act upon                 ::"
	echo "::   3 fields to prove override actions          ::"
	echo "::   If no parmlib/cmdlib the default is $myeditor"
	echo "::    (more info in the assoc file itself.)      ::"
	echo ":::::::::::::::::::::::::::::::::::::::::::::::::::"
	exit 
fi

# path to the assoc file
if [ ".$p1" == ".." ] ; then    # use  f .  to get to the assoc file
	$myeditor $assoc_file 
	exit
fi


found="no"   

# logic is processing a file looking for assoc to associate with a
# file and then take action.

#  while  line in file ; do
#     the processing (see comments below
#  done < assoc-file

#              assoc filename 3-actions rest 
#                 |     ||     |  |  |
while  read -r assoc filename a1 a2 a3  rest ; do

ech0 assoc $assoc filename $filename a1 $a1 a2 $a2 a3 $a3 rest $rest

#  if null-line skip it  (debug msg as null/blank line.)
#     if char1 of assoc is #  skip it  (debug msg as comment
#        if passed-val is assoc  mark found to bail 
#           if command_line(3) is null  process assocfile override
#                else if command_line(2)=sudo and (3)=null  sudo vim file
#                           else command_line(2+) is override_cmd

if [ "." != ".$assoc" ]; then             # null assoc => blank line
  if [ ${assoc:0:1}  != "#" ]; then       # char(1) of assoc => comment
    nop
    if [ "$p1" == "$assoc" ] ; then       # matching assoc ??
      found='yes'
      ech0 "found is now yes for " $assoc  $filename

      # handle assoclist line overrides 
      line_action=""                 # default assoclib override => null
        line_action=""
        if [ "." != ".$a1" ]; then line_action=$a1;fi
        if [ "." != ".$a2" ]; then line_action=$line_action" "$a2;fi
        if [ "." != ".$a3" ]; then line_action=$line_action" "$a3;fi

      break        # exit loop if found

    else
      ech0 "Onto the next line "
    fi
  else
    ech0 comment line
  fi
else
  ech0 blank line
fi
done < $assoc_file        # end read loop from given assoc file 

# NOT found msg and exit
if [ "$found" == "no" ] ; then
	echo "::                                               "
	echo ::  assoc  $p1  NOT found try . for assoclist 
	echo "::                                               "
	exit 4
fi

# Handle ~/whoever   to become     /home/$USER/whoever
if [ ${filename:0:1} == "~" ] ; then
	lead=$HOME              # now is /home/$USER   or   /root
	tailend=${filename:1}   # peel off the ~
	filename=$lead$tailend  # provide actual name 
fi

# handle the command line overrides
# remember p1 p2 p3 p4 prest  was cmd-line parse
cmd_ov=""                                     # default
if [ ".$p2" != "." ]; then cmd_ov="$p2";fi
if [ ".$p3" != "." ]; then cmd_ov="$cmd_ov $p3";fi
if [ ".$p3" != "." ]; then cmd_ov="$cmd_ov $p4";fi

echo "assoc: $p1, filename: $filename"
echo "default            : $myeditor"
echo "assoc line override: $line_action"
echo "cmdline override   : $cmd_ov"

cmd_action="$myeditor "                      #  set the default
if [ ".$line_action" != "." ]; then
  cmd_action=$line_action              # parm lib override
fi
if [ ".$cmd_ov" != "." ]; then     # commandline override
  cmd_action=$cmd_ov
fi
echo "Generated cmd: $cmd_action $filename"
$cmd_action $filename
