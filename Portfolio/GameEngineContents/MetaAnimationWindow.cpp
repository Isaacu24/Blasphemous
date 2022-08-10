#include "PreCompile.h"
#include "MetaAnimationWindow.h"
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineMetaDataFolder.h>
#include <GameEngineCore/GameEngineMetaData.h>

MetaAnimationWindow::MetaAnimationWindow() 
    : CurMetaFolder_{}
    , CurAtlasFolder_{}
    , CurMetaFile_{}
    , CurAtlasFile_{}
{
}

MetaAnimationWindow::~MetaAnimationWindow() 
{
}

void MetaAnimationWindow::Initialize(GameEngineLevel* _Level) 
{
}

void MetaAnimationWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime) 
{
    AtlasFolderButton();
    MetaFolderButton();

    AtlasFileButton();
    MetaFileButton();
}


void MetaAnimationWindow::MetaFolderButton()
{
    if (true == ImGui::Button("MetaFolderLoad"))
    {
        if (true == CurAtlasFolder_.empty()) 
        {
            MsgBoxAssert("아틀라스 시트를 선택하기 전에 메타 파일을 선택하려고 하였습니다.");
            return;
        }

        GameEngineDirectory Dir;
        Dir.MoveParentToExitsChildDirectory("GameEngineResources");
        Dir.Move("GameEngineResources");
        Dir.Move("Resources");
        Dir.Move("Metafile");

        std::string Path = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("메타 파일 로드"), Dir.GetFullPath());

        if (false == Path.empty())
        {
            CurMetaFolder_ = GameEnginePath::GetFileName(Path);
            GameEngineMetaDataFolder::Load(Path.c_str());
        }
    }

    if (false == CurMetaFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(CurMetaFolder_.c_str());
    }
}

void MetaAnimationWindow::AtlasFolderButton()
{
    if (true == ImGui::Button("AtlasFolderLoad"))
    {
        GameEngineDirectory Dir;
        Dir.MoveParentToExitsChildDirectory("GameEngineResources");
        Dir.Move("GameEngineResources");
        Dir.Move("Resources");
        Dir.Move("Sprite");

        std::string Path = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("아틀라스 시트 로드"), Dir.GetFullPath());

        if (false == Path.empty())
        {
            CurAtlasFolder_ = GameEnginePath::GetFileName(Path);

            GameEngineFolderTexture::Load(Path.c_str());
        }
    }

    if (false == CurAtlasFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(CurAtlasFolder_.c_str());
    }
}


void MetaAnimationWindow::MetaFileButton() 
{
}

void MetaAnimationWindow::AtlasFileButton()
{
    
}
