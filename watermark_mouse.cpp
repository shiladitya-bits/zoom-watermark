
#include "watermark.h"
//define our callback which we will install for mouse events

IplImage* zoom_in(IplImage *orig,CvRect zoom_box);
IplImage* set_cop(IplImage *im);

int zoom_level=0;
CvRect box;
bool drawing_box = false;
IplImage *tada;

int k=0;
char abc[50];

// a little subroutine to draw a box onto an image
void draw_box( IplImage *img,CvRect rect)
{
	cvRectangle(img,cvPoint(box.x,box.y),cvPoint(box.x+box.width,box.y+box.height),cvScalar(0xff,0x00,0x00));	//blue
}
int main()
{	
	box = cvRect(-1,-1,0,0);
	char name[100];
	
	IplImage *tmp=cvLoadImage("kolkata.jpg");
	tada=set_cop(cvCloneImage(tmp));
	//sprintf(abc,"file%d",k++);
	//cvSaveImage(abc,tada);

	struct wateripl *wat=(struct wateripl *)malloc(sizeof(struct wateripl *));
	wat->img=tmp;
	wat->water=tada;
	
	IplImage *temp=(cvCloneImage(wat->img));
	
	cvNamedWindow("box example",CV_WINDOW_AUTOSIZE);
	cvNamedWindow("zoom output",CV_WINDOW_AUTOSIZE);
	
	cvSetMouseCallback("box example",my_mouse_callback,(void *)wat);

	while(1)
	{
		cvCopyImage(wat->water,temp);
		if( drawing_box ) draw_box( temp,box );
		cvShowImage("box example",temp);          //changed
		
		cvShowImage("zoom output",tada);
		if(cvWaitKey(15) == 27 ) break;
	}

	//cvReleaseImage(&image);
	cvReleaseImage(&temp);
	cvDestroyWindow("box example");
	return 0;
}

void my_mouse_callback( int event,int x,int y,int flags, void *param)
{
	struct wateripl *ww=(struct wateripl *)param;
	IplImage *image=ww->img;
	switch(event)
	{
	case CV_EVENT_MOUSEMOVE:
		{
			if(drawing_box )
			{
				box.width=x-box.x;
				box.height=y-box.y;
			}
			
		}
		break;
		case CV_EVENT_LBUTTONDOWN: 
		{
			drawing_box = true;
			box = cvRect(x, y, 0, 0);
			//tada=zoom_in(image,cvRect(x-100,y-100,200,200));

		}
		break;	
	case CV_EVENT_LBUTTONUP: 
		{
			drawing_box = false;
			if(box.width<0) 
			{
				box.x+=box.width;
				box.width *=-1;
			}
			if(box.height<0) 
			{
				box.y+=box.height;
				box.height*=-1;
			}
			//draw_box(image, box);
			tada=set_cop(zoom_in(image,box));
			//sprintf(abc,"file%d",k++);
			//cvSaveImage(abc,tada);
		}
		break;
	}
}
