G52CPP coursework parts 3 and 4
================================

This readme includes instructions for various different platforms since you suggested that you may want to use different platforms. 
Please note that we can support you on Windows, e.g. helping out if there is some configuration issue, but you should only use a different platform if you think you can do so without needing our support for it!
i.e. the different options are provided for your convenience, at your own risk.

You can demo the coursework using any platform you wish - just make sure it works when you demo it.
It should be possible to take your files to any other platform and they just run.
If you want to submit to the hall of fame, please recompile the code on the lab PCs at that time, and provide me an exe for windows.

IMPORTANT: If you change platforms or versions of Visual Studio after you have added files, you will need to remember to add them to the project / makefiles that you are using.


Windows:
========

If you are running on Visual Studio 2017 (e.g. lab pcs), that is the default, so just run the CourseworkBase2018.sln file which is in this directory.
If you are running on Visual Studio 2015 (e.g. flexible desktop), instead run the CourseworkBase_VS2015.sln file which is in this directory.
If you are running on Visual Studio 2013, instead run the CourseworkBase_VS2013.sln file which is in this directory.

When you build, the output executables will be placed in the Debug and Release directories in this folder.
When you run the program from within visual studio, it will look for things like the fonts and images in the src directory.


Linux Quick Run
===============

In the Linux directory is a readme and a makefile. Follow the instructions in the readme. You may need to change the paths in the makefile if your system has things installed in different directories.
Someone made this for me, and I tested it and it compiled on the Linux server here so it should be fine I hope. If it fails, you can either fix it if you know how, or follow Steve's instructions below...
Note that the SDL code is in a relative directory, SDL, within the main directory. So the makefile is set up to use ../SDL as the root directory for SDL. You may want to change this to use the SDL header files that you installed instead.
Note: Mac users may be able to use a similar makefile by just modifying the one above. I don't know enough about the Mac OS though to know what to change - but hopefully as Mac users you do. Otherwise, use the instructions below.


Proper Configuration for Mac or Linux
=====================================

Dr Steven Bagley set up a cmake system for me which should work to build you makefiles which are configured for your own system. 
In theory these should work for you regardless of your platform. His instructions follow:

This uses cmake to find the required libraries and build the relevant project files for your preferred build system. You will need to have installed cmake (cmake.org) along with the relevant SDL libraries (SDL2, SDL2_ttf and SDL2_image). These exist for Windows, Mac and Linux and should be installed in the appropriate manner.

He provided a GOT repository that you can close but given the response I got to this in lectures, I added this stuff to the same coursework zip as for Windows/Linux. So I changed the instructions a little...

First change into the cloned repository, e.g.:

cd <somepath>/CPPCoursework2018

Now we need to create and change into a build directory to contain everything:

mkdir build
cd build

Finally, we need to generate the build files for the project. On a Mac, assuming you've followed the steps above you would execute the following:

cmake -G Xcode ..

which would generate a G52CPP.xcodeproj that can be opened in XCode to build the project. 

Under linux, make files can be created using:

cmake -G 'Unix Makefiles' ..

instead (note the quote marks), which will generate a Makefile that can be used to build the project. 

You can then edit the files and project/Makefiles as normal to complete your coursework. 

Similar generators exist for cmake to create build files for VisualStudio, Eclipse etc.
