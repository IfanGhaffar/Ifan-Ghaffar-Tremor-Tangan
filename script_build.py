import os
from SCons.Script import Import # type: ignore

Import("env")
env.Replace( # type: ignore
    UPLOADFSFLAGS=[
        "--chip",
        "esp32s3",
        "--before",
        "default_reset",
        "--after",
        "hard_reset",
        "write_flash",
        "0x110000",
        "buildfs",
    ]
)
