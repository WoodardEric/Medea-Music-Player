# Medea-Music-Player
A simple wav player(for now)<br/><br/>
Made using wxWidgets and portaudio libraries<br/><br/>
Thanks to icon king1 for the icons<br/>
From: https://freeicons.io/icon-list/material-icons-alert-and-av<br/>

# Building
For now can only build on windows with visual studio 2019.<br/>
*Make sure to read the notes after each step before following the guides*<br/><br/>

1) Download and install visual sudio 2019
https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=msvc-160

2) clone wxWidgets to your pc
https://github.com/wxWidgets/wxWidgets

3) Build wxWidgets by following this video
https://www.youtube.com/watch?v=sRhoZcNpMb4

note: we only need the x64 debug and release. 
On the tool bar there are two drop down boxes one should say Debug and the other x84 or x64.
Make sure it is set to x64 then from the menu bar navigate to build then select build solution(or press f6)
Then do this again but change the Debug box to Release.

Also: Make sure to set up the environment variable how he shows in the video.

4) clone portaudio
https://github.com/PortAudio/portaudio

5) Follow his guide to build
http://files.portaudio.com/docs/v19-doxydocs/compile_windows.html
skip step 3 and do step 4

In step 7 <br/>
Do:<br/>
C/C++ -> Optimization -> Omit frame pointers = Yes

skip:<br/>
Optional: C/C++ -> Code Generation -> Floating point model = fast

In step 9 use:<br/>
PA_USE_ASIO<br/>
PA_USE_DS (DirectSound)<br/>
PA_USE_WMME (MME)<br/>
PA_USE_WASAPI<br/>

In step 10 you only need to build for x64
Skip the "Building without ASIO support" section

6) Add a system environment variable named PORTAUDIO 
that points to the directy where you cloned portaudio

This step is similar to in the video on building wxWidgets
But this guide also goes through environment variables
https://www.computerhope.com/issues/ch000549.htm

7) Clone this repo to a directory. If the environment variable are 
set correctly then all the librarys will be linked to the project
and the app should compile and build.


