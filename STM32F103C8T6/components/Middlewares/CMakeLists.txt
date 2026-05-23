target_compile_definitions(${PROJECT_NAME} PRIVATE
    
)
target_include_directories(${PROJECT_NAME} PRIVATE

	"${CMAKE_CURRENT_LIST_DIR}/FreeRTOS"
	"${CMAKE_CURRENT_LIST_DIR}/LVGL"
	"${CMAKE_CURRENT_LIST_DIR}/USB"

    
)
target_sources(${PROJECT_NAME} PRIVATE


)