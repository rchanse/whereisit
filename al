#!/bin/bash

if [ ".$1" == ".un" ]; then
    unalias ..
    unalias path
    unalias now
    unalias p3
    unalias v1
    unalias v2
    unalias hal
    unalias varshow
    unalias cdx
    unalias cdb
else
    alias ..='cd ..'
    alias path='echo -e ${PATH//:/\\n}'
    alias now='date +"%T"'
    alias p3='ping -c 3 '
    alias v1='vim  tempname'
    alias v2='vim ~/tempname'
    alias hal='ls -alh '
    alias varshow='echo \$rchjlp is $rchjlp'
    alias cdx='cd ~/$rchjlp'
    alias cdb='cd ~/whereis'
fi
