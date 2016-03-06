cmake_minimum_required(VERSION 2.8)

project(final)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


find_package( Threads )


set(Boost_INCLUDE_DIR /usr/include)
set(Boost_LIBRARY_DIR /usr/lib)

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

set(Boost_LIBRARIES ${Boost_LIBRARIES} boost_system)

set(SOURCE_EXE connection.cpp connection.hpp connection_manager.cpp connection_manager.hpp header.hpp main.cpp mime_types.cpp mime_types.hpp reply.cpp reply.hpp request_handler.cpp request_handler.hpp request.hpp request_parser.cpp request_parser.hpp server.cpp server.hpp)

add_executable(final ${SOURCE_EXE})
target_link_libraries(final ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries(final ${Boost_LIBRARIES})
