#
#  Created by Bradley Austin Davis on 2015/11/18
#  Copyright 2015 High Fidelity, Inc.
#  Copyright 2020 Vircadia contributors.
#  Copyright 2023-2025 Overte e.V.
#
#  Distributed under the Apache License, Version 2.0.
#  See the accompanying file LICENSE or http:#www.apache.org/licenses/LICENSE-2.0.html
#  SPDX-License-Identifier: Apache-2.0
#

if ((WIN32 OR UNIX AND NOT APPLE) AND (NOT OVERTE_RENDERING_BACKEND STREQUAL "GLES"))
    set(TARGET_NAME openvr)
    setup_hifi_plugin(Gui Qml Multimedia)
    link_hifi_libraries(shared task gl qml networking controllers ui
        plugins display-plugins ui-plugins input-plugins
        audio-client render-utils graphics shaders gpu render material-networking model-networking model-baker hfm model-serializers ktx image procedural ${PLATFORM_GL_BACKEND})
    include_hifi_library_headers(octree)
    include_hifi_library_headers(script-engine)

    target_openvr()
    if (WIN32)
        target_link_libraries(${TARGET_NAME} Winmm.lib)
    endif()
endif()
