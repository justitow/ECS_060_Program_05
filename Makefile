train.out : train.o TrainRunner.o StationNode.o
	g++ -ansi -Wall -g -o train.out train.o TrainRunner.o StationNode.o

train.o : train.cpp TrainRunner.h train.h StationNode.h
	g++ -ansi -Wall -g -c train.cpp

TrainRunner.o : TrainRunner.cpp CPUTimer.h train.h TrainRunner.h 
	g++ -ansi -Wall -g -c TrainRunner.cpp

StationNode.o : StationNode.cpp StationNode.h TrainRunner.h
	g++ -ansi -Wall -g -c StationNode.cpp

clean : 
	rm -f train.out train.o  TrainRunner.o   
