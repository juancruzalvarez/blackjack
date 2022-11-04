Set-Location src
g++ -o ../bin/main main.cc game/player.cc game/game.cc game/hand.cc game/round.cc game/shoe.cc strategy/perfect_strategy.cc strategy/chart_strategy.cc strategy/basic_strategy.cc strategy/improved_basic_strategy.cc strategy/chart.cc strategy/min_betting_strategy.cc strategy/count_betting_strategy.cc -Wall -Wextra
Set-Location ..