# packman

#### A packman implementation using the [2D-engine][1]

[1]: https://github.com/firecoders/2D-engine

This a reimplementation (from scratch) of the packman found in [my cpp-games
repository][2], so I reuse the assets.

[2]: https://github.com/shak-mar/cpp-games

## try it out!

You need a linux installation with
* SFML 2.1
* cmake >= 2.6
* a C++ compiler that supports `-std=c++11`
* git ( or just download a tarball )

If you have everything, just open a shell and run:
```sh
git clone https://github.com/firecoders/packman.git
cd packman
./cmake.sh setup all
./packman
```

You will first see a 16x16 questionmark, which is a placeholder for the
currently missing splashscreen. Press space to continue into the game.

## license

This project is [licensed under MIT][3].

[3]: https://github.com/firecoders/packman/blob/master/LICENSE
