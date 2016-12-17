/*
 * Copyright 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef GLES3JNI_H
#define GLES3JNI_H 1

#include <android/log.h>
#include <math.h>
#include <string>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#if DYNAMIC_ES3
#include "gl3stub.h"
#else
#include <GLES3/gl3.h>
#endif

#define DEBUG 1

#define LOG_TAG "GLES3JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif
// returns true if a GL error occurred
extern bool checkGlError(const char* funcName);
extern GLuint createProgram(const char* vtxSrc, const char* fragSrc);

// ----------------------------------------------------------------------------
// Interface to the ES2 and ES3 renderers, used by JNI code.

class Renderer {
public:
    virtual ~Renderer();
    void resize(int w, int h);
    void render();
    std::string shaderpath;
    AAssetManager* apkAssetManager;

protected:
    Renderer();

    // return a pointer to a buffer of MAX_INSTANCES * sizeof(vec2).
    // the buffer is filled with per-instance offsets, then unmapped.
    //virtual float* mapOffsetBuf() = 0;
    //virtual void unmapOffsetBuf() = 0;
    // return a pointer to a buffer of MAX_INSTANCES * sizeof(vec4).
    // the buffer is filled with per-instance scale and rotation transforms.

    virtual void draw() = 0;

};

extern Renderer* createES2Renderer();
extern Renderer* createES3Renderer();

#endif // GLES3JNI_H
