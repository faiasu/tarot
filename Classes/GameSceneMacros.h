//
//  GameScenMacros.h
//  tarot
//
//  Created by 福角彰啓 on 2014/06/22.
//
//
/*
 void*を引数にとるscene関数を宣言する
 引数はcreateからinitに引き渡される
 CREATE_FUNCの宣言は不要になる
 */
#define SCENE_FUNC_WITH_ARG(__TYPE__) \
static Scene* scene(void* arg) \
{ \
Scene* scene = Scene::create(); \
__TYPE__* layer = __TYPE__::create(arg); \
scene->addChild(layer); \
return scene; \
} \
CREATE_FUNC_WITH_ARG(__TYPE__);

/*
 void*を引数にとるcreate関数の宣言
 引数はinitに引き渡される
 */
#define CREATE_FUNC_WITH_ARG(__TYPE__) \
static __TYPE__* create(void* arg) \
{ \
__TYPE__ *pRet = new __TYPE__(); \
if (pRet && pRet->init(arg)) { \
pRet->autorelease(); \
return pRet; \
} \
else { \
delete pRet; \
pRet = NULL; \
return NULL; \
} \
}
