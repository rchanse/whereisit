#!/bin/bash

#Set default values
myeditor="vim"                         # choose your editor

base_dir="etc"                         # base index
if [ ! -d $HOME/$base_dir ]; then
  mkdir -pv $HOME/$base_dir
fi
parm_dir=$HOME/$base_dir

# IMPORTANT # # This code is to be use if you are invoking ech0 
# within a # script which has not internal  ech0 function.
#
# To use ech0 as an internal function within a script
# 1. copy it to the script   :r ech0   ( :r correct-dir/ech0 )
# 2. uncomment the last line of this block of comments.
# 3. uncomment the single  #}
#   2. and 3. will make an internal function eth0.
#
# 4. (OPTIONAL: remove the remaining comment lines.
#
 function ech0 () {     # turn on debugging with  export ech0=ON
  if [ ".$ech0" == ".ON" ]; then
    echo $@
  fi  
}
action=$1                                 # default for case
let count=$#
read -r action cmdp1 cmdp2 cmdp3 cmdp_rest <<< $@

NAMES_list=$parm_dir/gnamelist  # non-root file with list of names

# create is not existent
if [ ! -d $parm_dir ]; then
  echo "Creating $parm_dir directory (first time only)k"
  mkdir $parm_dir
  echo "Creating  $NAMES_list  (one time only)"
  echo " g(assoc)  ov1 ov2 ov3  rest " > $NAMES_list
fi


if [ -f $NAMES_list ]; then
  nl=`wc $NAMES_list | awk '{print $1}'`  
  # nl is the number of entries in list of names
fi

# list functions

# checking for an integer type value  found linuxquestion
function is_integer() {
  printf "%d" $1 > /dev/null 2>&1
  return $?
}

# checking for an integer is in range  between 1 and nl
function in_range() {
  if [ $1 -ge 1 ] && [ $1 -le $nl ] ; then
    return 0
  else
    return 1 
  fi
}

# used in show option to list NAMES_list entries and their assoc number
function list_by_number() { 
echo "List of names file " $NAMES_list "has" $nl "entries"

  if [ "$1." == '.' ]; then
    let start=1;let end=$nl;let index=1
  else
    let start=$1;let end=$start+9  # arrange for 10 lines
    if [ $end -gt $nl ]; then
      let end=$nl
    fi
    let index=$start
  fi
  echo "Range of entries from $start to $end"

  while [ $index -le $end ]; do
    thefile=`head -n$index $NAMES_list  | tail -n1`
    echo ">>"  $index  $thefile
    let index=$index+1
  done
 }

# end of functions


# start of mainline
action=none
ech0 "original  $action"
if [ ".$1" == "." ] || [ ".$1" == ".--help" ]; then 
   action=help
fi
ech0 "afterhelp $action"
if [ ".$1" == ".show" ]; then
  action=show
fi
ech0 "aftershow $action"
if [ ".$1" == ".0" ] || [ ".$1" == ".." ]; then 
  action=vimit
fi
ech0 "after vimit  $action"
if [ ".$1" == ".rep" ]; then
  action=overlay
ech0 $action
fi
ech0 "afterrep  $action"
if [ ".$1" == ".add" ]; then
  action=extend
fi
ech0 "$afteradd $action"
if [ ".$1" == ".q" ]; then
     echo locate $2
     locate $2 > ~/tempname
     wc ~/tempname
     g rep ~/tempname
     action=noop
fi
ech0 "afterq  $action"

case "$action" in

"noop" )
  ;;

"help" )   # provide syntax     no parms or parm1=help
  clear
  echo "  list file is $NAMES_list                 "
  echo "                                           "
  echo "      parm1  parm2 (maybe more)"
  
  echo "  g    (NULL)     - show this help/syntax "
  echo "       --help     - show this help/syntax "
  echo "       rep  file  - overlay list with file "
  echo "       add  file  - concat file to list    "
  echo "       show       - enumerat entire list   "
  echo "       show  n    - 10 entries in list  starting at n "
  echo "        .         - $myeditor $NAMES_list        "
  echo "        0         - $myeditor $NAMES_list        "
  echo "        n         - $myeditor entry n (unless parms 2, 3, 4 "
  echo "                   - are provided they override the $myeditor cmd "
  echo "                   - eg: g 4 rm -i  uses  rm -i 4-th file "
  echo "        q  value  - q(uickly)   locate value > $NAMES_list "
  echo "                                                           "
 ;;

"vimit" )
  $myeditor $NAMES_list       # /home/$USER/bin/gnamelistM
  ;;

"show" )
  list_by_number  $2
  ;;

"overlay" )
  echo "Replacing "$NAMES_list" with "$2
  echo "cat $2 > $NAMES_list"
  cat $2 > $NAMES_list
  ;;

"extend" )
  echo "Extend "$NAMES_list" with "$2
  cat $2 >> $NAMES_list
  ;;

 * )  # The default action  

if  is_integer $1; then
  if in_range $1; then
    theline=`head -n$1 $NAMES_list  | tail -n1`

    read -r thefile l1 l2 l3 linerest <<< $theline

    # parmlib override
    line_ov=""
    if [ ".$l1" != "." ]; then line_ov="$line_ov $l1"; fi
    if [ ".$l2" != "." ]; then line_ov="$line_ov $l2"; fi
    if [ ".$l3" != "." ]; then line_ov="$line_ov $l3"; fi
    
    # cmd_line override
    cmd_ov=""
    if [ ".$cmdp1" != "." ]; then cmd_ov="$cmd_ov $cmdp1";fi
    if [ ".$cmdp2" != "." ]; then cmd_ov="$cmd_ov $cmdp2";fi
    if [ ".$cmdp3" != "." ]; then cmd_ov="$cmd_ov $cmdp3";fi
    # handle the ~
    if [ ${thefile:0:1} == "~" ] ; then
      tailend=${thefile:1}
      thefile=$HOME$tailend
    fi
    cmd_action="$myeditor"        # the default
    echo "number: $1, file: $thefile"
    echo "default         : $cmd_action"
    echo "parmlib override: $line_ov"
    echo "command override: $cmd_ov"
    
    if [ ".$line_ov" != "." ]; then cmd_action=$line_ov;fi
    if [ ".$cmd_ov" != "." ]; then cmd_action=$cmd_ov;fi
    echo "Generated command: $cmd_action $thefile"
    $cmd_action $thefile 
    exit
  else
    echo $1 is NOT in RANGE  1 .. $nl
    exit
  fi
else
  echo "$1 is NOT and integer"
  echo "you hit the default - handle what is left"
  echo "how to handle  $1  is unknown "
fi
  ;;
esac
exit 0
