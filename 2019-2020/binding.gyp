{
    "targets": [{
        "target_name": "rpserver",
        "cflags!": ["-Wno-psabi", "-Wunused-result", "-fno-exceptions"],
        "cflags_cc!": ["-Wno-psabi", "-Wunused-result", "-fno-exceptions"],
        "sources": [
            "cppFiles/Sources/mainServer.cpp",
            "cppFiles/Sources/ServerFunctions.cpp",
            "cppFiles/Headers/ServerFunctions.h",
            "cppFiles/Headers/config.h"
        ],
        'include_dirs': [
            "<!@(node -p \"require('node-addon-api').include\")"
        ],
        'libraries': [],
        'dependencies': [
            "<!(node -p \"require('node-addon-api').gyp\")"
        ],
        'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS']
    }]
}