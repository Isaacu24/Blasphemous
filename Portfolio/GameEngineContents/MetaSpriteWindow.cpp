#include "PreCompile.h"
#include "MetaSpriteWindow.h"
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineCoreDebug.h>

MetaSpriteWindow::MetaSpriteWindow()
    : CurMetaFolder_{}
    , CurAtlasFolder_{}
    , CurMetaFile_{}
    , CurAtlasFile_{}
{}

MetaSpriteWindow::~MetaSpriteWindow() {}

void MetaSpriteWindow::Initialize(GameEngineLevel* _Level) {}

void MetaSpriteWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
    AtlasFileButton(_Level);
    MetaFileButton(_Level);

    // AtlasFileButton();
    // MetaFileButton();
}


void MetaSpriteWindow::MetaFileButton(GameEngineLevel* _Level)
{
    if (nullptr == TargetTexture)
    {
        return;
    }


    if (true == ImGui::Button("MetaFileLoad") && 0 == TargetTexture->GetCutCount())
    {
        std::string Path
            = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("메타 파일 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            GameEngineFile LoadFile = GameEngineFile(Path);
            LoadFile.Open(OpenMode::Read, FileMode::Text);

            std::string AllText = LoadFile.GetString();

            size_t StartPos = 0;

            while (true)
            {
                StartPos = AllText.find("rect:", StartPos);

                if (StartPos == std::string::npos)
                {
                    break;
                }

                size_t EndPos = AllText.find("outline:", StartPos);

                if (EndPos == std::string::npos)
                {
                    break;
                }

                std::string CutDataString = AllText.substr(StartPos, EndPos - StartPos);

                int StartX = 0;
                int StartY = 0;
                int SizeX  = 0;
                int SizeY  = 0;

                {
                    std::string FindString   = "x:";
                    size_t      DataStartPos = CutDataString.find(FindString);
                    size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
                    std::string XString      = CutDataString.substr(DataStartPos + FindString.size(),
                                                               DataEndpos - DataStartPos + FindString.size());
                    StartX                   = atoi(XString.c_str());
                }

                {
                    std::string FindString   = "y:";
                    size_t      DataStartPos = CutDataString.find(FindString);
                    size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
                    std::string XString      = CutDataString.substr(DataStartPos + FindString.size(),
                                                               DataEndpos - DataStartPos + FindString.size());
                    StartY                   = atoi(XString.c_str());
                }

                {
                    std::string FindString   = "width:";
                    size_t      DataStartPos = CutDataString.find(FindString);
                    size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
                    std::string XString      = CutDataString.substr(DataStartPos + FindString.size(),
                                                               DataEndpos - DataStartPos + FindString.size());
                    SizeX                    = atoi(XString.c_str());
                }

                {
                    std::string FindString   = "height:";
                    size_t      DataStartPos = CutDataString.find(FindString);
                    size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
                    std::string XString      = CutDataString.substr(DataStartPos + FindString.size(),
                                                               DataEndpos - DataStartPos + FindString.size());
                    SizeY                    = atoi(XString.c_str());
                }

                TargetTexture->Cut(StartX, StartY, SizeX, SizeY);
                StartPos += 1;
            }

            GameEngineActor* NewActor = _Level->CreateActor<GameEngineActor>();

            GameEngineTextureRenderer* Renderer = NewActor->CreateComponent<GameEngineTextureRenderer>();

            Renderer->SetTexture(TargetTexture, 2);
            Renderer->ScaleToCutTexture(2);

            // TargetTexture->Cut();


            // CurMetaFolder_ = GameEnginePath::GetFileName(Path);
            // GameEngineMetaDataFolder::Load(Path.c_str());
        }
    }


    // if (nullptr != TargetTexture)
    //{
    //     float4 ImagePos = TargetTexture->GetScale().Half();

    //    GameEngineDebug::DrawTexture(TargetTexture, ImagePos);

    //    for (size_t i = 0; i < TargetTexture->GetCutCount(); i++)
    //    {
    //        float4 Pos = TargetTexture->GetCutPos(i);
    //        float4 Scale = TargetTexture->GetCutScale(i);

    //        GameEngineDebug::DrawBox(Pos + Scale.Half(), Scale, float4::ZERO, float4(1.0f, 0.0f, 0.0f, 0.5f));
    //    }
    //}


    if (false == CurMetaFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(CurMetaFolder_.c_str());
    }
}

void MetaSpriteWindow::AtlasFileButton(GameEngineLevel* _Level)
{
    if (true == ImGui::Button("AtlasFileLoad"))
    {
        std::string Path = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("아틀라스 시트 로드"),
                                                      MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            TargetTexture = GameEngineTexture::Load(Path);
        }
    }

    if (false == CurAtlasFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(TargetTexture->GetNameCopy().c_str());
    }
}

