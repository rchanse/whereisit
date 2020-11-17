#!/bin/bash

# debugging I left in the debugging echos but you can turn then on/off
# to turn them on   from cmd line  enter  export eth0="ON"
# to turn then back off                   export eth0=anythingbut_ON
# Note: export eth0= cmds may be before invoking f or you can
#  add then within the code to turn debugging on/off in spots.

editor="vim"                # set the default editor

#  if [ ".$fdebug" == ".ON" ]; then
  # whaterever echo stmt you wish
#  fi

function ech0 () {               # set  debug=ON  export debug
  if [ ".$debug" == ".ON" ]; then
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

#  Below is the acro file (name of acro filename action    file )
acro_file=$HOME"/bin/ff_acrolist"
acro_file=$HOME"/oin/f_acrolist"
if [ -f $HOME/rchtest/f_acrolist ]; then
  acro_file=$HOME/rchtest/f_acrolist
else
  acro_file=$HOME/rchbuild/f_acrolist
fi

# save cmdline parms for later
p1=$1                         # first parm
if [ ".$2" == "." ]; then     # see if there is more than one parm
	p2=""                     # nope
else
    orig2=$2          # prep for check of  f acro sudo
    orig3=$3          #   when third parm is null
	shift
	p2=$@                     # obtain rest of cmdline
fi

#  Help info
if [ ".$p1" == "." ] ; then
    echo "parmfile  :>"$acro_file 
	echo ":::::::::::::::::::::::::::::::::::::::::::::::::::"
	echo "::  f -  quick invocation to file                ::"
	echo "::  f parm1 p2 p3 p4                             ::"
	echo "::    parm1                                      ::"
	echo "::      null   - display this help info          ::"
    echo "::      .      - go edit the acro list file      ::"
	echo "::      other  - acro for filename in acro_file  ::"
	echo "::    p2 p3 p4 - action to take default editor   ::"
	echo "::               e.g. f x sudo vim > sudo vim x  ::"
	echo "::                                               ::"
	echo ":: format of acro file    3 values               ::"
	echo "::   field1 acro  the acronym to search for      ::"
	echo "::   field2 filename to act upon                 ::"
	echo "::   field3 action to take  null  editor         ::"
	echo "::    (more info in the acro file itself.)       ::"
	echo ":::::::::::::::::::::::::::::::::::::::::::::::::::"
	exit 
fi

# path to the acro file
if [ ".$p1" == ".." ] ; then    # use  f .  to get to the acro file
	$editor $acro_file 
	exit
fi


found="no"   

# logic is processing a file looking for acronym to associate with a
# file and then take action.

#  while  line in file ; do
#     the processing (see comments below
#  done < acro-file

# while  read -r acro filename action rest ; do
while  read -r acro filename a1 a2 a3 rest ; do

#if [ ".$fdebug" == ".ON" ]; then
ech0 acro $acro filename $filename a1 $a1 a2 $a2 a3 $a3 rest $rest
#fi

#  if null-line skip it  (debug msg as null/blank line.)
#     if char1 of acro is #  skip it  (debug msg as comment
#        if passed-val is acro  mark found to bail 
#           if command_line(3) is null  process acrofile override
#                else if command_line(2)=sudo and (3)=null  sudo vim file
#                           else command_line(2+) is override_cmd

if [ "." != ".$acro" ]; then             # null acro => blank line
  if [ ${acro:0:1}  != "#" ]; then       # char(1) of acro => comment
    nop
    if [ "$p1" == "$acro" ] ; then       # matching acro ??
      found='yes'
      ech0 "found is now yes for " $acro  $filename

      line_action=""                 # default acrolib override => null
      command_override=""            # default cmdline overrid => null
      if [ ".$p2" == "." ]; then     # p2 null => no cmd line to process
        nop
        ech0 no cmdline
        line_action=""
        if [ "." != ".$a1" ]; then line_action=$a1;fi
        if [ "." != ".$a2" ]; then line_action=$line_action" "$a2;fi
        if [ "." != ".$a3" ]; then line_action=$line_action" "$a3;fi
        if [ "." != ".$rest" ]; then line_action=$line_action" "$rest;fi
        ech0 Built override by acro_lib"."$line_action"."
      else
        nop
        ech0 ">>"$orig2"<<>>"$orig3"<<"
        ech0 check for single sudo
        if [ ".$orig2" == ".sudo" ] && [ ".$orig3" == "." ]; then 
          command_override="sudo "$editor
        else
          command_override=$p2
        fi
      fi

      ech0 pre break  ">"$line_action"<>"$command_override"<"
      break        # exit loop if found

    else
      nop
      ech0 "Onto the next line "
    fi
  else
    ech0 comment line
  fi
else
  ech0 blank line
fi
done < $acro_file        # end read loop from given acro file 

# NOT found msg and exit
if [ "$found" == "no" ] ; then
	echo "::                                               "
	echo ::  acronym  $p1  NOT found try . for acrolist 
	echo "::                                               "
	exit 4
fi

# The actual file to work on 

# Handle ~/whoever   to become     /home/$USER/whoever
if [ ${filename:0:1} == "~" ] ; then
	lead=$HOME              # now is /home/$USER   or   /root
	tailend=${filename:1}   # peel off the ~
	filename=$lead$tailend  # provide actual name 
fi

echo "acro line override:"$line_action
echo "cmdline override:" $p2
echo "acro:"$p1", filename:"$filename

# Set the cmd_action value        
cmd_action="$editor "                      #  set the default
ech0 1 $cmd_action  ">"$line_action"<"
if [ ".$line_action" != "." ]; then
  cmd_action=$line_action              # parm lib override
fi
ech0 2 $cmd_action
if [ ".$command_override" != "." ]; then     # commandline override
  cmd_action=$command_override
fi
ech0 3 $cmd_action
echo $cmd_action $filename
$cmd_action $filename
