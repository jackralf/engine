#include "FontManager.h"
#include "../Helpers/FilePath.h"
#include "../Logger.h"
#include "../Context.h"
#include "../Graphics/GraphicsManager.h"
#include "../Scenes/SceneManager.h"
#include "../Scenes/BaseScene.h"
#include "../Components/CameraComponent.h"
#include "../Objects/FreeCamera.h"
#include "../Helpers/Math.h"

#ifdef ANDROID
#include "../StarEngine.h"
#endif

namespace star 
{
	FontManager::FontManager():
		mLibrary(0)
	{
		auto error = FT_Init_FreeType(&mLibrary);
		if(error)
		{
			LOG(star::LogLevel::Error,
				_T("Font Manager : Could not initialize FreeType library"),
				STARENGINE_LOG_TAG);
		}

		LOG(star::LogLevel::Info,
			_T("Font Manager : Initialized FreeType library"),
			STARENGINE_LOG_TAG);
	}

	FontManager::~FontManager()
	{

	}

	void FontManager::EraseFonts()
	{
		for(const auto& font : mFontList)
		{
			if(font.second)
			{
				font.second->DeleteFont();
			}
			delete font.second;
		}
		mFontList.clear();
		
		FT_Done_FreeType(mLibrary);
	}

	bool FontManager::LoadFont(const tstring& path, const tstring& name, uint32 size)
	{
		if(mFontList.find(name) != mFontList.end())
		{
			LOG(star::LogLevel::Info,
				_T("Font Manager : Font ") + name + _T(" already exist, using that"),
				STARENGINE_LOG_TAG);
			return true;
		}

		star::FilePath filepath(path);

		Font* tempFont = new Font();
		if(tempFont->Init(filepath.GetFullPath(), size, mLibrary))
		{
			mFontList[name] = tempFont;

		}
		else
		{
			delete tempFont;
			return false;
		}
		return true;
	}

	bool FontManager::DeleteFont(const tstring& name)
	{
		auto it = mFontList.find(name);
		if(it != mFontList.end())
		{
			mFontList.erase(it);
			return true;
		}
		return false;
	}

	const Font* FontManager::GetFont(const tstring& name)
	{
		ASSERT_LOG(
			mFontList.find(name) != mFontList.end(),
			_T("No such font"), STARENGINE_LOG_TAG
			);
		return mFontList[name];
	}
}
