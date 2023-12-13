# Comet Buster FIP1A

A Small C project using SDL1.2 fixed by [Roman G](https://github.com/chaun14) and [Jordan B](https://github.com/jordanbmrd) @ IMT Atlantique
And based on many teacher's work throught the (long) time.

Find the projet's github repository [here](https://github.com/chaun14/comet-buster/)

## Features

- Working game base without too much segfaults as far as I know
- Sounds
- Startup / Gameover title messages
- High Score save (add to leaderboard if name doesn't exitst, otherwise update only if new score is higher than previous high score)
- Nice health hearts

## Installation

- Please use a real os such as linux to avoid problems :/
- Make sure you have all required depedencies such as `make gcc libsdl1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev` ¯\\\_(ツ)\_/¯
- Run `sh start.sh` ʘ_ʘ
- Enjoy :)

# Known issues

- The sound system can only play one sound at once
- I failed the string sanitization when entering the score save username, please be cautious otherwise you may run into problems
- For some reason that I didn't take the time to dig into, the end screen key press might not work or my require spamming a bit

## Screenshot

![](https://github.com/chaun14/comet-buster/blob/master/images/image.png?raw=true)

BTW if you're using this repo to avoid working on the project that's not a clever idea, always do by yourself otherwise you won't understand ;)
