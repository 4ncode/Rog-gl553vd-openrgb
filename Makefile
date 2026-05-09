CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2 `pkg-config --cflags hidapi-libusb`
LDFLAGS = `pkg-config --libs hidapi-libusb`

SRCDIR = src
TARGET = test_gl553vd

SOURCES = $(SRCDIR)/standalone_test.cpp $(SRCDIR)/ASUSROGGL553VDController.cpp
HEADERS = $(SRCDIR)/ASUSROGGL553VDController.h

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(TARGET)

test: $(TARGET)
	sudo ./$(TARGET)