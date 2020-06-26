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
MAINOBJECTS = my_main.o
LIBOBJECTS = $(SRCDIR)/lcd/lcd_2004a_i2c.o $(SRCDIR)/temp_sensor/ds18b20_temp_sensor.o
MAINOBJECTS = $(SRCDIR)/main/my_main.o

all: lcd.o ds18b20_temp_sensor.o main.o home_auto_temp

lcd.o: $(LCD_SOURCES)/lcd_2004a_i2c.cpp
	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

ds18b20_temp_sensor.o: $(TEMP_SENSOR_SOURCES)/ds18b20_temp_sensor.cpp
	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

main.o: $(MAIN_SOURCES)/main.cpp
	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

home_auto_temp: $(ODIR)/main.o
	$(CXX) $(CXXFLAGS) -o $(BINDIR)/$@ $^

#$(LCD_SOURCES)/lcd_2004a_i2c.o: lcd_2004a_i2c.cpp
#	$(CXX) $(CXXFLAGS) -o $(ODIR)/$@ $^

#$(TEMP_SENSOR_SOURCES)/ds18b20_temp_sensor.o: ds18b20_temp_sensor.cpp
#	$(CXX) $(CXXFLAGS) -o $(ODIR)/$@ $^

#$(MAIN_SOURCES)/my_main.o: my_main.cpp
#	$(CXX) $(CXXFLAGS) -c -o $(ODIR)/$@ $^

#_DEPS = ds18b20_temp_sensor.h lcd_2004a_i2c.h
#DEPS = $(patsubst %,%(IDIR)/%,$(_DEPS))

#_OBJ = lcd_2004a_i2c.o ds18b20_temp_sensor.o my_main.o
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#$(ODIR)/%.o: %.c $(DEPS)
#	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
