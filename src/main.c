#include <math.h>

#define __POKEROK_IMPLEMENTATION
#include <pokerok.h>

int main () {
  Game game;
  init(&game, 6);

  Rules *rules = game.rules;

  shuffleDeck(game.rules->deck);

  for (int i = 0; i < numberOfDeals(&game); i++) {
    printf("%s\n", currentDeal(&game, i));
  }

  for (int i = 0; i < game.nPlayers; i++) {
    dealToPlayer(&game, i);
  }

  InitWindow(rules->screenWidth, rules->screenHeight, "POKEROK");
  SetTargetFPS(60);

  int cnt = 0;

  while(!WindowShouldClose() && dealHandSize(&game)) {
    BeginDrawing();
      ClearBackground((Color){220,220,220,255});
      for (int i = 0; i < game.nPlayers; i++) {
        drawPlayerHandAt(rules, game.players[i], (Vector2){0, 10 + (10 + rules->cardHeight) * i});
      }
    EndDrawing();
    if ((++cnt) % 100 == 0) {
      game.round++;
      shuffleDeck(game.rules->deck);
      for (int i = 0; i < game.nPlayers; i++) {
        dealToPlayer(&game, i);
      }
    }
  }

  CloseWindow();

  return 0;
}
