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

## Output
```
Boundary Points: (Always take ACKW rotation)
50 90
 70 110
 60 120
40 80
Noraml Vectors: (Pointing Inside)
     -0.707107  0.707107
     -0.707107 -0.707107
      0.894427 -0.447214
     -0.707107  0.707107

------- New Line --------
 P1: ( 25 105) ->  P2: ( 85 105)

 Wi = P1 - Qi
 t = - Wi.Ni / D.Ni
 D (P2-P1): 60  0

P_  D [   Nx Ny ]   [   Qx Qy ]   [   Wx Wy ] |   N.W |   N.D |  Tmin |  Tmax |
 -------------------------------------------------------------------------- 
PL   [   -0.707107  0.707107 ]   [   50 90 ]   [   -25  15 ] | 28.2843 | -42.4264 |     0 | 0.666667 | ( Tmin Tmax ) = 0 0.666667
PL   [   -0.707107 -0.707107 ]   [    70 110 ]   [   -45  -5 ] | 35.3553 | -42.4264 |     0 | 0.833333 | ( Tmin Tmax ) = 0 0.833333
PE   [    0.894427 -0.447214 ]   [    60 120 ]   [   -35 -15 ] | -24.5967 | 53.6656 | 0.458333 |     0 | ( Tmin Tmax ) = 0.458333 1
PL   [   -0.707107  0.707107 ]   [   40 80 ]   [   -15  25 ] | 28.2843 | -42.4264 |     0 | 0.666667 | ( Tmin Tmax ) = 0 0.666667
 tmin: (52.5  105) t: 0.458333
 tmax: ( 65 105) t: 0.666667

```
