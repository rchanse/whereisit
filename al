#!/bin/bash

if [ ".$1" == ".un" ]; then
    unalias ..
    unalias cdb
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
    alias cdb='cd ~/whereis'
    alias cdx='cd ~/$rchjlp'
    alias cnx='chmod -x '    
    alias cx='chmod +x '    
    alias hal='ls -alh '
    alias now='date +"%T"'
    alias p3='ping -c 3 '
    alias path='echo -e ${PATH//:/\\n}'
    alias v1='vim  tempname'
    alias v2='vim ~/tempname'
    alias varshow='echo \$rchjlp is $rchjlp'
fi
