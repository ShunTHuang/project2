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
        model/queue/DeficitRoundRobin.cpp
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
        model/queue/DeficitRoundRobin.h
        model/utils/QoSCreator.h
        model/utils/QoSCreator.cpp
)

add_library(project2 STATIC ${SOURCES} ${HEADERS})
target_include_directories(project2 PUBLIC
        model
        model/filter_elements
        model/queue
        model/utils
)

target_link_libraries(project2 PUBLIC
        ns3.core
        ns3.network
        ns3.traffic-control
)

add_executable(SpqSimulation
        examples/SpqSimulation.cpp)

target_link_libraries(SpqSimulation PRIVATE
        project2
        ns3.core
        ns3.network
        ns3.traffic-control
)

# DrrSimulation
add_executable(DrrSimulation
        examples/DrrSimulation.cpp)

target_link_libraries(DrrSimulation PRIVATE
        project2
        ns3.traffic-control
        ns3.core
        ns3.network
        ns3.internet
        ns3.applications
        ns3.point-to-point
)

#target_link_libraries(demo-diffsver PRIVATE
#        project2
#        ns3.core
#        ns3.network
#        ns3.traffic-control
#)

