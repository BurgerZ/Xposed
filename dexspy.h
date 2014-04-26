#ifndef DEXSPY_H_
#define DEXSPY_H_

#define ANDROID_SMP 0
#include "Dalvik.h"
#include <list>
#include <android_runtime/AndroidRuntime.h>

namespace android {

#define DEXSPY_DIR "/data/miui/"
#define DEXSPY_JAR DEXSPY_DIR "DexspyInstaller.jar"
#define DEXSPY_JAR_NEWVERSION DEXSPY_DIR "DexspyInstaller.jar.newversion"
#define DEXSPY_LOAD_BLOCKER DEXSPY_DIR "disabled"
#define DEXSPY_CLASS "miui/dexspy/DexspyInstaller"
#define DEXSPY_CLASS_DOTS "miui.dexspy.DexspyInstaller"
#define DEXSPY_VERSION "1.0"

#ifndef ALOGD
#define ALOGD LOGD
#define ALOGE LOGE
#define ALOGI LOGI
#define ALOGV LOGV
#endif

extern bool keepLoadingDexspy;
typedef std::list<Method>::iterator OriginalMethodsIt;

// called directoy by app_process
void dexspyInfo();
bool isDexspyDisabled();
bool dexspyShouldIgnoreCommand(const char* className, int argc,
		const char* const argv[]);
bool addDexspyToClasspath(bool zygote);
bool dexspyOnVmCreated(JNIEnv* env, const char* className);
void dexspyStartMain(JNIEnv* env);

// handling hooked methods / helpers
static void dexspyCallHandler(const u4* args, JValue* pResult,
		const Method* method, ::Thread* self);
static OriginalMethodsIt findOriginalMethod(const Method* method);
static jobject dexspyAddLocalReference(::Thread* self, Object* obj);
static void replaceAsm(void* function, char* newCode, int len);

// JNI methods
static jboolean miui_dexspy_DexspyInstaller_initNative(JNIEnv* env,
		jclass clazz);
static void miui_dexspy_DexspyInstaller_hookMethodNative(JNIEnv* env,
		jclass clazz, jobject declaredClassIndirect, jint slot);
static jobject miui_dexspy_DexspyInstaller_invokeOriginalMethodNative(
		JNIEnv* env, jclass clazz, jobject reflectedMethod,
		jobjectArray params1, jclass returnType1, jobject thisObject1,
		jobjectArray args1);
static int register_miui_dexspy_DexspyInstaller(JNIEnv* env);
}

#endif
