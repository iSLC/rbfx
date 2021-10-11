//
// Copyright (c) 2017-2020 the rbfx project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <Urho3D/Engine/EngineDefs.h>
#include "Project.h"
#include "Editor.h"
#include "Pipeline/Commands/BuildAssets.h"


namespace Urho3D
{

BuildAssets::BuildAssets(Context* context)
    : SubCommand(context)
{
}

void BuildAssets::RegisterObject(Context* context)
{
    context->RegisterFactory<BuildAssets>();
}

void BuildAssets::RegisterCommandLine(CLI::App& cli)
{
    SubCommand::RegisterCommandLine(cli);
    cli.add_flag("--full", full_, "Disable out-of-date checks and rebuild cache completely.");
    cli.add_option("flavor", flavor_, "Flavor to build.");
}

void BuildAssets::Execute()
{
    auto* project = GetSubsystem<Project>();
    if (project == nullptr)
    {
        GetSubsystem<Editor>()->ErrorExit("BuildAssets subcommand requires project being loaded.");
        return;
    }

    PipelineBuildFlags flags{PipelineBuildFlag::EXECUTE_OPTIONAL};
    if (!full_)
        flags |= PipelineBuildFlag::SKIP_UP_TO_DATE;

    auto* pipeline = GetSubsystem<Pipeline>();
    pipeline->BuildCache(pipeline->GetFlavor(flavor_), flags);
    pipeline->WaitForCompletion();
}

}
