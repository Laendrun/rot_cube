# ROT_CUBE (Rotating Cube)

This project was inspired by [Daniel Shiffmann](https://github.com/shiffman).

I wanted to try and recreate one of his coding challenge in C using MiniLibX.

[Coding Challenge #112: 3D Rendering with Rotation and Projection](https://youtu.be/p4Iz0XJY-Qk)

## Description

This project "simply" makes a 2D projection of some 3D points representing a cube.

This makes use of matrices maths to multiply the points matrices by a rotation matrix and also a projection matrix.

## Usage

> Note that I did this on a MacBook so the MiniLibX that is included in this project might not work on your computer.

> Search for MiniLibX to find more information about it and how to run it on different OS.

1. Clone the repository.
1. ```cd``` in the directory.
1. Run ```make```.

This compiles the project and the micro matrices "library" I built and used for this project.

You can then run the program using one of the following commands :

```sh
./rot_cub

./rot_cub <distance>

./rot_cub <scale> <distance>
```

The first one simply runs the program with a distance set to ```1``` by default.

The second one let's you specify a distance for the perspective.

The third one let's you specify a scaling for the cube (default: 100), and a distance.

(I will maybe add some other variants later).

## Warnings

:warning: There will surely be some memory leaks, I didn't check that for now.

:warning: There could be some weird things happening if you scale the cube up enough to go around the edges, I didn't do anything to check that.
