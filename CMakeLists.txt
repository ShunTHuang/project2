cmake_minimum_required(VERSION 3.10)
project(project2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

build_lib(
        LIBNAME project2
        SOURCE_FILES
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
        HEADER_FILES
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

        LIBRARIES_TO_LINK
        ${libcore}
        ${libnetwork}
        ${libtraffic-control}
        ${libapplications}
        ${libpoint-to-point}
        ${libtraffic-control}
)
target_include_directories(project2 PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/model>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/model/filter_elements>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/model/queue>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/model/utils>
)

build_exec(
        EXECNAME SpqSimulation
        SOURCE_FILES examples/SpqSimulation.cpp
        LIBRARIES_TO_LINK
        project2
        ${libcore}
        ${libnetwork}
        ${libapplications}
        ${libpoint-to-point}
        ${libtraffic-control}
        EXECUTABLE_DIRECTORY_PATH
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/project2/
        ${IGNORE_PCH}
)

build_exec(
        EXECNAME DrrSimulation
        SOURCE_FILES examples/DrrSimulation.cpp
        LIBRARIES_TO_LINK
        project2
        ${libcore}
        ${libnetwork}
        ${libinternet}
        ${libapplications}
        ${libpoint-to-point}
        ${libtraffic-control}
        EXECUTABLE_DIRECTORY_PATH
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/src/project2/
        ${IGNORE_PCH}
)