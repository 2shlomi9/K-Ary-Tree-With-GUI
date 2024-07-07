CXX = g++

# Define C++ standard (adjust according to your project's requirements)
CXXFLAGS = -std=c++2a -Werror -Wsign-conversion

# Define output filename
OUTPUT = a.out

# Define object files
OBJECTS = Complex.o

# Rule to build the final executable
$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(OUTPUT) 

tree: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) Demo.o $(OBJECTS) -o tree 

test: Test.o TestCounter.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) Test.o TestCounter.o $(OBJECTS) -o test 

tidy:
	$(TIDY) $(HEADERS) $(TIDY_FLAGS) --

valgrind: test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Rules to compile individual source files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Define header files for your project
HEADERS = Node.hpp Tree.hpp

# Phony target for cleaning up generated files
clean:
	rm -f *.o $(OUTPUT) tree test
