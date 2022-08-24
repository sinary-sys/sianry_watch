idf_component_register(
        SRC_DIRS
        .
        SRCS
        .
        "http_web.c"
        INCLUDE_DIRS
        "."
        REQUIRES esp_http_server main my_system)
        