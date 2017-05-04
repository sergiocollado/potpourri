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
ALGORITHM 1: Threshold Segmentation:
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

![Caballos](../images/threshold_segmentation.PNG)
