#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace cv;

/// Global variables

int threshold_value = 0;
int const max_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );

/**
 * @function main
 */
int main( int argc, char** argv )
{
  /// Load an image
  src = imread( argv[1], 1 );

  /// Convert the image to Gray
  cvtColor( src, src_gray, CV_RGB2GRAY );
  /// Create a window to display results
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );

  /// Call the function to initialize
  Threshold_Demo( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }

}


/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  Mat dst = src_gray.clone(); // (src_gray.cols, src_gray.rows, DataType<char>::type);

  int x_shift = 0;
  int y_shift = 0;

  for (int i = 0 ; i < dst.rows; i ++)
	for (int j = 0; j < dst.cols; j ++)
	{		

		if( (*(dst.ptr<char>(i) + j)) < 69)
		{
			*(dst.ptr<char>(i) + j) = 0;
		}
		else
		{
			 *(dst.ptr<char>(i) + j) = 255;
		}
		if((i < x_shift || i >= x_shift + 32) || (j < y_shift || j >= y_shift + 128))
		{
			*(dst.ptr<char>(i) + j) = 0;
		}

	}
//  threshold( src_gray, dst, threshold_value, 255, 0);

  imshow( window_name, dst );
}
