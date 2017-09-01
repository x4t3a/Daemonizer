export CXXFLAGS := --std=c++1z
export CXX := clang++-5.0

daemonizer_test: daemonizer_test.cpp daemonizer.cpp daemonizer.hpp
	${CXX} ${CXXFLAGS} daemonizer_test.cpp daemonizer.cpp -o $@
