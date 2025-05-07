cmake_minimum_required(VERSION 3.10)
project(project2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

build_lib(
        LIBNAME project2
        SOURCE_FILES
        model/diff-serv.cpp
        model/traffic-class.cpp
        model/filter.cpp
        model/filter-element.cpp
        model/filter_elements/source-ip-address.cpp
        model/filter_elements/source-mask.cpp
        model/filter_elements/source-port-number.cpp
        model/filter_elements/destination-ip-address.cpp
        model/filter_elements/destination-mask.cpp
        model/filter_elements/destination-port-number.cpp
        model/filter_elements/protocol-number.cpp
        model/queue/strict-priority-queue.cpp
        model/queue/deficit-round-robin.cpp
        model/utils/qos-creator.cpp
        model/utils/cli-parser.cpp
        HEADER_FILES
        model/diff-serv.h
        model/traffic-class.h
        model/filter.h
        model/filter-element.h
        model/filter_elements/source-ip-address.h
        model/filter_elements/source-mask.h
        model/filter_elements/source-port-number.h
        model/filter_elements/destination-ip-address.h
        model/filter_elements/destination-mask.h
        model/filter_elements/destination-port-number.h
        model/filter_elements/protocol-number.h
        model/queue/strict-priority-queue.h
        model/queue/deficit-round-robin.h
        model/utils/qos-creator.h
        model/utils/cli-parser.h
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