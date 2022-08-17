#include "PreCompile.h"
#include "MetaSpriteWindow.h"
#include <GameEngineCore/GameEngineFolderTexture.h>
#include <GameEngineCore/GameEngineCoreDebug.h>
#include "MetaTextureRenderer.h"
#include <GameEngineCore/GameEngineRes.h>

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

    ImGui::ShowDemoWindow();


    // AtlasFileButton();
    // MetaFileButton();
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

                int   StartX = 0;
                int   StartY = 0;
                int   SizeX  = 0;
                int   SizeY  = 0;
                float PivotX = 0;
                float PivotY = 0;

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

                    std::string XString = CutDataString.substr(DataStartPos + FindString.size(),
                                                               DataEndpos - DataStartPos + FindString.size());

                    SizeY = atoi(XString.c_str());
                }

                {
                    std::string FindString   = "pivot:";
                    size_t      DataStartPos = CutDataString.find(FindString);
                    size_t      DataEndpos   = CutDataString.find("}", DataStartPos);

                    std::string PivotString = CutDataString.substr(DataStartPos + FindString.size(),
                                                                   DataEndpos - DataStartPos + FindString.size());

                    size_t XStartPos = PivotString.find("x: ");
                    size_t XEndpos   = PivotString.find(", ");

                    std::string XString = PivotString.substr(XStartPos + 3, XEndpos - 5);

                    size_t YStartPos = PivotString.find("y: ");
                    size_t YEndpos   = PivotString.find("}");

                    std::string YString = PivotString.substr(YStartPos + 3, PivotString.size() - YEndpos);

                    PivotX = atof(XString.c_str());
                    PivotY = atof(YString.c_str());
                }

                MetaData Data = {StartX, StartY, SizeX, SizeY, PivotX, PivotY};

                MetaDatas_.push_back(Data);

                std::string DebugText;
                DebugText += "StartX : " + std::to_string(StartX) + ",";
                DebugText += "StartY : " + std::to_string(StartY) + ",";
                DebugText += "SizeX : " + std::to_string(SizeX) + ",";
                DebugText += "SizeY : " + std::to_string(SizeY) + ",";
                DebugText += "PivotX : " + std::to_string(PivotX) + ",";
                DebugText += "PivotY : " + std::to_string(PivotY) + ",";
                DebugText += "\n";

                GameEngineDebug::OutPutString(DebugText.c_str());
                StartPos += 1;
            }
            // 1. 메타정보만 로딩하여 vector에 저장
            // 2. 로딩된 텍스처가 이미 잘려있다면, 그 vector의 정보를 사용하지 않음.
            // 3. 안잘려있다면, for문을 돌아서 자름.

            if (0 == TargetTexture->GetCutCount())
            {
                for (auto& [PosX, PosY, Width, Height, PivotX, PivotY] : MetaDatas_)
                {
                    TargetTexture->Cut(PosX, PosY, Width, Height);
                }
            }


            GameEngineActor* NewActor = _Level->CreateActor<GameEngineActor>();

            NewActor->GetTransform().SetLocalPosition(float4{-300.0f, 0.0f, 0.0f});

            Renderer = NewActor->CreateComponent<MetaTextureRenderer>();
            Renderer->SetTexture(TargetTexture, 0);
            Renderer->SetSamplingModePoint();
            Renderer->ScaleToCutTexture(0);
        }
    }

    if (nullptr != Renderer && nullptr != TargetTexture && 0 != TargetTexture->GetCutCount())
    {
        ImGui::SliderInt("ImageIndex", &CurFrame, 0, TargetTexture->GetCutCount() - 1);
        Renderer->SetTexture(TargetTexture, CurFrame);
        Renderer->ScaleToCutTexture(CurFrame);
        // MetaSetPivot();
        Renderer->SetMetaData({MetaDatas_[CurFrame].PivotX, MetaDatas_[CurFrame].PivotY},
                              TargetTexture->GetCutScale(CurFrame).x,
                              TargetTexture->GetCutScale(CurFrame).y);
    }


    if (nullptr != TargetTexture)
    {
        float4 ImagePos = TargetTexture->GetScale().Half();

        ImagePos.y = -ImagePos.y;

        GameEngineDebug::DrawTexture(TargetTexture, ImagePos);

        for (size_t i = 0; i < TargetTexture->GetCutCount(); i++)
        {
            float4 Pos   = TargetTexture->GetCutPos(i);
            float4 Scale = TargetTexture->GetCutScale(i);

            Pos.y = -Pos.y;
            Pos.x += Scale.x * 0.5f;
            Pos.y -= Scale.y * 0.5f;

            GameEngineDebug::DrawBox(Pos, Scale, float4::ZERO, float4(1.0f, 0.0f, 0.0f, 0.5f));
        }
    }


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
            auto fileName = std::filesystem::path{Path}.filename().string();
            auto pTexture = GameEngineRes<GameEngineTexture>::Find(fileName);
            TargetTexture = (nullptr != pTexture) ? pTexture : GameEngineTexture::Load(Path);
        }
    }

    if (false == CurAtlasFolder_.empty())
    {
        ImGui::SameLine();
        ImGui::Text(TargetTexture->GetNameCopy().c_str());
    }
}
//
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
// z
// }
//
//
