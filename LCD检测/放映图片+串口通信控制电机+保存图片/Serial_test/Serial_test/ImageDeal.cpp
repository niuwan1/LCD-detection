#include"ImageDeal.h"


void ImageShow(int num)
{
	char filename[100];
	char windowname[100];
	int i = num;
	sprintf(filename, "�������ڰ�\\%d.jpg", i);// ��ͼƬ����������������1.jpg 2.jpg�ȣ�����D:/test/�ļ�����
	//printf("filename is %d\n", i);
	sprintf(windowname, "window%d.jpg", i);
	IplImage* src = cvLoadImage(filename, 1);//����ͼƬ
	if (!src)
	{
		printf("err");
	}
	cvNamedWindow("src", CV_WND_PROP_FULLSCREEN);
	//cvResizeWindow("src", 2436, 1624);
	cvSetWindowProperty("src", CV_WND_PROP_FULLSCREEN, CV_WINDOW_FULLSCREEN);
	cvShowImage("src", src);

	ShowCursor(FALSE);//����ԭ���Ĺ��
	//SetCursor(hcursor);//�����µĹ��
	//ShowCursor(TRUE);//��ʾ�µĹ�� 

	//cvWaitKey(5000);
	//cvReleaseImage(&src);
	//cvDestroyWindow("src");

}