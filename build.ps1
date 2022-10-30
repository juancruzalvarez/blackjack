Set-Location src
g++ -o ../bin/main main.cc game/game.cc game/hand.cc game/round.cc game/shoe.cc strategy/basic_strategy.cc -Wall
Set-Location ..