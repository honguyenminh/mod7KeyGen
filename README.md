# mod7KeyGen
A basic product key generator for Microsoft products from 90s that use mod7 algorithm (e.g Windows 95, Office 97, Windows NT,...)
This repo isn't meant to encourage piracy, only used for sciectific or educational purposes.
The code and algorithm written here is not clean and efficient at all, but hey.

Algorithm source: gurney.dev/posts/mod7/

## About
mod7KeyGen is a win32 terminal (console) app, works like a normal terminal app on Linux, but it's on Windows.
Releases are compiled as /MTd, all binaries should work without Visual C++ installed, in exchange for the humble of files required for such a small project.

## Instructions
To run this app, don't double-click it, won't work.
Instead, you have to run from a command prompt (cmd.exe) followed by arguments.

### How to run
1. Download latest release, then extract (if needed) to your desired folder (Desktop should work :) i guess)
2. Open command prompt and navigate to that folder with cd command, or, 
   Hold down Shift and right-click the folder, then "Open command window here"
3. Type command with syntax described below, or just type `MOD7KeyGen.exe --help`

### Syntax
Command syntax:    MOD7KeyGen.exe    {argument}(required)   {number of key(s)}(optional)

{argument} is required to set key type, list below.
Generate 1 key with the specified key type set by {argument}
Number of key(s) generated can be modified with the {number of key} option
**Warning: Only one argument can be passed at a time.**

### Arguments list
Shorthand args | Full-size args | Description
-------------- | -------------- | -----------
-h | --help | Display help screen
-10 | --10digitCD | Set key type as 10-digit for CD retails. Is oftenly used in Windows 95, NT,... as CD retails
-11 | --11digitCD | Set key type as 11-digit for CD retails. This type can be found in Office 97,...
-20 | --20digitOEM | Set key type as 20-digit for OEM versions.

Example command:  MOD7KeyGen.exe -11      
                  MOD7KeyGen.exe -20 5
                  
## Build instruction (not tested on other machine)
### Dependencies
* Visual Studio
* C++ Win32 Development package?
### Build manually
1. Clone repo or download as zip and extract
1. Open solution (.sln file) with Visual Studio
2. Choose build type as release
3. Build -> Build solution (Ctrl+Shift+B)
4. Go to <insert solution folder here>/Release/
File should be there. Somewhat
  
   
   
   
    
This thing have SUPER COW POWER.
