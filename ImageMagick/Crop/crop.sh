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
imageWidth=$(identify -format "%w" sample.png)
imageHeight=$(identify -format "%h" sample.png)
echo "$imageWidth"x"$imageHeight"
newImageWidth=100
newImageHeight=100

convert -crop "100x100" sample.png dest.png
convert -crop $newImageWidth"x"$newImageHeight"+"50"+"50 sample.png dest1.png
convert -crop $newImageWidth"x"$newImageHeight"+"100"+"100 sample.png dest2.png
convert -crop $newImageWidth"x"$newImageHeight"+"100"-"50 sample.png dest3.png