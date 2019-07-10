#include <opencv2/opencv.hpp>
#include <iostream>


using namespace cv;
using namespace std;


std::string get_tegra_pipeline(int width, int height, int fps) {
    return "nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)" + std::to_string(width) + ", height=(int)" +
            std::to_string(height) + ", format=(string)NV12, framerate=(fraction)" + std::to_string(fps) +
            "/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink";
}


int main()
{   
    // Options
    int WIDTH = 1920;
    int HEIGHT = 1080;
    int FPS = 30;
	Mat img_color;

    // Define the gstream pipeline
    std::string pipeline = get_tegra_pipeline(WIDTH, HEIGHT, FPS);
    std::cout << "Using pipeline: \n\t" << pipeline << "\n";

	//���� ĸ�� �ʱ�ȭ
	VideoCapture cap(pipeline);
	if (!cap.isOpened()) {
		cerr << "���� - ī�޶� �� �� �����ϴ�.\n";
		return -1;
	}

	// ������ ������ �����ϱ� ���� �غ�  
	Size size = Size((int)cap.get(CAP_PROP_FRAME_WIDTH),
		(int)cap.get(CAP_PROP_FRAME_HEIGHT));

	VideoWriter writer;
	double fps = 30.0;
	writer.open("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, size, true);
	if (!writer.isOpened())
	{
		cout << "�������� �����ϱ� ���� �ʱ�ȭ �۾� �� ���� �߻�" << endl;
		return 1;
	}


	while(1)
	{
		cap.read(img_color);
		if (img_color.empty()) {
			cerr << "�� ������ ĸ�ĵǾ����ϴ�.\n";
			break;
		}

		//������ ���Ͽ� �� �������� ������.  
		writer.write(img_color);

		imshow("Color", img_color);

		if (waitKey(25) >= 0)
			break;


	}
	

	return 0;
}