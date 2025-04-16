def build(bld):
    module = bld.create_ns3_module('project2', ['core', 'network', 'traffic-control'])

    module.source = [
        'model/DiffServ.cpp',
        'model/TrafficClass.cpp',
        'model/Filter.cpp',
        'model/FilterElement.cpp',
        'model/filter_elements/src_ip.cpp',
        'model/filter_elements/src_mask.cpp',
        'model/filter_elements/src_port.cpp',
        'model/filter_elements/dst_ip.cpp',
        'model/filter_elements/dst_mask.cpp',
        'model/filter_elements/dst_port.cpp',
        'model/filter_elements/protocol.cpp',
    ]

    headers = bld(features='ns3header')
    headers.module = 'project2'
    headers.source = [
        'model/DiffServ.h',
        'model/TrafficClass.h',
        'model/Filter.h',
        'model/FilterElement.h',
        'model/filter_elements/src_ip.h',
        'model/filter_elements/src_mask.h',
        'model/filter_elements/src_port.h',
        'model/filter_elements/dst_ip.h',
        'model/filter_elements/dst_mask.h',
        'model/filter_elements/dst_port.h',
        'model/filter_elements/protocol.h',
    ]

    bld.ns3_python_bindings()