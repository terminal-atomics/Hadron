cmake_minimum_required(VERSION 3.9)
project(hadron)

enable_language(ASM_NASM)

include_directories("src")
include_directories("src/common")
include_directories("src/common/std")

set(CMAKE_C_COMPILER "x86_64-elf-gcc")
set(CMAKE_LINKER "x86_64-elf-ld")
set(CMAKE_C_LINK_EXECUTABLE  "<CMAKE_LINKER> <CMAKE_CXX_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -o <TARGET> <LINK_LIBRARIES>")

set(CMAKE_C_FLAGS "-mno-sse -nostdlib -ffreestanding -fno-exceptions -Wall -Wextra -g -fno-omit-frame-pointer -mno-red-zone")
set(CMAKE_ASM_NASM_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS "-T ../src/arch/amd64/linker.ld -z max-page-size=4096")

set(CMAKE_ASM_NASM_OBJECT_FORMAT elf64)

file(GLOB _STD "src/common/std/*.c" "src/common/std/*.asm")
file(GLOB _MEMORY "src/common/memory/*.c" "src/common/memory/*.asm")

file(GLOB _INIT "src/arch/amd64/init/*.c" "src/arch/amd64/init/*.asm")
file(GLOB _GDT "src/arch/amd64/gdt/*.c" "src/arch/amd64/gdt/*.asm")
file(GLOB _INTERRUPTS "src/arch/amd64/interrupts/*.c" "src/arch/amd64/interrupts/*.asm")
file(GLOB _IO "src/arch/amd64/io/*.c" "src/arch/amd64/io/*.asm")
file(GLOB _PIC "src/arch/amd64/pic/*.c" "src/arch/amd64/pic/*.asm")
file(GLOB _VGA "src/arch/amd64/vga_basic/*.c" "src/arch/amd64/vga_basic/*.asm")
file(GLOB _PAGING "src/arch/amd64/paging/*.c" "src/arch/amd64/paging/*.asm")

add_custom_target(iso COMMAND sh ../tools/amd64/make_iso.sh)
add_dependencies(iso hadron)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../bin/amd64/")

add_executable(hadron ${_STD} ${_INIT} ${_GDT} ${_INTERRUPTS} ${_IO} ${_PIC} ${_VGA} ${_PAGING} ${_MEMORY})