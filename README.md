# Image filtering
Implement filters to an image to create different visual effects.

## Overview
Filtering an image is like taking the pixels of some original image and modifying each pixel in such a way that a particular effect is apparent in the resulting image. In this project, the image is a '.bmp' file.

### Filters
1. Grayscale('g'): convert an image to black-and-white while maintaining the same brightness or darkness as the old image
2. Reflection('r'): Like placing the image in front of a mirror. Any pixels on the left side should end up on the right side
3. Sepia('s'): gives images an old-timey feel by making the whole image look a bit reddish-brown
4. Blur('b'): creates the effect of blurring or softening an image 
5. Edges('e'): detects edges in an image and creates a boundary between one object and another

### Code Structure
- *bmp.h : defines a struct called RGBTRIPLE which encapsulates three bytes: one blue, one green, one red. 
- *filter.c: main file. 
- *helpers.h: helper file provides function prototypes for the function I worked with. 
- *Makefile: specifies what should happen when we run a terminal command. 
- helpers.c: implementation of the functions declared in helpers.h.
- *are files have been written by cs50.

### Installing
Online C complier [CS50 IDE](https://ide.cs50.io/).

### Implementation
Compiling
```
$ make filter 
```
Run the program by running:
```
$./filter -g images/infile.bmp outfile.bmp 
$./filter -r images/infile.bmp outfile.bmp 
$./filter -s images/infile.bmp outfile.bmp 
$./filter -b images/infile.bmp outfile.bmp 
$./filter -e images/infile.bmp outfile.bmp
```


CS50 filter project link:[CS50 filter](https://cs50.harvard.edu/x/2020/psets/4/filter/less/)


