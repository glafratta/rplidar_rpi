#include "a1lidarrpi.h"

class DataInterface : public A1Lidar::DataInterface {
public:
	FILE * f;
	int counter=0;
    char fileName[256];

	DataInterface(){
	// //TODAYS DATE AND TIME
    time_t now =time(0);
    tm *ltm = localtime(&now);
    int y,m,d;
    y=ltm->tm_year-100;
    m = ltm->tm_mon +1;
    d=ltm->tm_mday;
    sprintf(fileName, "scan%02i%02i%02i_%02i%02i", d,m,y, ltm->tm_hour, ltm->tm_min);
	f=fopen(fileName, "w+");
	fclose(fileName);

	}
	void newScanAvail(float,A1LidarData (&data)[A1Lidar::nDistance]) {
		f=fopen(fileName, "a");
		for(A1LidarData &data: data) {
			if (data.valid)
				fprintf(f, "%.2f\t%.2f\n",
				       data.x,
				       data.y,
);
		}
		counter++;
		fclose(fileName);
	}
};

int main(int, char **) {
	fprintf(stderr,"prints x, y coordinates approximated to the second decimal\n");
	A1Lidar lidar;
	DataInterface dataInterface();
	lidar.registerInterface(&dataInterface);
	lidar.start();
	do {
	} while (dataInterface.counter<1);
	lidar.stop();
	printf("done\n");

}
