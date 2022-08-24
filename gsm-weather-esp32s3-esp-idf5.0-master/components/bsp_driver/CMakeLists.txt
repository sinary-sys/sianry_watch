idf_component_register(
                    SRCS
                    "."
                    "bsp_i2c.c"
                    "bsp_sd.c"
                    "bsp_ledc.c"
                    "bsp_key.c"
                    "bsp_power.c"
                    SRC_DIRS
                    "."

                    INCLUDE_DIRS
                    "."
                    REQUIRES driver main fatfs
                    )

