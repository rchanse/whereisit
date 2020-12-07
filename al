#!/bin/bash

shopt -s expand_aliases

if [ ".$1" == ".un" ]; then   # don't seem to work ?? tbd
    unalias ..
    unalias cdb
    unalias cdn
    unalias cdx
    unalias cnx
    unalias cx
    unalias hal
    unalias now
    unalias p3
    unalias path
    unalias v1
    unalias v2
    unalias varshow
else
   alias ..='cd ..'
   if [ ".$rchbls" != "." ]; then
     alias cdn='cd ~/newtest'
     echo "\$rchbls = $rchbls"
     read build_dir rest < $rchbls/builddir
     read exec_dir  rest < $rchbls/execdir
     echo "build-dir = $build_dir, exec-dir = $exec_dir"
     echo "alias cdx='cd $exec_dir'"
     alias cdx='cd $exec_dir'             # to exec-lib dir.
     echo "alias cdb='cd $build_dir'"
     alias cdb='cd $build_dir'            # to build-lib dir.
   fi
   alias cnx='chmod -x '    
   alias cx='chmod +x '    
   alias hal='ls -alh '
   alias now='date +"%T"'
   alias p3='ping -c 3 '
   alias path='echo -e ${PATH//:/\\n}'
   alias v1='vim  tempname'
   alias v2='vim ~/tempname'
   alias varshow='echo \$rchbls is $rchbls'
fi
