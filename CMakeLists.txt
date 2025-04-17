cmake_minimum_required(VERSION 3.10)
project(project2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(NS3_ROOT "$ENV{HOME}/ns-3-dev")
set(NS3_DIR "$ENV{HOME}/ns-3-dev/build")
set(NS3_INCLUDE "${NS3_DIR}/include")
set(NS3_SRC "${NS3_DIR}/src")
set(NS3_LIBDIR  "${NS3_DIR}/lib")

include_directories(
        ${NS3_INCLUDE}
        ${NS3_ROOT}/src/core/model
        ${NS3_ROOT}/src/network/model
        ${NS3_ROOT}/src/internet/model
        ${NS3_ROOT}/src/network/utils
)
link_directories(${NS3_LIBDIR})

set(SOURCES
        model/DiffServ.cpp
        model/TrafficClass.cpp
        model/Filter.cpp
        model/FilterElement.cpp
        model/filter_elements/src_ip.cpp
        model/filter_elements/src_mask.cpp
        model/filter_elements/src_port.cpp
        model/filter_elements/dst_ip.cpp
        model/filter_elements/dst_mask.cpp
        model/filter_elements/dst_port.cpp
        model/filter_elements/protocol.cpp
        model/queue/StrictPriorityQueue.cpp
)
set(HEADERS
        model/DiffServ.h
        model/TrafficClass.h
        model/Filter.h
        model/FilterElement.h
        model/filter_elements/src_ip.h
        model/filter_elements/src_mask.h
        model/filter_elements/src_port.h
        model/filter_elements/dst_ip.h
        model/filter_elements/dst_mask.h
        model/filter_elements/dst_port.h
        model/filter_elements/protocol.h
        model/queue/StrictPriorityQueue.h
)

add_library(project2 STATIC ${SOURCES} ${HEADERS})
target_include_directories(project2 PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/model
        ${CMAKE_CURRENT_SOURCE_DIR}/model/filter_elements
)

target_link_libraries(project2 PUBLIC
        ns3.core
        ns3.network
        ns3.traffic-control
)

add_executable(demo-diffsver examples/demo-diffsver.cc)
target_link_libraries(demo-diffsver PRIVATE
        project2
        ns3.core
        ns3.network
        ns3.traffic-control
)
