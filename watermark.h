#include<cv.h>
#include<highgui.h>
#include<stdio.h>
void my_mouse_callback(int event,int x,int y,int flags,void *param);
IplImage* set_cop(IplImage *im);
IplImage* zoom_in(IplImage *orig,CvRect zoom_box);
void draw_box( IplImage *img,CvRect rect);
void trackbar_callback(int);

struct wateripl
{
	IplImage *img;
	IplImage *water;
};

