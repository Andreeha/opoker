#include <raylib.h>
#include <math.h>

#define __POKEROK_IMPLEMENTATION
#include <pokerok.h>

int main () {
  Deck *d = createDeck(d);
  Rules rules;

  rules.fontSize = 20;
  rules.screenWidth = 800;
  rules.screenHeight = 600;
  rules.cardWidth = 40;
  rules.cardHeight = 60;

  InitWindow(rules.screenWidth, rules.screenHeight, "POKEROK");
  SetTargetFPS(60);


  while(!WindowShouldClose()) {
    BeginDrawing();
      ClearBackground((Color){220,220,220,255});
      for (int s = 0; s < oN_SUITS; s++) {
        for (int r = 0; r < oN_RATING; r++) {
          drawCardAt(&rules, &d->cards[2 + s * oN_RATING + r], (Vector2){10 + r * (rules.cardWidth + 10), 10 + s * (rules.cardHeight + 10)});
        }
      }
      drawCardAt(&rules, &d->cards[0], (Vector2){10, 300});
      drawCardAt(&rules, &d->cards[1], (Vector2){20 + rules.cardWidth, 300});
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
