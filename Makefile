CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I/usr/local/include
LDFLAGS = -L/usr/local/lib

# Source files
SRCS = src/main.cc src/thread.cc src/simulator.cc src/schedulers/round_robin.cc
OBJS = $(SRCS:.cc=.o)

# Test files
TEST_SRCS = tests/test_driver.cc
TEST_OBJS = $(TEST_SRCS:.cc=.o)

# Round Robin test files
ROUND_ROBIN_TEST_SRCS = tests/round_robin_test.cc tests/test_driver.cc src/thread.cc src/simulator.cc src/schedulers/round_robin.cc
ROUND_ROBIN_TEST_OBJS = $(ROUND_ROBIN_TEST_SRCS:.cc=.o)

# Targets
all: scheduler_benchmarker test_driver round_robin_test

scheduler_benchmarker: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) -lnlohmann_json

test_driver: $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@ $(LDFLAGS) -lnlohmann_json

round_robin_test: $(ROUND_ROBIN_TEST_OBJS)
	$(CXX) $(ROUND_ROBIN_TEST_OBJS) -o $@ $(LDFLAGS) -lnlohmann_json

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(ROUND_ROBIN_TEST_OBJS) scheduler_benchmarker test_driver round_robin_test

.PHONY: all clean round_robin_test 