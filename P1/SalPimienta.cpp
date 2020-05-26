#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

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

#define PI 3.14159

void eventoTrack(int v, void *p){
    cout << "Valor: " << v << endl;
}

int main(int argc, char *argv[]){
    //Captura de video
    string nombreVideo = "alien.mp4";
    namedWindow("Video Original", WINDOW_AUTOSIZE);
    VideoCapture video(nombreVideo);
    
    int sal = 0;
    int pimienta = 0;

    if(video.isOpened()){
        Mat frame;
        Mat gausMat;
        Mat medMat;
        Mat borMat;
        Mat suavizadoMat;
        
        createTrackbar("Ruido de Sal: ", "Video Original", &sal, 100, eventoTrack, NULL);
        createTrackbar("Ruido de Pimienta: ", "Video Original", &pimienta, 100, eventoTrack, NULL);
        
        while(3==3){
            video >> frame;

            cvtColor(frame, frame, COLOR_BGR2GRAY);
            double porcentajeSal = (double)sal/100;
            double porcentajePimienta = (double)pimienta/100;
            int totalRuidoPimienta = ((int) (porcentajePimienta * ((double) frame.rows*frame.cols)));
            int totalRuidoSal = ((int)(porcentajeSal * ((double) frame.rows*frame.cols)));
            srand(time(NULL));

            int x=0, y=0;
            for(int i=0; i<totalRuidoSal; i++){
                y = rand() % frame.rows;
                x = rand() % frame.cols;
                frame.at<uchar>(y,x) = 255;
            }

            int j=0, k=0;
            for(int i=0; i<totalRuidoPimienta; i++){
                k = rand() % frame.rows;
                j = rand() % frame.cols;
                frame.at<uchar>(k,j) = 0;
            }
            
            medianBlur(frame, medMat, 13);
            GaussianBlur(frame, gausMat, Size(11,11), 13);

            Laplacian(gausMat, borMat, CV_8UC1, 7);
            //Canny(gausMat, borMat, 53, 53*3, 3);
            //Sobel(gausMat, borMat, CV_8UC1, 1, 0, 7);
            


            //imshow("Video Original", frame);
            //imshow("Gausiano", gausMat);
            //imshow("Mediana", medMat);
            imshow("Bordes", borMat);

            
            if(waitKey(23)==27)
                break;
        }      
    }

    destroyAllWindows();
    return 0;
}