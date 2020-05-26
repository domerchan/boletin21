#include <iostream>
#include <cstdlib>

// Librerías de OpenCV 4
//#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <time.h>

using namespace std;
using namespace cv;

Mat original;
Mat gris;
Mat erosion;
Mat dilatacion;
Mat top;
Mat black;
Mat operacion;

void operacionTopHat(int, void*);
void operacionBlackHat(int, void*);

int main(int argc, char *argv[]){
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Gris", WINDOW_AUTOSIZE);
    namedWindow("Erosión", WINDOW_AUTOSIZE);
    namedWindow("Dilatación", WINDOW_AUTOSIZE);
    namedWindow("Top Hat", WINDOW_AUTOSIZE);
    namedWindow("Black Hat", WINDOW_AUTOSIZE);
    namedWindow("Original+(TH-BH)", WINDOW_AUTOSIZE);
    
    original = imread("images/imagen1.jpg", IMREAD_COLOR);
    //original = imread("images/imagen2.jpg", IMREAD_COLOR);
    //original = imread("images/imagen3.jpeg", IMREAD_COLOR);

    Mat estructura = getStructuringElement(MORPH_CROSS, Size(37,37));
 
    resize(original, original, Size(original.cols/2,original.rows/2));
    cvtColor(original, gris, COLOR_BGRA2GRAY);

    //SUAVIZADO//
    GaussianBlur(gris, gris, Size(3,3), 1);

    //EROSIÓN
    erode(gris, erosion, estructura);

    //DILATACIÓN
    dilate(gris, dilatacion, estructura);

    //TOP HAT
    operacionTopHat(0,0);

    //BLACK HAT
    operacionBlackHat(0,0);

    //ORIGINAL+(TOPHAT-BLACKHAT)
    operacion = gris+(top-black);

    imshow("Original", original);
    imshow("Erosión", erosion);
    imshow("Dilatación", dilatacion);
    imshow("Gris", gris);
    imshow("Original+(TH-BH)", operacion);

    waitKey(0);
    destroyAllWindows();
    return 0;
}

void operacionTopHat(int, void*) {
    //Cross = 1
    Mat element = getStructuringElement (1, Size(37,37), Point(18,18));
    //Top hat = 5
    morphologyEx(gris, top, 5, element);
    imshow("Top Hat", top);
}

void operacionBlackHat(int, void*) {
    //Cross = 1
    Mat element = getStructuringElement (1, Size(37,37), Point(18,18));
    //Black hat = 6
    morphologyEx(gris, black, 6, element);
    imshow("Black Hat", black);
}