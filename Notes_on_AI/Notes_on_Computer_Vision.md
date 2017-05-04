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


