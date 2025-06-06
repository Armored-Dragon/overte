#
#  Created by Bradley Austin Davis on 2018/10/24
#  Copyright 2013-2018 High Fidelity, Inc.
#
#  Distributed under the Apache License, Version 2.0.
#  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
#
macro(TARGET_OPENXR)
    find_package(OpenXR REQUIRED)
    target_link_libraries(${TARGET_NAME} OpenXR::openxr_loader)
endmacro()
