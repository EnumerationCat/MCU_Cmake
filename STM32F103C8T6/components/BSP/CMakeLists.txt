target_compile_definitions(${PROJECT_NAME} PRIVATE
    
)

target_include_directories(${PROJECT_NAME} PRIVATE



	"${CMAKE_CURRENT_LIST_DIR}/oled"
	"${CMAKE_CURRENT_LIST_DIR}/led"
	"${CMAKE_CURRENT_LIST_DIR}/key"
	"${CMAKE_CURRENT_LIST_DIR}/mycan"

	



    
)


target_sources(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/oled/oled.c"
	"${CMAKE_CURRENT_LIST_DIR}/led/led.c"
	"${CMAKE_CURRENT_LIST_DIR}/key/key.c"
	"${CMAKE_CURRENT_LIST_DIR}/mycan/mycan.c"
	
	

 
)