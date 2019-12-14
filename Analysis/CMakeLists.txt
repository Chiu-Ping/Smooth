project (Analysis)
add_executable(Analysis Analysis.cpp Plot_Eff.cpp)
#add_executable(Analysis Analysis.cpp 63)
#add_executable(Plot_Eff Plot_Eff.cpp)
add_dependencies(Analysis Channel Event)
link_libraries(Analysis Event Channel Event ${ROOT_LIBRARIES} Event Channel Event)

target_link_libraries(Analysis Event Channel Event ${ROOT_LIBRARIES} Event Channel Event)

#install(TARGETS Analysis RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})
#install(TARGETS Plot_Eff RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}



