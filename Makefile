train.out : train.o TrainRunner.o StationMap.o
	g++ -ansi -Wall -g -o train.out train.o TrainRunner.o StationMap.o

train.o : train.cpp TrainRunner.h train.h StationMap.h
	g++ -ansi -Wall -g -c train.cpp

TrainRunner.o : TrainRunner.cpp CPUTimer.h train.h TrainRunner.h 
	g++ -ansi -Wall -g -c TrainRunner.cpp

StationMap.o : StationMap.cpp StationMap.h TrainRunner.h
	g++ -ansi -Wall -g -c StationMap.cpp

clean : 
	rm -f train.out train.o  TrainRunner.o   
