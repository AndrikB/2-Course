#ifndef OPERATORS_H
#define OPERATORS_H
#include <stdlib.h>
#include <QDebug>
#include <time.h>
enum suit_cards
{
    diamonds,//♦
    clubs,//♣
    hearts,//♥
    spades,//♠
    jocker//for bot, if he dont know this card in your hand
};

struct card
{
   int value;
   suit_cards suit;
   card(int v=0, suit_cards su=diamonds):value(v), suit(su){}
};


const QString string_suit[] ={"♦", "♣","♥","♠", };

const QString string_value[]={" error0",
                              " jocker",
                              " 2",
                              " 3",
                              " 4",
                              " 5",
                              " 6",
                              " 7",
                              " 8",
                              " 9",
                              "10",
                              " J",
                              " Q",
                              " K",
                              " A"
};

inline bool operator ==(const card& a, const card& b)
{
    return (a.suit==b.suit && a.value==b.value);

}

//return true, if a may beat b
inline bool operator >(const card& a, const card& b)
{
    return (a.suit==b.suit && a.value>b.value);
}

inline bool operator <(const card& a, const card& b)
{
    return (a.suit==b.suit && a.value<b.value);

}

inline bool operator !(const card a)
{
    return (a.value==0);
}

#endif // OPERATORS_H
