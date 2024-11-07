install(
    TARGETS cloxc_exe
    RUNTIME COMPONENT cloxc_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
