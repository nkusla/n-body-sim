#!/bin/bash

# This script is used for downloading and extracing ImGui library
# It is intended to be used by Docker when building an image

# Copying ImGui library files from source repository
IMGUI_SRC_DIR="imgui-1.90.1"

wget -c https://github.com/ocornut/imgui/archive/refs/tags/v1.90.1.tar.gz -O - | tar -xz

mkdir imgui

cd $IMGUI_SRC_DIR/backends/
cp imgui_impl_opengl3.cpp \
	imgui_impl_opengl3.h \
	imgui_impl_opengl3_loader.h \
	imgui_impl_glfw.cpp \
	imgui_impl_glfw.h \
	../../imgui

cd ..

cp imconfig.h \
	imgui.cpp \
	imgui_demo.cpp \
	imgui_draw.cpp \
	imgui.h \
	imgui_internal.h \
	imgui_tables.cpp \
	imgui_widgets.cpp \
	imstb_rectpack.h \
	imstb_textedit.h \
	imstb_truetype.h \
	../imgui

cd ..

rm -rf $IMGUI_SRC_DIR

# Creating other directories
mkdir -p build results