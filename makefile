all: ntuple datagenerator subset
PHONY: all

ntuple:
	g++ -std=c++11 -o ntuple ntuple.cpp -O2

datagenerator:
	g++ -std=c++11 -o datagenerator datagenerator.cpp 

subset:
	g++ -std=c++11 -o subset subset.cpp

clean:
	$(RM) datagenerator, $(RM) ntuple, $(RM) subset
