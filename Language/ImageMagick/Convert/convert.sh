#!/bin/bash

#功能: 
#说明: 

#---------------------------------------------------------------------------------------
# Helper Function
#---------------------------------------------------------------------------------------

#---------------------------------------------------------------------------------------
# Logic
#---------------------------------------------------------------------------------------
echo LogicStart--------------------------------------
convert rose.jpg rose.png
convert rose.jpg -resize 50% rose_resize.png
convert -size 320x85 canvas:none -pointsize 72 \
    -draw "text 25,60 'Magick'" -channel RGBA -blur 0x6 -fill darkred -stroke magenta \
    -draw "text 20,55 'Magick'" fuzzy-magick.png
