CXXFLAGS=-s -Os -pipe -Wall -std=c++11
CPPFLAGS=-std=c++11
LDLIBS=-lsfml-system -lsfml-graphics -lsfml-window
SRCS=xsf/Box.cpp unknown.cpp tagged.cpp timer.cpp movement.cpp sensor.cpp animation.cpp sequence.cpp collide.cpp world.cpp main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: sfmlpkmn

sfmlpkmn: $(OBJS)
	$(CXX) $(LDFLAGS) -o sfmlpkmn $(OBJS) $(LDLIBS) 

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) *~ .dependtool

include .depend

