CC      = gcc
CXX     = g++
TARGET	= GodsInvader
CCFLAGS = -Wall
CXXFLAGS = -Wall
VISIBILITY = 

COCOS2DX_PATH = /home/igor/Development/cocos2d-x/cocos2dx
COCOS_PATH = /home/igor/Development/cocos2d-x

INCLUDES =  -I../ \
			-I../Classes \
			-I../Classes/Screens \
			-I../Classes/Managers \
			-I../Classes/Entities \
			-I../Classes/Utils \
			-I../Classes/Graphics \
			-I$(COCOS2DX_PATH) \
			-I$(COCOS2DX_PATH)/platform/third_party/linux \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libfreetype2 \
			-I$(COCOS2DX_PATH)/cocoa \
			-I$(COCOS2DX_PATH)/include \
			-I$(COCOS2DX_PATH)/platform \
			-I$(COCOS2DX_PATH)/platform/linux \
			-I$(COCOS2DX_PATH)/kazmath/include \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libxml2 \
			-I$(COCOS2DX_PATH)/platform/third_party/linux/libjpeg  \
			-I$(COCOS_PATH)/extensions/ \
			-I$(COCOS_PATH)/external/ \
			-I$(COCOS_PATH)/CocosDenshion/include


DEFINES = -DLINUX

OBJECTS = ./main.o \
			../Classes/Options.o \
			../Classes/AppDelegate.o \
			../Classes/Utils/Utils.o \
			../Classes/Entities/Entity.o \
			../Classes/Entities/Gas.o \
			../Classes/Entities/Pickup.o \
			../Classes/Entities/Platform.o \
			../Classes/Entities/BarEntity.o \
			../Classes/Entities/Hero.o \
			../Classes/Entities/Castle.o \
			../Classes/Entities/BaseEnemy.o \
			../Classes/Entities/BaseBullet.o \
			../Classes/Entities/Cloud.o \
			../Classes/Entities/SmallCloud.o \
			../Classes/Entities/BaseExplosion.o \
			../Classes/Managers/EntityManager.o \
			../Classes/Screens/Screen.o \
			../Classes/Screens/Level.o \
			../Classes/Screens/Preloader.o \
			../Classes/Managers/ScreenManager.o \
			../Classes/Graphics/Texture.o \
			../Classes/Screens/GameOver.o \
			../Classes/Screens/GameWon.o \

LBITS := $(shell getconf LONG_BIT)
ifeq ($(LBITS),64)
STATICLIBS_DIR = $(COCOS2DX_PATH)/platform/third_party/linux/libraries/lib64
else
STATICLIBS_DIR = $(COCOS2DX_PATH)/platform/third_party/linux/libraries
endif
STATICLIBS = 
STATICLIBS = $(STATICLIBS_DIR)/libfreetype.a \
				$(STATICLIBS_DIR)/libxml2.a \
				$(STATICLIBS_DIR)/libpng.a \
				$(STATICLIBS_DIR)/libjpeg.a \
				$(STATICLIBS_DIR)/libtiff.a \
				$(COCOS_PATH)//lib/linux/Debug/libbox2d.a \
#				$(STATICLIBS_DIR)/libGLEW.a \

SHAREDLIBS = 
ifeq ($(LBITS),64)
SHAREDLIBS_DIR = $(COCOS_PATH)/CocosDenshion/third_party/fmod/lib64/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex64
else
SHAREDLIBS_DIR = $(COCOS_PATH)/CocosDenshion/third_party/fmod/api/lib
SHAREDLIBS = -L$(SHAREDLIBS_DIR) -lfmodex
endif

SHAREDLIBS += -lglfw 
SHAREDLIBS += -Wl,-rpath,$(SHAREDLIBS_DIR)
SHAREDLIBS += -L$(COCO2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib -lGLEW
SHAREDLIBS += -Wl,-rpath,$(COCOS2DX_PATH)/platform/third_party/linux/glew-1.7.0/glew-1.7.0/lib

BIN_DIR_ROOT=bin
BIN_DIR = $(BIN_DIR_ROOT)

debug: BIN_DIR = $(BIN_DIR_ROOT)/debug
debug: CCFLAGS += -g3 -O0
debug: CXXFLAGS += -g3 -O0
debug: SHAREDLIBS += -L$(COCOS_PATH)/lib/linux/Debug -lcocos2d -lrt -lz -lcocosdenshion
debug: SHAREDLIBS += -Wl,-rpath,$(COCOS_PATH)/lib/linux/Debug/
debug: DEFINES += -DDEBUG -DCOCOS2D_DEBUG=0
debug: $(TARGET)

release: BIN_DIR = $(BIN_DIR_ROOT)/release
release: CCFLAGS += -O3
release: CXXFLAGS += -O3
release: SHAREDLIBS += -L$(COCOS_PATH)/lib/linux/Release -lcocos2d -lrt -lz -lcocosdenshion
release: SHAREDLIBS += -Wl,-rpath,$(COCOS_PATH)/lib/linux/Release/
release: DEFINES += -DNDEBUG
release: $(TARGET)

####### Build rules
$(TARGET): $(OBJECTS) 
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(OBJECTS) -o $(BIN_DIR)/$(TARGET) $(SHAREDLIBS) $(STATICLIBS)

####### Compile
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) $(DEFINES) $(VISIBILITY) -c $< -o $@

clean: 
	rm -f $(OBJECTS) $(TARGET) core
