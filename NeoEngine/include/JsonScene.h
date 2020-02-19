#ifndef __JSON_SCENE_H__
#define __JSON_SCENE_H__

#include <LevelLoader.h>

namespace Neo
{

class NEO_ENGINE_EXPORT JsonScene : public SceneFile
{
public:
	bool load(Level& level, const std::string& file, ObjectHandle root = ObjectHandle()) override;
	bool save(Level& level, const std::string& file, ObjectHandle root = ObjectHandle()) override;
	bool supportsExtension(const std::string& ext) override;
	const char* getName() const override { return "JsonScene"; }
};

}

#endif