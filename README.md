# I am not proud of any of the code in this repo.
## It's honestly a miracle that it even compiles.
This was scrapped together at the dead of night by mangling an existing multi threaded dice rolling program I had lying around to do the same thing as the C# version. 

Other than the lack of C#'s fancy dancy Parallel.For loop, this is almost exactly the same. It is still multi threaded, it still uses some semblance of thread local variables, and it still uses bit manipulation.

The main differences that I can think of are the fact that this version generates random *unsigned* longs, allowing more dice rolls per random, and the fact that it is running one method call per thread instead of using a more flexable thread pool.

## How to run
### Clone this repo
either run `git clone https://github.com/Squaduck/GravelerCpp.git` or click the big green "<> Code" button above and click "Download ZIP"
### Build the program
`cd` into the cloned directory then run `g++ Graveler.cpp -o Graveler -O3` to build it with optimizations. 

Other compilers *seem* to work, but no promises.
### Run the compiled executable
in the cloned directory, simply run `./Graveler`

## Compatibility
I cannot guarantee that this will compile on any given system. I don't know if this will even work on Windows.

At the very least I was able to compile with clang? This hasn't been tested with msvc.

## TLDR: good luck.