#ifndef NEO_LEVELLOADER_H
#define NEO_LEVELLOADER_H

#include "NeoEngine.h"
#include "Object.h"

#include <string>

namespace Neo 
{
class Renderer;
class Level;
class SceneFile;
class NEO_ENGINE_EXPORT LevelLoader
{
	static std::vector<SceneFile*> s_loaders;
public:
	static bool load(Level& level, const char* file, const char* rootNode = nullptr);
	static bool load(Level& level, const char* file, ObjectHandle rootNode);

	static bool save(Level& level, const char* file, const char* rootNode = nullptr);
	static bool save(Level& level, const char* file, ObjectHandle rootNode);

	static void registerLoader(SceneFile* ldr);
	static bool supportsExtension(const char* ext);
};

#define REGISTER_LEVEL_LOADER(classname) namespace { \
class classname##_register\
{\
public:\
	classname##_register() { \
		Neo::LevelLoader::registerLoader(&obj);\
	} \
	classname obj; \
};\
classname##_register g_obj;\
}

class NEO_ENGINE_EXPORT SceneFile
{
public:
	virtual bool load(Level& level, const std::string& file, ObjectHandle root = ObjectHandle()) = 0;
	virtual bool save(Level& level, const std::string& file, ObjectHandle root = ObjectHandle()) = 0;

	virtual bool supportsExtension(const std::string& ext) = 0;
	virtual const char* getName() const = 0;

	static std::string findExtension(const std::string& f);
};

}

#endif // NEO_LEVELLOADER_H