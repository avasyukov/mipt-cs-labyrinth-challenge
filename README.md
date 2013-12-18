mipt-cs-labyrinth-challenge
===========================

Sources of labyrinth challenge created at MIPT seminars. Really ugly for the moment. I'll do my best to improve them, really.

Tested with gcc on Fedora 16 and above.

Licensed under GPLv3. Feel free to fork and use for your purposes.

Compile
=======

Place your logic into player/brain.h and run:

make


Run
===

Default settings start two player game. So:

First console: ./server/server

Second console: ./player/player

Third console: ./player/player

This will start two players with identical logic. Of course, you can prepare two players with different logic - just clone player.c and include different brains for these two players.
