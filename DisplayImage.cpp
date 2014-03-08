#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace cv;
#define N 512
/// Global variables

int threshold_value = 0;
int const max_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

unsigned char logo_buffer[N];
char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );
void myWaitKey()
{
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }
}

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
  myWaitKey();
}


/**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  Mat dst = src_gray.clone(); // (src_gray.cols, src_gray.rows, DataType<char>::type);

  int x_shift = 222; //Lena's eyes coordinates
  int y_shift = x_shift;

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
  myWaitKey();

  FILE* display = fopen("logo.bin", "r");
  fread(logo_buffer, sizeof(char), N, display);
  FILE* lena_display = fopen("lena.bin", "w");
  
  for(int j = y_shift + 127; j >= y_shift; j--)
  {
		for(int k = 0; k < 4; k++)
		{
			unsigned char byte = logo_buffer[128 * k - j + 127 + y_shift];
			unsigned char new_byte = 0;
		    
			for(int i = 0; i < 8; i++)
			{
				unsigned char temp = (byte & 1) * 255;
				unsigned char pixel = ((*(dst.ptr<char>(8 * k + i + x_shift) + j) +  256) % 256) / 255;
				*(dst.ptr<char>(8 * k + i + x_shift) + j) = temp;

				pixel = pixel << i;
				new_byte = new_byte | pixel;
				byte  = byte >> 1;
			}
			logo_buffer[128 * k - j + 127 + y_shift] = new_byte;
		}
  }

  fwrite(logo_buffer, sizeof(char), N, lena_display);
  imshow( window_name, dst );

  fclose(display);
  fclose(lena_display);
}
