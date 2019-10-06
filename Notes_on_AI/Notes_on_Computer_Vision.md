# Notes on Computer Vision

The aim of computer vision is to detect the significant areas on an image, and then process those areas for a classification. This problem
is known as **segmentation**, and persons can do it inmidiately and efortless, due a great experience and kwnoledge, adquired in 
their childhood. 

Artificial vision is yet far away to match peoples performance; and the segmentation operation is done based in two or tree signals 
deduced from the image to study. Those signal can be the color, intensity, edges, movements, textures, patterns ... Following the most
common methods for 2D segmentation will be introduced.

# Threshold segmentation

A plausible option to discriminate the image of an object from its background, is taking into account the intensity of the light in the 
grey scale. 

In the case you have a color image, in a RGB format, you can actually calculate its intensity in gray scale, with the formula:

I_G (u,v) = 0.299·r + 0.587·g + 0.114·b  Forall (r,g,b):= I_RGB(u,v)

note that the reason, all the factors aren't equal, is due that the human eye, doesn't sense all the colors equally.

Continuing with the problem, for a given image in gray scale and a defined threshold t e (0,..q) a second imagen I' binarized can be
processed with the following algorithm. In that image the pixeles with intensity I'(u,v) = 0 represent the background of the scene. The pixels I'(u,v) = q represent the foreground.


```
ALGORITHM 1: Threshold Segmentation
===================================
Forall pixeles (u,v) in I do:
  I'(u,v) := 
               q if I(u,v)>=t (threshold)
               0 otherwise
end for
```
The algorithm can be also implemented the otherway arround: 

```
ALGORITHM 2: Inverse Threshold Segmentation
===========================================

Forall pixeles (u,v) in I do:
  I'(u,v) :=
              q if I(u,v)<= t (threshold)
              0 otherwise
end for
```

![Caballos](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_AI/images/threshold_segmentation.PNG)


The selection of the threshold t, can be at your own criteria, or automatically selected, usually the percentiles
10% and 90% give us robusts values for estimating the threshold t.

```
ALGORITHM 3: Threshold estimation (I, pmin, pmax)
==================================================
H := Calculate the histogram in grey scale (I) 
H := Calculate the accumulated histogram
min := calculate the percentile(Ha, pmin)
max := calculate the percentile(Ha, pmax)
t := (min+max)/2
```


Another strategy for the binarization of an image, is to use a different threshold for each pixel based in it color value, this is mainly a work based on the algorithms developed by Niblack and Sauvola, commonly used in OCR (Optical Character Recognition) applications. 

Niblack binarization threshold:

threshold(u,v) = M_w(u,v) + k·S_w(u,v)

Sauvola binarization threshold:

threshold(u,v) = M(u,v)·( 1 - k·( 1- (S_w(u,v)/R)))

Where the parameters are defined as:

 - threshold: local threshold at that grey scale value, for position pixel (u,v)
 - w: size of the evaluation window. It's actual size depends on the image size.
 - M_w: average value in the window w.
 - V_w: local variace in the window w.
 - S_w: Tipical desviation on window w.
 - k: constant value. For Niblack usually a value in the range [-1, -0.4]. For Sauvola around 0.5
 - R: dinamic range of the standar desviation. Sometimes is given the fixed value 128. Other times a better result is obtained with the value R=max(S_w(u,v)).
 
# Color Segmentation

When working on color images, not only the intensity, but also the color information can be used. For color segmentation, there are
several algorithms that take into account different factors, as the color model. Next a few algorithms are reviewed, they are simple,
and can be implemented with little effort, but they can give very good results.

The easiest idea, consists in define different fixed limits, in an HSV image, for the different channels. In a HSV image, the color information, is independent form the saturation or bright, so the definition of different ranges for each color is easy achivable, and returns a good result.

For the H channel, you should have into account, that it is defined as the angle in the range [0º,360º), so the start and end of the 
range, can be connected. That means that we can have two scenarios, i.e.:

```
    |  min->xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx<-max |
 0º |-----------------------------------------------------------------| 360º
    |xxxxxxx<- min                                       max ->xxxxxxx|
```


```
ALGORITHM 4: HSV color segmentation:
====================================

If h_max > h_min : then 

   For_all pixels(u,v) in I do:
                   /    
                   |     q  if:  h > h_min  AND  h < h_max AND s > s_min AND s < s_max AND v > v_min AND v < v_max
       I'(u,v):=  <
                   |     0  otherwise
                   \ 
   End For
   
Else

   For_all pixels(u,v) in I do:
      (h,s,v):= I(u,v)
                   /    
                   |     q  if:  (h > h_min OR h < h_max) AND s > s_min AND s < s_max AND v > v_min AND v < v_max
       I'(u,v):=  <
                   |     0  otherwise
                   \ 
   End For

End If
```

![COLOR SEGMENTATION BLUE](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_AI/images/Color_Segmentation_Matlab_BLUE.PNG)

![COLOR SEGMENTATION GREEN](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_AI/images/Color_Segmentation_Matlab_GREEN.PNG)

![COLOR SEMENTATION RED](https://github.com/sergiocollado/potpourri/blob/master/Notes_on_AI/images/Color_Segmentation_Matlab_RED.PNG)



Another possibility for color segmentation is based in the density function of a gaussian probability distribution of order _m_, whith 
**μ**, as the average value, and the covariance matrix **C**.

f(**x**) = ( 1 / ((2·Π)^(m/2))·sart(det(C)) ) · exp( -1/2 · (**x** - **μ**)^T · C^(-1) ·  (**x** - **μ**) ) 

for the case of m = 3 dimensions, -- red, green and blue -- and a trainning set of _n_ pixeles, **x_i** for all i ∈ {0,1, ... n}, and those pixeles, can be manually hand-picked to correspond to the desired color to be segemented; then the expected value **μ**, is the
arithmentic average of the trainnig set.

averg(**x**) = 1/n ∑ **x_n**

and the covariance matrix is:

**C** = 1/(n-1) · ∑  (**x_i** - avrg(**x**)) ·  (**x_i** - avrg(**x**))^T

When implementing this algorithm, in practice, the factor of the exponential function is ommited, and the value of the function
is checked against a threshold value, that have that factor implicit in it. 

















More on: https://homepages.inf.ed.ac.uk/rbf/HIPR2/wksheets.htm
