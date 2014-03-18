set(CMAKE_LEGACY_CYGWIN_WIN32 0)

PROJECT(Boost CXX)

#set(Boost_USE_STATIC_LIBS OFF) 
#set(Boost_USE_MULTITHREADED ON)  
#set(Boost_USE_STATIC_RUNTIME OFF) 

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")
endif()

ADD_EXECUTABLE(boost_any boost_any.cpp)
##ADD_EXECUTABLE(boost_options boost_options.cpp)
ADD_EXECUTABLE(boost_variant boost_variant.cpp)

