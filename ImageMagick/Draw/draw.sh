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
# Single Pixel Draw  (two ways -- these have been enlarged)

# Point 'paints' the color pixel
convert -size 10x6 xc:skyblue  -fill black \
-draw 'point 3,2'         -scale 100x60   draw_point.gif

# Color Point 'replaces' the color pixel
convert -size 10x6 xc:skyblue  -fill red \
-draw 'color 6,3 point'   -scale 100x60   draw_color_point.gif


  # Rectangle  /  Rounded Rectangle  /  Rectangular Arc

  convert -size 100x60 xc:skyblue -fill white -stroke black \
          -draw "rectangle 20,10 80,50"       draw_rect.gif

  convert -size 100x60 xc:skyblue -fill white -stroke black \
          -draw "roundrectangle 20,10 80,50 20,15"  draw_rrect.gif

  convert -size 100x60 xc:skyblue -fill white -stroke black \
          -draw "arc  20,10 80,50  0,360"     draw_arc.gif

  convert -size 100x60 xc:skyblue -fill black -stroke black \
          -draw "arc  20,10 80,50 45,270"     draw_arc_partial.gif

  convert -size 320x420 xc:lightblue -pointsize 70 \
      -fill red -stroke none                 -draw 'text 30,80  "Stroke -"' \
      -fill red -stroke black -strokewidth 0 -draw 'text 30,160 "Stroke 0"' \
      -fill red -stroke black -strokewidth 1 -draw 'text 30,240 "Stroke 1"' \
      -fill red -stroke black -strokewidth 2 -draw 'text 30,320 "Stroke 2"' \
      -fill red -stroke black -strokewidth 3 -draw 'text 30,400 "Stroke 3"' \
      stroke_table.jpg


  convert -background lightblue  -fill blue  -pointsize 20 \
          label:'ImageMagick\nRules - OK!'     label_multiline.gif