#include "AppDelegate.cpp"
#include "Options.cpp"
#include "Texture.cpp"
#include "EntityManager.cpp"
#include "Entity.cpp"
#include "Screen.cpp"
#include "Level.cpp"
#include "Preloader.cpp"
#include "ScreenManager.cpp"
#include "GameOver.cpp"
#include "GameWon.cpp"
#include "Hero.cpp"
#include "Utils.cpp"
#include "Gas.cpp"
#include "Platform.cpp"
#include "BaseBullet.cpp"
#include "Castle.cpp"
#include "Pickup.cpp"
#include "BarEntity.cpp"
#include "BaseEnemy.cpp"
#include "Cloud.cpp"
#include "Small.cpp"
#include "Options.cpp"
#include "BaseExplosion.cpp"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

extern "C"
{

jint JNI_OnLoad(JavaVM *vm, void *reserved)
{
    JniHelper::setJavaVM(vm);

    return JNI_VERSION_1_4;
}

void Java_org_cocos2dx_lib_Cocos2dxRenderer_nativeInit(JNIEnv*  env, jobject thiz, jint w, jint h)
{
    if (!CCDirector::sharedDirector()->getOpenGLView())
    {
        CCEGLView *view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        AppDelegate *pAppDelegate = new AppDelegate();
        CCApplication::sharedApplication()->run();
    }
    else
    {
        ccDrawInit();
        ccGLInvalidateStateCache();
        
        CCShaderCache::sharedShaderCache()->reloadDefaultShaders();
        CCTextureCache::reloadAllTextures();
        CCNotificationCenter::sharedNotificationCenter()->postNotification(EVNET_COME_TO_FOREGROUND, NULL);
        CCDirector::sharedDirector()->setGLDefaultValues(); 
    }
}

}
