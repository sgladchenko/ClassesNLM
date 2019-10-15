compiler = mpic++

# All of them
all:
	make run; make clean

# Main calculational unit in this project

run: Main.o InitialSpectra.o Segmentation.o AdiabaticScheme.o BaseBin.o
	$(compiler) Main.o InitialSpectra.o Segmentation.o AdiabaticScheme.o BaseBin.o -o run 

Main.o: ./source/Main.cpp 
	$(compiler) -c ./source/Main.cpp -lm

AdiabaticScheme.o: ./source/AdiabaticScheme.cpp
	$(compiler) -c ./source/AdiabaticScheme.cpp -lm

InitialSpectra.o: ./source/InitialSpectra.cpp
	$(compiler) -c ./source/InitialSpectra.cpp -lm

Segmentation.o: ./source/Segmentation.cpp
	$(compiler) -c ./source/Segmentation.cpp -lm

BaseBin.o: ./source/BaseBin.cpp
	$(compiler) -c ./source/BaseBin.cpp -lm

clean:
	rm -rf *.o