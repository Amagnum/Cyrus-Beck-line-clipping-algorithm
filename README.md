# Cyrus-Beck-line-clipping-algorithm
Cyrus Beck line clipping algorithm allows line clipping for non-rectangular windows

## Run:
```
g++ -I ./lib/eigen-3.3.9/Eigen 3dTransf.cpp -o 3d.exp
./3d.exp < 3d.in
```

## Input format 
```
poi
4
50 90 
70 110 
60 120 
40 80
1
25 105
85 105

win
0 8 0 4
1
-1 1
9 3

-------------------------
Type (win/poi)
Npoints / window (xmin,xmax, ymin, ymax)
px1 py1
...
#lines
P1_line1
P2_line1
---------------------------
```
