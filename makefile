CXX = g++
CXXFLAGS = -std=c++11 -lcurl

SRC_FILES = main.cpp httpDownLoader.cpp

OBJ_FILES = $(SRC_FILES:.cpp=.o)

TARGET = downloadTool

$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ_FILES) $(TARGET)
