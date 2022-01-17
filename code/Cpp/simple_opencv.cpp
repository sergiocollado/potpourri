// to install opencv in a raspberry pi 4
// reference: https://millo-l.github.io/Install-Opencv-4-on-Raspberry-Pi-4/
/*
# Installing opencv-4.1.0 tar
wget https://github.com/sol-prog/raspberry-pi-opencv/releases/download/opencv4rpi2.1/opencv-4.1.0-armhf.tar.bz2

# Decompression
tar xfv opencv-4.1.0-armhf.tar.bz2

# Move uncompressed folder path
sudo mv opencv-4.1.0 /opt

# remove opencv-4.1.0 tar
rm opencv-4.1.0-armhf.tar.bz2

# Install Modules for Using Opencv
sudo apt install libgtk-3-dev libcanberra-gtk3-dev
sudo apt install libtiff-dev zlib1g-dev
sudo apt install libjpeg-dev libpng-dev
sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt-get install libxvidcore-dev libx264-dev
sudo apt install python-numpy python3-numpy

# .bashrc settings
echo 'export LD_LIBRARY_PATH=/opt/opencv-4.1.0/lib$LD_LIBRARY_PATH' >> .bashrc
. .bashrc
sudo ln -s /opt/opencv-4.1.0/lib/python2.7/dist-packages/cv2 /usr/lib/python2.7/dist-packages/cv2
sudo ln -s /opt/opencv-4.1.0/lib/python3.7/dist-packages/cv2 /usr/lib/python3/dist-packages/cv2

# Install git and clone from github
sudo apt install git
git clone https://gist.github.com/sol-prog/ed383474872958081985de733eaf352d opencv_cpp_settings

# settings
cd opencv_cpp_settings
sudo cp opencv.pc /usr/lib/arm-linux-gnueabihf/pkgconfig/

# remove folder
cd ~
rm -rf opencv_cpp_settings

# Verify opencv Installation
git clone https://github.com/sol-prog/raspberry-pi-opencv
cd raspberry-pi-opencv
cd tests
python3 gui_python_test.py
*/

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
int main(int argc, char** argv)
{
        VideoCapture cap;
        //open default camera, use something different than 0 otherwise
        //Check VideoCapture documentation
        std::cout << "Press ESC to finish the program\n";
        std::cout << "Using opencv version: " << CV_VERSION << "\n";

        if(!cap.open(0))
                return 0;
        for(;;)
        {
                Mat frame;
                cap >> frame;
                if( frame.empty()) break; //end of video stream
                imshow("this is you, smile! :)", frame);
                if ( (waitKey(10)%256) == 27) break; //waitkeypatch: check for 10ms: then stop capturing by pressing ESC=27
        }
        // the camera will be closed automatically upon exit
        return 0;
}

// to compile: g++ cam_tst.cpp -o test `pkg-config --cflags --libs opengcv`




