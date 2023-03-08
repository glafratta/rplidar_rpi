#include "a1lidarrpi.h"
#include <fstream>

class DataInterface : public A1Lidar::DataInterface {
public:
	FILE * f;
//	std::ofstream o;
	int counter=0;
    char fileName[256];

	void __init__(){
		// //TODAYS DATE AND TIME
		time_t now =time(0);
		tm *ltm = localtime(&now);
		int y,m,d;
		y=ltm->tm_year-100;
		m = ltm->tm_mon +1;
		d=ltm->tm_mday;
		sprintf(fileName, "/tmp/scan%02i%02i%02i_%02i%02i.txt", d,m,y, ltm->tm_hour, ltm->tm_min);
	//	o = std::ofstream(fileName);
		f=fopen(fileName, "w+");
		fclose(f);

	}
	
	void newScanAvail(float,A1LidarData (&data)[A1Lidar::nDistance]) {
		counter++;
		f=fopen(fileName, "a+");
		printf("writing to %s\n", fileName);
		for(A1LidarData &data: data) {
			if (data.valid){
			fprintf(f,"%.3f\t%.3f\n",data.x,data.y);
		//		o<<data.x<<"\t"<<data.y<<"\n"<<std::flush;
		}
			//else{
			//printf("invalid data");
			//}
		}

		fclose(f);
	}
};

int main(int, char **) {
	fprintf(stderr,"prints x, y coordinates approximated to the third decimal\n");
	A1Lidar lidar;
	DataInterface dataInterface;
	dataInterface.__init__();
	lidar.registerInterface(&dataInterface);
	lidar.start();
	do {
}while (std::ifstream(dataInterface.fileName).peek()==std::ifstream::traits_type::eof());
	//dataInterface.o<<std::flush;
	//dataInterface.o.close();
	lidar.stop();
	printf("done\n");

}
