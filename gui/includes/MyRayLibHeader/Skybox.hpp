/*
** EPITECH PROJECT, 2022
** gui
** File description:
** Skybox.hpp
*/

#pragma once

#include <iostream>
#include "raylib.h"
#include "rlgl.h"
#include "raymath.h"

#if defined(PLATFORM_DESKTOP)
    #define GLSL_VERSION    330
#else
    #define GLSL_VERSION    100
#endif

namespace MyRayLib {
    class Skybox {
        private:
        public:
            ::Mesh _cube;
            ::Model _skybox;
            ::Shader _shdrCubemap;
            MyRayLib::Texture2D _panorama;
            ::Image _img;
            bool _useHDR;
            Skybox(float width, float height, float length) {
                _cube = GenMeshCube(width, height, length);
                _useHDR = true;
            }
            ~Skybox() {

            };
            void MyLoadFromMesh(Mesh mesh) {
                _skybox = LoadModelFromMesh(mesh);
            }
            ::Model MyGetModel() {
                return _skybox;
            }
            ::Mesh MyGetMesh() {
                return _cube;
            }
            void SetMesh(::Mesh mesh) {
                _cube = mesh;
            }
            Shader MyLoadShader(const char *vsFileName, const char *fsFileName) {
                return LoadShader(TextFormat(vsFileName, GLSL_VERSION), TextFormat(fsFileName, GLSL_VERSION));
            }
            void MySetShaderValue(Shader shader, int locIndex, const void *value, int uniformType) {
                SetShaderValue(shader, locIndex, value, uniformType);
            }
            int MyGetShaderLocation(Shader shader, const char *uniformName) {
                return GetShaderLocation(shader, uniformName);
            }
            int MyTextCopy(char *dst, const char *src) {
                return TextCopy(dst, src);
            }
            ::Texture2D MyLoadTexture(const char *fileName) {
                return LoadTexture(fileName);
            }
            ::Image MyLoadImage(const char *fileName) {
                return LoadImage(fileName);
            }
            void MyrlDisableBackfaceCulling() {
                rlDisableBackfaceCulling();
            }
            void MyrlDisableDepthMask() {
                rlDisableDepthMask();
            }
            void MyUnloadImage(::Image image) {
                UnloadImage(image);
            }
            TextureCubemap MyLoadTextureCubemap(Image image, int layout) {
                return LoadTextureCubemap(image, layout);
            }
            void MyrlEnableBackfaceCulling() {
                rlEnableBackfaceCulling();
            }
            void MyrlEnableDepthMask() {
                rlEnableDepthMask();
            }
            void MyUnloadShader() {
                UnloadShader(this->_skybox.materials[0].shader);
            }
            void MyUnloadTexture() {
                UnloadTexture(this->_skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture);
            }
            void MyUnloadModel() {
                UnloadModel(this->_skybox);
            }
            ::TextureCubemap MyGenTextureCubemap(Shader shader, int size, int format)
            {
                TextureCubemap cubemap = { 0, 0, 0, 0, 0 };
                MyrlDisableBackfaceCulling();
                unsigned int rbo = rlLoadTextureDepth(size, size, true);
                cubemap.id = rlLoadTextureCubemap(0, size, format);
                unsigned int fbo = rlLoadFramebuffer(size, size);
                rlFramebufferAttach(fbo, rbo, RL_ATTACHMENT_DEPTH, RL_ATTACHMENT_RENDERBUFFER, 0);
                rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X, 0);
                if (rlFramebufferComplete(fbo)) TraceLog(LOG_INFO, "FBO: [ID %i] Framebuffer object created successfully", fbo);
                rlEnableShader(shader.id);
                Matrix matFboProjection = MatrixPerspective(90.0*DEG2RAD, 1.0, RL_CULL_DISTANCE_NEAR, RL_CULL_DISTANCE_FAR);
                rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_PROJECTION], matFboProjection);
                Matrix fboViews[6] = {
                    MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
                    MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){ -1.0f,  0.0f,  0.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
                    MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f,  1.0f }),
                    MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f, -1.0f,  0.0f }, (Vector3){ 0.0f,  0.0f, -1.0f }),
                    MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f,  1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f }),
                    MatrixLookAt((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector3){  0.0f,  0.0f, -1.0f }, (Vector3){ 0.0f, -1.0f,  0.0f })
                };
                rlViewport(0, 0, size, size);
                rlActiveTextureSlot(0);
                rlEnableTexture(this->_panorama.getTexture().id);
                for (int i = 0; i < 6; i++) {
                    rlSetUniformMatrix(shader.locs[SHADER_LOC_MATRIX_VIEW], fboViews[i]);
                    rlFramebufferAttach(fbo, cubemap.id, RL_ATTACHMENT_COLOR_CHANNEL0, RL_ATTACHMENT_CUBEMAP_POSITIVE_X + i, 0);
                    rlEnableFramebuffer(fbo);
                    rlClearScreenBuffers();
                    rlLoadDrawCube();
                }
                rlDisableShader();
                rlDisableTexture();
                rlDisableFramebuffer();
                rlUnloadFramebuffer(fbo);
                rlViewport(0, 0, rlGetFramebufferWidth(), rlGetFramebufferHeight());
                rlEnableBackfaceCulling();
                cubemap.width = size;
                cubemap.height = size;
                cubemap.mipmaps = 1;
                cubemap.format = format;
                return cubemap;
            }
            void InitSkybox() {
                MyLoadFromMesh(_cube);
                int a[1] = { MATERIAL_MAP_CUBEMAP };
                int b[1] = { _useHDR ? 1 : 0 };
                int c[1] = { _useHDR ? 1 : 0 };
                int d[1] = { 0 };

                _skybox.materials[0].shader = MyLoadShader("./gui/assets/Skybox/skybox.vs", "./gui/assets/Skybox/skybox.fs");

                MySetShaderValue(_skybox.materials[0].shader, MyGetShaderLocation(_skybox.materials[0].shader, "environmentMap"), a, SHADER_UNIFORM_INT);
                MySetShaderValue(_skybox.materials[0].shader, MyGetShaderLocation(_skybox.materials[0].shader, "doGamma"), b, SHADER_UNIFORM_INT);
                MySetShaderValue(_skybox.materials[0].shader, MyGetShaderLocation(_skybox.materials[0].shader, "vflipped"), c, SHADER_UNIFORM_INT);

                _shdrCubemap = MyLoadShader("./gui/assets/Skybox/cubemap.vs", "./gui/assets/Skybox/cubemap.fs");
                MySetShaderValue(_shdrCubemap, MyGetShaderLocation(_shdrCubemap, "environmentMap"), d, SHADER_UNIFORM_INT);
            }
            void chooseSkyboxFile(const MyRayLib::Texture2D &texture) {
                if (_useHDR) {
                    this->_panorama = texture;
                    this->_skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = MyGenTextureCubemap(_shdrCubemap, 1024, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
                }
            }
    };
}
