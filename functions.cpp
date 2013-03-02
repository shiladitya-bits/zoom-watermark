#include "watermark.h"
IplImage* set_cop(IplImage *im)
{
	IplImage *test=cvCreateImage(cvGetSize(im),im->depth,im->nChannels);
	//IplImage *test=cvCloneImage(im);
	
	cvCvtColor(im, test, CV_BGR2HSV); //from RGB to HSV
	IplImage *h,*s,*v;
	
	h=cvCreateImage(cvGetSize(test),test->depth,1);
	s=cvCreateImage(cvGetSize(test),test->depth,1);
	v=cvCreateImage(cvGetSize(test),test->depth,1);

	cvSplit(test,h,s,v,NULL);
	IplImage *copyright=cvLoadImage("bisaag.png",0);
	cvSetImageROI(v,cvRect(0,0,100,50));

	cvNamedWindow("intensity",CV_WINDOW_AUTOSIZE);
	cvShowImage("intensity",copyright);
	
	printf("channels of bisag=%d depth of bisag=%d\n",v->roi->height,v->roi->width);
	uchar *vdata=(uchar *)v->imageData;
	uchar *hdata=(uchar *)h->imageData;
	uchar *sdata=(uchar *)s->imageData;

	uchar *copdata=(uchar *)copyright->imageData;
	//cvAddWeighted(v,0.5,copyright,0.5,0.0,v);

	for( int i=0;i<50;i++)
	{
		for(int j=0;j<100;j++)
		{
			if(  copdata[i*100+j] <200)
			{
				//vdata[ (i * im->width) + j]=(int)(vdata[i*copyright->width + j]*0.6 + copdata[i*100+j]*0.4 + 0.5);
				if( vdata [i*im->width + j] > 20 ) 
					vdata[ (i * im->width) + j]=(int)(copdata[i*100+j]*0.45+vdata[i*im->width+j]*0.55);
				else
				{
					vdata[ (i * im->width) + j]=(int)((255-copdata[i*100+j])*0.3);
					hdata[ (i * im->width) + j]=0;
					sdata[ (i * im->width) + j]=0;

				}
			}
		}
	}
	
	cvResetImageROI(v);
	
	cvMerge(h,s,v,NULL,test); //merging new components
	
	cvCvtColor(test, test, CV_HSV2BGR); //from HSV to RGB
	
	return test;
	
}

// function to zoom in to selected rectangle!
IplImage* zoom_in(IplImage *orig,CvRect zoom_box)
{
	IplImage *im=cvCloneImage(orig);
	int height=im->height,width=im->width;
	IplImage *imnew=cvCreateImage(cvSize(width,height),8,3);
	
	cvSetImageROI(im,zoom_box);
	
	cvResize(im,imnew);
	
	cvResetImageROI(im);

	return imnew;
}
