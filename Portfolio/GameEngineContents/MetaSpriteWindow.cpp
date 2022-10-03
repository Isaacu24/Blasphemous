#include "PreCompile.h"
#include "MetaSpriteWindow.h"
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineCoreDebug.h>
#include "MetaTextureRenderer.h"
#include <GameEngineCore/GameEngineRes.h>
#include "MetaSpriteManager.h"

MetaSpriteWindow::MetaSpriteWindow()
    : CurMetaFile_{}
    , CurAtlasFile_{}
{}

MetaSpriteWindow::~MetaSpriteWindow() {}

void MetaSpriteWindow::Initialize(GameEngineLevel* _Level) {}

void MetaSpriteWindow::OnGUI(GameEngineLevel* _Level, float _DeltaTime)
{
    AtlasFileButton(_Level);
    MetaFileButton(_Level);

    AllFolderButton(_Level);
}


void MetaSpriteWindow::MetaFileButton(GameEngineLevel* _Level)
{
    if (nullptr == TargetTexture)
    {
        return;
    }

    if (true == ImGui::Button("MetaFileLoad") && nullptr == Renderer)
    {
        std::string Path
            = GameEngineGUI::OpenFileDlg(GameEngineString::AnsiToUTF8Return("메타 파일 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            GameEngineFile LoadFile = GameEngineFile(Path);
            LoadFile.Open(OpenMode::Read, FileMode::Text);

            std::string AllText = LoadFile.GetString();

            MetaParsing(AllText);

            if (0 == TargetTexture->GetCutCount())
            {
                for (auto& [Index, PosX, PosY, Width, Height, PivotX, PivotY] : MetaDatas_)
                {
                    TargetTexture->Cut(PosX, TargetTexture->GetScale().y - PosY - Height, Width, Height);
                }
            }

            GameEngineActor* PreviewActor = _Level->CreateActor<GameEngineActor>();
            PreviewActor->GetTransform().SetLocalPosition(float4{-300.0f, 0.0f, 0.0f});
            Renderer = PreviewActor->CreateComponent<MetaTextureRenderer>();

            std::string FileName = std::filesystem::path{Path}.filename().string();

            std::string ImageName     = std::filesystem::path{FileName}.replace_extension("").string();  // Remove .meta
            std::string AnimationName = std::filesystem::path{ImageName}.replace_extension("").string();  // Remove .png

             Renderer->CreateFrameAnimationCutTexture(
                 AnimationName, {ImageName, 0, static_cast<unsigned int>(MetaDatas_.size() - 1), 0.1f, true});

            //Renderer->ChangeFrameAnimation(AnimationName);

            Renderer->SetCurData(MetaDatas_);

            MetaSpriteManager::Inst_->Insert(AnimationName, MetaDatas_);
        }
    }

    if (nullptr != Renderer && nullptr != TargetTexture && 0 != TargetTexture->GetCutCount())
    {
        ImGui::SliderInt("ImageIndex", &CurFrame, 0, TargetTexture->GetCutCount() - 1);
        Renderer->SetTexture(TargetTexture, CurFrame);
        Renderer->ScaleToCutTexture(CurFrame);
    }

    //디버깅 렌더
    if (nullptr != TargetTexture)
    {
        float4 ImagePos = TargetTexture->GetScale().Half();

        ImagePos.y = -ImagePos.y;

        GameEngineDebug::DrawTexture(TargetTexture, ImagePos);

        for (size_t i = 0; i < static_cast<size_t>(TargetTexture->GetCutCount()); i++)
        {
            float4 Pos   = TargetTexture->GetCutPos(i);
            float4 Scale = TargetTexture->GetCutScale(i);

            Pos.y = -Pos.y;
            Pos.x += Scale.x * 0.5f;
            Pos.y -= Scale.y * 0.5f;

            GameEngineDebug::DrawBox(Pos, Scale, float4::ZERO, float4(1.0f, 0.0f, 0.0f, 0.5f));
        }
    }

    if (false == CurMetaFile_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(CurMetaFile_.c_str());
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
            std::string        FileName   = std::filesystem::path{Path}.filename().string();
            GameEngineTexture* NewTexture = GameEngineRes<GameEngineTexture>::Find(FileName);

            TargetTexture = (nullptr != NewTexture) ? NewTexture : GameEngineTexture::Load(Path);
        }
    }

    if (false == CurAtlasFile_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(TargetTexture->GetNameCopy().c_str());
    }
}

void MetaSpriteWindow::AllFolderButton(GameEngineLevel* _Level)
{
    if (true == ImGui::Button("FolderLoad"))
    {
        std::string Path
            = GameEngineGUI::OpenFolderDlg(GameEngineString::AnsiToUTF8Return("폴더 로드"), MetaDir.GetFullPath());

        if (false == Path.empty())
        {
            GameEngineDirectory Dir;
            MovePath(Dir, {"ContentsResources", "Resources", "MetaAtlas", "Penitent"});

            std::vector<GameEngineFile> Textures = Dir.GetAllFile();

            for (size_t i = 0; i < Textures.size(); i++)
            {
                std::string FileName  = Textures[i].GetFileName();
                std::string extension = std::filesystem::path{FileName}.extension().string();

                if (".png" == extension)
                {
                    GameEngineTexture* NewTexture = GameEngineRes<GameEngineTexture>::Find(Textures[i].GetFullPath());

                    if (nullptr != NewTexture)
                    {
                        Textures_.push_back(NewTexture);
                        continue;
                    }

                    NewTexture = GameEngineTexture::Load(Textures[i].GetFullPath());
                    Textures_.push_back(NewTexture);
                }

                else if (".meta" == extension)
                {
                    Textures[i].Open(OpenMode::Read, FileMode::Text);

                    std::string AllText = Textures[i].GetString();

                    MetaSpriteManager::Inst_->MetaParsing(AllText);

                    std::string FileName      = std::filesystem::path{Textures[i].GetFileName()}.filename().string();
                    std::string ImageName     = std::filesystem::path{FileName}.replace_extension("").string();
                    std::string AnimationName = std::filesystem::path{ImageName}.replace_extension("").string();

                    if (0 == MetaSpriteManager::Inst_->MetaDatas_.size())
                    {
                        int a = 0;
                    }

                    MetaSpriteManager::Inst_->Insert(AnimationName, MetaSpriteManager::Inst_->MetaDatas_);

                    AllDatas_.push_back(MetaDatas_);
                }
            }

            CutAllTexture();
        }
    }
}

void MetaSpriteWindow::MetaParsing(const std::string& _AllText)
{
    MetaDatas_.clear();

    size_t StartPos       = 0;
    size_t AnimationStart = 0;

    while (true)
    {
        AnimationStart = _AllText.find("second:", AnimationStart);

        if (AnimationStart == std::string::npos)
        {
            break;
        }

        size_t AnimationEnd = _AllText.find("externalObjects", AnimationStart);

        if (AnimationEnd == std::string::npos)
        {
            break;
        }

        std::string AnimationString = _AllText.substr(AnimationStart, AnimationEnd - AnimationStart);

        StartPos = _AllText.find("rect:", StartPos);

        if (StartPos == std::string::npos)
        {
            break;
        }

        size_t EndPos = _AllText.find("outline:", StartPos);

        if (EndPos == std::string::npos)
        {
            break;
        }

        std::string CutDataString = _AllText.substr(StartPos, EndPos - StartPos);

        int   Index  = 0;
        float StartX = 0;
        float StartY = 0;
        float SizeX  = 0;
        float SizeY  = 0;
        float PivotX = 0;
        float PivotY = 0;

        {
            std::string FindString   = "second:";
            size_t      DataStartPos = AnimationString.find(FindString);
            size_t      DataEndpos   = AnimationString.find("\n", DataStartPos);

            std::string IndexString = AnimationString.substr(DataStartPos, DataEndpos);

            size_t UnderBarPos = IndexString.rfind("_");

            size_t Size = IndexString.size();

            IndexString = IndexString.substr(UnderBarPos + 1, IndexString.size() - UnderBarPos);

            Index = atoi(IndexString.c_str());
        }

        {
            std::string FindString   = "x:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            StartX = atof(XString.c_str());
        }

        {
            std::string FindString   = "y:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
            StartY = atof(XString.c_str());
        }

        {
            std::string FindString   = "width:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);
            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());
            SizeX = atof(XString.c_str());
        }

        {
            std::string FindString   = "height:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("\n", DataStartPos);

            std::string XString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            SizeY = atof(XString.c_str());
        }

        {
            std::string FindString   = "pivot:";
            size_t      DataStartPos = CutDataString.find(FindString);
            size_t      DataEndpos   = CutDataString.find("}", DataStartPos);

            std::string PivotString
                = CutDataString.substr(DataStartPos + FindString.size(), DataEndpos - DataStartPos + FindString.size());

            size_t XStartPos = PivotString.find("x: ");
            size_t XEndpos   = PivotString.find(", ");

            std::string XString = PivotString.substr(XStartPos + 3, XEndpos - 5);

            size_t YStartPos = PivotString.find("y: ");
            size_t YEndpos   = PivotString.find("}");

            std::string YString = PivotString.substr(YStartPos + 3, PivotString.size() - YEndpos);

            PivotX = atof(XString.c_str());
            PivotY = atof(YString.c_str());

            MetaData Data = {Index, StartX, StartY, SizeX, SizeY, PivotX, PivotY};

            MetaDatas_.push_back(Data);
        }

        std::string DebugText;
        DebugText += "Animation : " + std::to_string(Index) + ",";
        DebugText += "StartX : " + std::to_string(StartX) + ",";
        DebugText += "StartY : " + std::to_string(StartY) + ",";
        DebugText += "SizeX : " + std::to_string(SizeX) + ",";
        DebugText += "SizeY : " + std::to_string(SizeY) + ",";
        DebugText += "PivotX : " + std::to_string(PivotX) + ",";
        DebugText += "PivotY : " + std::to_string(PivotY) + ",";
        DebugText += "\n";

        GameEngineDebug::OutPutString(DebugText.c_str());
        StartPos += 1;
        AnimationStart += 1;
    }

    // Renderer->SetTexture(TargetTexture, 0);
    // Renderer->SetSamplingModePoint();
    // Renderer->ScaleToCutTexture(0);
}

//퐅더 전용 Texture Cut 함수
void MetaSpriteWindow::CutAllTexture()
{
    for (size_t i = 0; i < Textures_.size(); i++)
    {
        TargetTexture = Textures_[i];

        if (nullptr == TargetTexture)
        {
            continue;
        }

        for (size_t j = 0; j < AllDatas_[i].size(); j++)
        {
            TargetTexture->Cut(AllDatas_[i][j].PosX,
                               TargetTexture->GetScale().y - AllDatas_[i][j].PosY - AllDatas_[i][j].Height,
                               AllDatas_[i][j].Width,
                               AllDatas_[i][j].Height);
        }
    }

    Textures_.clear();
}


// void MetaSpriteWindow::MetaSetPivot()
//{
//     float X = Vectors_[CurFrame].x - 0.5f;
//     float Y = (1 - Vectors_[CurFrame].y) - 0.5f;
//
//     float SizeX = TargetTexture->GetCutScale(CurFrame).x;
//     float SizeY = TargetTexture->GetCutScale(CurFrame).y;
//
//     float Width = abs(X * SizeX);
//     float Height = abs(Y * SizeY);
//
//     //1사분면일 때
//     if (0.f < X &&
//         0.f > Y)
//     {
//         Renderer->GetTransform().SetLocalPosition({-(Width), -(Height)});
//     }
//     // 2사분면일 때
//     else if (0.f > X
//         && 0.0f > Y)
//     {
//         Renderer->GetTransform().SetLocalPosition({(Width), -(Height)});
//     }
//     // 3사분면일 때
//     else if (0.f > X
//         && 0.f < Y)
//     {
//         Renderer->GetTransform().SetLocalPosition({(Width), (Height)});
//     }
//     // 4사분면일 때
//
//     else if (0.f < X && 0.f < Y)
//     {
//         Renderer->GetTransform().SetLocalPosition({-(Width), (Height)});
//     }
// }


