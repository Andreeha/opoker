#ifndef __POKEROK_H
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define oHEARTS   0x01
#define oDIAMONDS 0x11
#define oSPADES   0x00
#define oCLUBS    0x10
#define oN_SUITS  4
#define oBLACK    0x00
#define oRED      0x01

#define o2  0
#define o3  1
#define o4  2
#define o5  3
#define o6  4
#define o7  5
#define o8  6
#define o9  7
#define o10 8
#define oJ  9
#define oQ  10
#define oK  11
#define oA  12
#define oN_RATING 13
#define oJACK 14

#define oN_CARDS (oN_SUITS * oN_RATING + 2)

typedef struct {
  int suit;
  int rating;
  char* s;
} Card;

typedef struct {
  Card* cards;
  int* shuffle;
} Deck;

typedef struct {
  void *rule;
} Round;

typedef struct {
  Card* cards;
} Player;

typedef struct {
  int fontSize;
  int screenWidth;
  int screenHeight;
  int cardWidth;
  int cardHeight;

  int nPlayers;
  Player *players;
  int *playerScores;

  int round;
} Rules;


Deck* createDeck();
Color cardColor(Card *c);
const char* ratingToChar(Card *c);
char suitToChar(Card *c);

void shuffleDeck(Deck *d);

int numberOfDeals(Rules *r);
const char* currentDeal(Rules *r, int iDeal);

// visual
void drawCardAt(Rules *r, Card* c, Vector2 p);

#endif // __POKEROK_H

#ifdef __POKEROK_IMPLEMENTATION

Deck* createDeck() {
  srand(time(NULL));
  char str[64];
  Deck* d = malloc(sizeof(Deck));
  d->cards = malloc(sizeof(Card) * oN_CARDS);
  d->cards[0].suit   = oRED;
  d->cards[0].rating = oJACK;
  d->cards[0].s = malloc(64 * sizeof(char));
  sprintf(str, "%s", ratingToChar(&d->cards[0]));
  strcpy(d->cards[0].s, str);
  d->cards[1].suit   = oBLACK;
  d->cards[1].rating = oJACK;
  d->cards[1].s = malloc(64 * sizeof(char));
  sprintf(str, "%s", ratingToChar(&d->cards[1]));
  strcpy(d->cards[1].s, str);
  for (int s = 0; s < oN_SUITS; s++) {
    for (int r = 0; r < oN_RATING; r++) {
      int i = 2 + s * oN_RATING + r;
      d->cards[i].suit = s;
      d->cards[i].rating = r;
      d->cards[i].s = malloc(64 * sizeof(char));

      sprintf(str, "%s", ratingToChar(&d->cards[i]));
      strcpy(d->cards[i].s, str);
    }
  }
  return d;
}

void shuffleDeck(Deck *d) {
  if (!d->shuffle) {
    d->shuffle = malloc(oN_CARDS * sizeof(int));
  }
  for (int i = 0; i < oN_CARDS; i++) {
    int nu_i = rand() % (oN_CARDS - i);
    for (int j = 0, nu_j = -1; j < oN_CARDS; j++) {
      int used = 0;
      for (int k = 0; k < i; k++) {
        if (j == d->shuffle[k]) used = 1;
      }
      nu_j += !used;
      if (nu_j == nu_i) {
        d->shuffle[i] = j;
        break;
      }
    }
  }
}

Color cardColor(Card *c) {
  Color color[] = {BLACK, RED, YELLOW, GREEN};
  return color[c->suit];
}

const char* ratingToChar(Card *c) {
  const char* s[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","A","","Jkr"};
  return s[c->rating];
}

char suitToChar(Card *c) {
  const char* s = "SHCD";
  return s[c->suit];
}

int isHovered(Vector2 tl, Vector2 br) {
  Vector2 mp = GetMousePosition();
  return tl.x <= mp.x && tl.y <= mp.y && br.x >= mp.x && br.y >= mp.y;
}

// visual
void drawCardAt(Rules *r, Card* c, Vector2 p) {
  if (isHovered(p, (Vector2){p.x + r->cardWidth, p.y + r->cardHeight})) {
    DrawRectangleV(p, (Vector2){r->cardWidth, r->cardHeight}, PINK);
  }
  DrawLineV(p, (Vector2){p.x + r->cardWidth, p.y}, BLACK);
  DrawLineV(p, (Vector2){p.x, p.y + r->cardHeight}, BLACK);
  DrawLineV((Vector2){p.x + r->cardWidth, p.y + r->cardHeight}, (Vector2){p.x + r->cardWidth, p.y}, BLACK);
  DrawLineV((Vector2){p.x + r->cardWidth, p.y + r->cardHeight}, (Vector2){p.x, p.y + r->cardHeight}, BLACK);
  int x = p.x + (r->cardWidth - MeasureText(c->s, r->fontSize)) / 2;
  int y = p.y + (r->cardHeight - r->fontSize) / 2;
  DrawText(c->s, x, y, r->fontSize, cardColor(c));
}

int numberOfDeals(Rules *r) {
  return 8 + (r->nPlayers + 1) + 8 + 4;
}

const char* currentDeal(Rules *r, int iDeal) {
  const char* d[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
  const char* s[] = {"no trump", "blind", "dog-poor", "golden"};
  if (iDeal < 8) return d[iDeal];
  if (iDeal < 8 + r->nPlayers + 1) return d[8];
  if (iDeal < 8 + r->nPlayers + 1 + 8) return d[(8 + r->nPlayers + 1 + 8 - iDeal - 1)];
  if (iDeal < 8 + r->nPlayers + 1 + 8 + 4) return s[iDeal - (8 + r->nPlayers + 1 + 8)];
  return "no such deal";
}

#endif // __POKEROK_IMPLEMENTATION
