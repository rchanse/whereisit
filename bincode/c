#!/bin/bash 	
#
function ech0 () {     # turn on debugging with  export ech0=ON
  if [ ".$ech0" == ".ON" ]; then
    echo $@
  fi  
}

#  first make sure there is a parm
if [ ".$1" == "." ] ; then
  found="yes"
  cat << EOF-usage
usage: quick change to another director by assoc

syntax;
 . c  parm
   parm1  null - this help info
          .    - view/alter the assoclist
	      - , old, back - all act like  cd -  back prev dir \$OLDDIR
	                  Note this is a toggle  prev-dir and current-dir
          other - search c_assoclist to see which dir. to use in cd 

EOF-usage
return
fi
if [ "$1" == "old" ] || [ "$1" == "back" ] || [ "$1" == "-" ]; then
   echo "Remember '-', 'old' and 'back' are special to return to the" 
   echo "calling cd-dir, so  returning to $OLDPWD"
   cd $OLDPWD
   return
fi

assoc_to_find=$1
c_dir=/home/$USER/bintest    # if in bintest
c_dir=/home/$USER/bin        # if in bin
c_dir=/home/$USER/etc        # if in bin

#c_dir=$rchbls           # for whereisit system to get this into
                        # ~/bin comment out this line.

found="nope"
# special case to edit the list of assocnyms
if [ ".$1" == ".." ] ; then 
  echo " editing the 'c' script to view/alter the list "
# vim $c_dir/c      # <<<-- this much change  org was cd0
  echo vim $c_dir/c_assoclist      # <<<-- this much change  org was cd0
  vim $c_dir/c_assoclist      # <<<-- this much change  org was cd0
  found="yes"
  return
fi

# set the second parm and make certain only certain one are used

if [ ".$2" == "." ]; then
  action="cd"
else
  echo "need proper action in parm 2 - null"
  found="yes"     # kill end  not found mismessage
  return
fi

assoc_found="no"
line_item=''
ech0 "\$line_item = $line_item."
while [ ".$assoc_found" == ".no" ] && 
 read line_item  ; do
# while  read line_item  ; do
  ech0 $line_item
  IFSsave=$IFS
  IFS=" "

  # adding to the parse so items 3+ are for documentation
  read assoc_item new_dir_item doc_info<<< $line_item

  IFS=$IFSsave
# ech0 "dir_new_item=$dir_new_item, arco_item=$assoc_item,
if [ ".$assoc_item" == ".$assoc_to_find" ]; then
  ech0 "$assoc_to_find in c_assoclis at line: $line_item"
  echo "FOUND: $assoc_to_find : $new_dir_item :: $doc_info "
  ## convert '~' to full name
  if [ ${new_dir_item:0:1} == "~" ]; then
    lead=$HOME
    tailend=${new_dir_item:1}
    new_dir_item=$lead$tailend
  fi
  ## check to see if new directory exists.
  answer=FALSE
    if [ -e $new_dir_item ]; then
      if [ -d $new_dir_item ]; then
        ech0 $new_dir_item exists as a directory
        answer=TRUE
      else
        ech0 $new_dir_item exists but NOT as a directory
      fi
    else
      echo $new_dir_item doe not exist
    fi
  if [ ".$answer" == ".FALSE" ]; then
    echo "Quiting No work done."
    echo
    return 2
  fi

    
  ## check to see if new directory exists.
  assoc_found="yes"
  echo "change to $new_dir_item  (which EXISTs)"
  OLDPWD=$PWD               # remember where I came from
                            # in case I want to go back
  ech0 "cd $new_dir_item"                   
                            # also cannot use $0 this becomes bash
  cd $new_dir_item                   
    
  ech0 "PWD=$PWD"
else
  ech0 ".$assoc_item. <> .$assoc_to_find. "
fi
done <   $c_dir/c_assoclist      # <<<-- this much change  org was cd0

# fall through to message that cd path not found 
if [ ".$assoc_found"  == ".no" ]; then
     echo
     echo "$assoc_to_find NOT FOUND  as an cd path "
     echo "Check your typing  or look  '. c .'"
fi

