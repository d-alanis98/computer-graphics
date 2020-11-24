#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "Please provide the duration of the animation in seconds"
    exit 1
fi

seconds=$((24 * $1))

for i in $(seq 1 $seconds);
do
    degrees=$((5 * $i))
    ./test prueba.obj $degrees > "animation/animation$i.ppm"
done

echo "Generating video"
ffmpeg -framerate 24 -i animation/animation%d.ppm animation/output.avi -start_number 1 -y

rm animation/*.ppm

exit 0