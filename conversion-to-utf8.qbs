import qbs

CppApplication {
    consoleApplication: true
    cpp.debugInformation: true
    cpp.cxxLanguageVersion: "c++17"
    cpp.includePaths: [
        "inc",
    ]
    Group
    {
        name: "headers"
        prefix: "inc/kmx/to_utf8/"
        files: [
            "from_utf16.hpp",
            "from_utf32.hpp",
        ]
        qbs.installDir:  "include/to_utf8"
        qbs.install:  true
    }
    Group {
        name: "test"
        files: [
            "test/utf16.cpp",
            "test/utf32.cpp",
        ]
        qbs.install: false
    }
}
