PROJECT(cifras CXX)
SET(PROJECT_DATA_DIR share/cifras CACHE PATH "Project data directory")
SET(PROJECT_BIN_DIR bin CACHE PATH "Project binary directory")

CONFIGURE_FILE(cifras-gui.in cifras-gui @ONLY)
CONFIGURE_FILE(cifras.kmdr.in cifras.kmdr @ONLY)
ADD_EXECUTABLE(cifras cifras.cc memory_manager.cc node.cc operation.cc)

INSTALL(TARGETS cifras RUNTIME DESTINATION ${PROJECT_BIN_DIR})
INSTALL(PROGRAMS ${cifras_BINARY_DIR}/cifras-gui DESTINATION ${PROJECT_BIN_DIR})
INSTALL(FILES ${cifras_BINARY_DIR}/cifras.kmdr DESTINATION ${PROJECT_DATA_DIR})
