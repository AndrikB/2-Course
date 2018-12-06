#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "operators.h"
#include "smb_win.h"
#include <QThread>
#include <QScrollBar>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QVector<card> deck_of_cards, player_cards, bot_cards;
    QVector<std::pair<card, card>> pair_cards;

    bool game_is_go_on=false;
    card trump_card;//cosr card
    suit_cards trump;//cosir
    bool the_player_s_turn_is_now; //who's turn is now
    bool bot_said_i_take; //bot will take cards
    bool player_said_i_take;
    bool was_rubbish; //if was rubbish in game

    QVector<card> deck_of_all_card_for_bot;//which can be in player
    QVector<card> deck_of_card_which_is_in_player_for_bot;//card can be jocker(

    void shufle_cards();

    void game();
    void bot_turn_to_beat();
    bool can_be_beaten_for_bot(card );
    bool bot_can_put_card_for_attack(card );
    bool bot_turn_to_attack();
    void add_card_to_player();
    double value_of_card(card);
    double current_situation();
    void drop(int );
private slots:
    void start_game();
    void on_drop_card_clicked();
    void all_write();
    void check();
    void you_win();
    void you_lose();
    void on_pas_clicked();

private:
    void sort(QVector<card> &c);
    Ui::MainWindow *ui;
    QTimer *timer;
    smb_win *win=new smb_win;
};

#endif // MAINWINDOW_H
