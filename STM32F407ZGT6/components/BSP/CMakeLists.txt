target_compile_definitions(${PROJECT_NAME} PRIVATE
    
)

target_include_directories(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/key"
	"${CMAKE_CURRENT_LIST_DIR}/timer"
	"${CMAKE_CURRENT_LIST_DIR}/usart"

	



    
)


target_sources(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/key/key.c"
	"${CMAKE_CURRENT_LIST_DIR}/timer/timer.c"
	"${CMAKE_CURRENT_LIST_DIR}/usart/uart_device.c"

	
	

 
)