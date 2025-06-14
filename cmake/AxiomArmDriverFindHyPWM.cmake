include(FetchContent)
set(BUILD_HYPWM_EXAMPLE OFF)
find_package(HyPWM QUIET)

if (NOT HyPWM_FOUND)
    message(STATUS "Can't find HyPWM locally，try fetching from GitHub...")
    FetchContent_Declare(
            HyPWM_fetched
            GIT_REPOSITORY "https://github.com/RoboMaster-DLMU-CONE/HyPWM"
            GIT_TAG "main"
    )
    FetchContent_MakeAvailable(HyPWM_fetched)
else ()
    message(STATUS "Found HyPWM v${HyPWM_VERSION}")
endif ()