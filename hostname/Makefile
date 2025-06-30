CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17

SRC := hostname.cpp ../lib/stoneParser.cpp
OUT := hostname

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	rm -f $(OUT)

.PHONY: all clean
