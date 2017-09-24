CONFIG -= debug_and_release debug_and_release_target

*g++* { kgl_cc = g++ }
*msvc* { kgl_cc = msvc }
*mingw* { kgl_cc = mingw }
*clang++* { kgl_cc = clang }
*icc* { kgl_cc = icc }
*-64* { kgl_arch = x64 } else { kgl_arch = x86 }
*-arm* { kgl_arch = arm } # fallback
*-armeabi* { kgl_arch = armeabi }
*-armeabi-v7a* { kgl_arch = armeabi-v7a }
*-armeabi-v8a* { kgl_arch = armeabi-v8a }
*android* { kgl_arch = $${ANDROID_TARGET_ARCH} }

win32 {
    contains(QT_ARCH, x86_64) {
        kgl_arch = x64
    }
}

contains(QMAKE_PLATFORM, win32) { kgl_os = windows }
contains(QMAKE_PLATFORM, linux) { kgl_os = linux }
contains(QMAKE_PLATFORM, macx) { kgl_os = macosx }
contains(QMAKE_PLATFORM, solaris) { kgl_os = solaris }
contains(QMAKE_PLATFORM, bsd) { kgl_os = freebsd }
contains(QMAKE_PLATFORM, android) { kgl_os = android }
contains(QMAKE_PLATFORM, blackberry) { kgl_os = blackberry }
contains(QMAKE_PLATFORM, winphone) { kgl_os = winphone }
CONFIG(debug, debug|release) { kgl_mode = debug } else { kgl_mode = release }

kgl_path = $${kgl_os}_$${kgl_arch}_$${kgl_cc}/$${kgl_mode}
