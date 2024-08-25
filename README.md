# I am not proud of any of the code in this repo.
## It's honestly a miracle that it even compiles.
This was scrapped together at the dead of night by mangling an existing multi threaded dice rolling program I had lying around to do the same thing as the C# version. 

Other than the lack of C#'s fancy dancy Parallel.For loop, this is almost exactly the same. It is still multi threaded, it still uses some semblance of thread local variables, and it still uses bit manipulation.

The main differences that I can think of are the fact that this version generates random *unsigned* longs, allowing more dice rolls per random, and the fact that it is running one method call per thread instead of using a more flexible thread pool.

## How to run
### Clone this repo
either run `git clone https://github.com/Squaduck/GravelerCpp.git` or click the big green "<> Code" button above and click "Download ZIP"
### Build the program
See Below for either [Windows](#windows) or [Linux](#linux-or-other)
### Run the compiled executable
in the cloned directory, simply run `./Graveler`

## Compilation and Compatibility
- **This project has not been extensively tested.**
### Windows
#### Using the Visual Studio Build tools
- Found [Here](https://visualstudio.microsoft.com/downloads/#build-tools-for-visual-studio-2022)
- You *should* only need the "MSVC vXXX - VS 20XX C++ {arch} build tools (latest)" component. I'm not sure if it needs anything else.

Using the Native Tools Command Prompt, navigate to the cloned project directory and run 

`cl /std:c++20 /O2 /EHsc Graveler.cpp`

- (The VS Build Tools also include Clang, but I couldn't get it to work for me on windows.)

#### Using MSYS2
- Found [Here](https://www.msys2.org/)
- Need to run `pacman -S mingw-w64-ucrt-x86_64-gcc` in any MSYS2 Command Prompt to install the GCC suite.

Using the MSYS2 UCRT64 Command Prompt, Navigate to the cloned project directory and run

`g++ Graveler.cpp -o Graveler -march=native -Ofast -std=c++20`

- (MSYS runs in a linux-esque environment where "/" is the root of the filesystem and directories are marked with forward slashes. To navigate to the project, `cd` to "/{lowercase drive letter}/{path to project}" )
- (MSYS also includes a version of clang. I didn't try it because I was running out of space on my VM's virtual disk, and didn't want a second copy of clang.)
### Linux (or other?)
Install your distro's build-essential package (or equivalent) and run either

`g++ Graveler.cpp -o Graveler -march=native -Ofast -std=c++20`

or

`clang++ Graveler.cpp -o Graveler -std=c++20 -Ofast`

- (clang probably not in build-essential. May need to be downloaded separately.)

in the project directory.

## Looking at it in an IDE
- Ensure that your IDE is set to the C++20 standard.
- Don't judge too hard. This is scrapped together from stuff I never expected to be public. Its a learning project, and I've definitely learned. (Mostly that C++ is tedious.)