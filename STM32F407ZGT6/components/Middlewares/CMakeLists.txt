target_compile_definitions(${PROJECT_NAME} PRIVATE
    
)
target_include_directories(${PROJECT_NAME} PRIVATE

	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/include"
    "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/portable/GCC/ARM_CM4F"
    "${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/config"
	"${CMAKE_CURRENT_LIST_DIR}/LVGL"
	"${CMAKE_CURRENT_LIST_DIR}/USB"
	"${CMAKE_CURRENT_LIST_DIR}/AT_Socket"

    
)
target_sources(${PROJECT_NAME} PRIVATE
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/croutine.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/event_groups.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/list.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/queue.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/stream_buffer.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/tasks.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/source/timers.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/portable/GCC/ARM_CM4F/port.c"
	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS/portable/MemMang/heap_4.c"


	"${CMAKE_CURRENT_LIST_DIR}/AT_Socket/at_command.c"
	"${CMAKE_CURRENT_LIST_DIR}/AT_Socket/at_socket.c"
	"${CMAKE_CURRENT_LIST_DIR}/AT_Socket/esp8266.c"
	"${CMAKE_CURRENT_LIST_DIR}/AT_Socket/TCP_Client_Test.c"





)