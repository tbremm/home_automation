IDIR = headers
SRCDIR = src
ODIR=obj
BINDIR = bin

LCD_SOURCES = $(SRCDIR)/lcd
TEMP_SENSOR_SOURCES = $(SRCDIR)/temp_sensor
MAIN_SOURCES = $(SRCDIR)/main
ALL_SOURCES = $(LCD_SOURCES)/*.cpp $(TEMP_SENSOR_SOURCES)/*.cpp $(MAIN_SOURCES)/*.cpp

CXX = g++
CXXFLAGS = -Wall -I$(IDIR) -lwiringPi

LCDOBJECTS = lcd_2004a_i2c.o
TEMPOBJECTS = ds18b20_temp_sensor.o
MAINOBJECTS = main.o
LIBOBJECTS = $(ODIR)/lcd_2004a_i2c.o $(ODIR)/ds18b20_temp_sensor.o
MAINOBJECTS = $(ODIR)/my_main.o

all: lcd.o ds18b20_temp_sensor.o main.o home_auto_temp

lcd.o: $(LCD_SOURCES)/lcd_2004a_i2c.cpp
	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

ds18b20_temp_sensor.o: $(TEMP_SENSOR_SOURCES)/ds18b20_temp_sensor.cpp
	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

main.o: $(MAIN_SOURCES)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

home_auto_temp: $(ODIR)/main.o $(ODIR)/lcd.o $(ODIR)/ds18b20_temp_sensor.o
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $^

.PHONY: clean

clean:
	rm -f $(ODIR)/* && rm -f $(BINDIR)/*
