compiler = mpic++

# All of them
all:
	make run; make generate; make parser; make clean

# Main calculational unit in this project

run: Main.o InitialSpectra.o Inhomogeneities.o Segmentation.o StandardScheme.o BaseBin.o Matrix.o StandardRK.o
	$(compiler) Main.o InitialSpectra.o Segmentation.o StandardScheme.o BaseBin.o Matrix.o StandardRK.o Inhomogeneities.o -o run 

Main.o: ./source/Main.cpp ./source/Constants.h
	$(compiler) -c ./source/Main.cpp -lm

StandardScheme.o: ./source/StandardScheme.cpp ./source/StandardScheme.h ./source/BaseScheme.h ./source/Constants.h ./source/Log.h
	$(compiler) -c ./source/StandardScheme.cpp -lm

InitialSpectra.o: ./source/InitialSpectra.cpp ./source/InitialSpectra.h ./source/PhysicalConstants.h
	$(compiler) -c ./source/InitialSpectra.cpp -lm

Segmentation.o: ./source/Segmentation.cpp ./source/Segmentation.h ./source/Constants.h
	$(compiler) -c ./source/Segmentation.cpp -lm

BaseBin.o: ./source/BaseBin.cpp ./source/BaseBin.h ./source/Constants.h
	$(compiler) -c ./source/BaseBin.cpp -lm

Matrix.o: ./source/Matrix.cpp ./source/Matrix.h ./source/Constants.h
	$(compiler) -c ./source/Matrix.cpp -lm

StandardRK.o: ./source/StandardRK.cpp ./source/StandardRK.h ./source/Constants.h
	$(compiler) -c ./source/StandardRK.cpp -lm

Inhomogeneities.o: ./source/Inhomogeneities.cpp ./source/Inhomogeneities.h ./source/Constants.h
	$(compiler) -c ./source/Inhomogeneities.cpp -lm


# Executable which generates for us initial data, saved in rec.bin

generate: InitialSpectra.o Generate.o Inhomogeneities.o ./source/Constants.h ./source/BaseBin.h
	$(compiler) InitialSpectra.o Generate.o Inhomogeneities.o  -o generate

Generate.o: ./source/Generate.cpp
	$(compiler) -c ./source/Generate.cpp -lm


# Additional executable which is used for processing data of full bin-files

parser: InitialSpectra.o Parser.o
	$(compiler) InitialSpectra.o Parser.o -o parser

Parser.o: ./source/Parser.cpp
	$(compiler) -c ./source/Parser.cpp -lm


# Clean all the object files

clean:
	rm -rf *.o