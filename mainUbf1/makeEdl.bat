rem
call ..\makedefs.bat
rem
%mcpp% inputs\simAgentTest.epp > simAgentTest.edl  -I ..\data -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""
%mcpp% inputs\agentTest.epp    > agentTest.edl     -I ..\data -DFONT_PATH="\"../data/fonts/\""  -DFONT_11_19_PATH="\"../data/fonts/11x19/normal/\"" -DTEXTURES_PATH="\"../data/textures/\""
