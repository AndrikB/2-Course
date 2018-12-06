#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

//convert card value and suit to qstring
QString card_to_qstring(card card)
{
    QString s="";
    if (card.value!=0) s=string_value[card.value]+' '+string_suit[card.suit];
    return s;
}

double MainWindow::value_of_card(card card)
{
    double is_smaller=0;
    if (card.suit==trump)
    {
        is_smaller+=9*3+card.value-6;
    }
    else
    {
        is_smaller+=card.value-6;
    }


    return is_smaller;//max 36
}

double MainWindow::current_situation()
{
    if (!the_player_s_turn_is_now)
    {
        if (player_said_i_take)//you take
        {
            return (24-deck_of_cards.size())*1.5;
        }
        else//you beat
        {
            return (28-deck_of_cards.size())*1.5;//this may be not 28. calibrate it
        }
    }
    else//bot beat
    {
        return (40-deck_of_cards.size())*1.5;//this may be not 32. calibrate it
    }

    //return 0;
}

void MainWindow::drop(int )
{
    this->on_drop_card_clicked();
}


MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(all_write()));
    connect(this->win, SIGNAL(start()), this, SLOT(start_game()));
    connect(this->ui->player_cards, SIGNAL(itemDoubleClicked(QListWidgetItem *)), this, SLOT(on_drop_card_clicked()));
    this->start_game();
}


MainWindow::~MainWindow()
{
    delete ui;
}


//return true, if card is in QVector<card>
bool is_card_in_QVector(QVector<card> vec, card card)
{
    int size=vec.size();
    for (int i=0;i<size;i++)
    {
        if (vec[i]==card) return true;
    }
    return false;
}

void MainWindow::sort(QVector<card> &cards)
{
    int size=cards.size();
    //sort for suit(trump==max)
    for (int i=0;i<size;i++)
    {
        for (int j=i+1;j<size;j++)
        {

            if ((cards[i].suit<cards[j].suit&&cards[i].suit!=trump)||cards[j].suit==trump)
            {
                card tmp=cards[i];
                cards[i]=cards[j];
                cards[j]=tmp;
            }

        }
    }
    //sort for value(not swap if not same suit)
    for(int i=0;i<size;i++)
    {
        for (int j=i+1;j<size;j++)
        {
            if (cards[i]<cards[j])
            {
                card tmp=cards[i];
                cards[i]=cards[j];
                cards[j]=tmp;
            }

        }
    }


}


//return color of card
QColor card_color(card card)
{
    if (card.suit==diamonds||card.suit==hearts)return Qt::red;
    return Qt::black;
}

void MainWindow::all_write()
{
    //deck of card
    {
        ui->deck_of_cards->clear();
        if (card_color(trump_card)==Qt::red)
            ui->trump->setStyleSheet("QLabel { color : red; }");
        else
            ui->trump->setStyleSheet("QLabel { color : dark; }");
        if (deck_of_cards.isEmpty())
        {
            ui->trump->setText(string_suit[trump]);
        }
        else
        {
            ui->trump->setText(card_to_qstring(trump_card));
            ui->deck_of_cards->setText(QString::number(deck_of_cards.size()));
        }
    }

    //qlabel 'bot said'
    {
        if (the_player_s_turn_is_now)
        {
            if (bot_said_i_take)
            {
                ui->bot_said->setText("Bot said: I take");
            }
            else
            {
                ui->bot_said->setText("Drop card");
            }
        }
        else
        {
            ui->bot_said->setText("Drop card or take");

        }

    }

    //player cards
    {
        int cur=ui->player_cards->currentRow();
        QScrollBar *vb = ui->player_cards->verticalScrollBar();
        int oldValue = vb->value();
        ui->player_cards->clear();
        int size_player_cards=player_cards.size();
        for(int i=0;i<size_player_cards;i++)
        {
            ui->player_cards->addItem(card_to_qstring(player_cards[i]));
            ui->player_cards->item(i)->setForeground(card_color(player_cards[i]));
        }
        ui->player_cards->setCurrentRow(cur);
        vb->setValue(oldValue);

    }

    //game space
    {
        ui->game_space1->clear();
        ui->game_space2->clear();
        int size=pair_cards.size();
        for (int i=0;i<size;i++)
        {
            ui->game_space1->addItem(card_to_qstring(pair_cards[i].first));
            ui->game_space1->item(i)->setForeground(card_color(pair_cards[i].first));
            //qDebug()<<card_to_qstring(pair_cards[i].first)<<card_to_qstring(pair_cards[i].second);
            if(!!pair_cards[i].second)
            {
                ui->game_space2->addItem(card_to_qstring(pair_cards[i].second));
                ui->game_space2->item(i)->setForeground(card_color(pair_cards[i].second));
            }
        }
    }

    //bot cards
    {
        ui->bot_cards->clear();
        int size_bot_cards=bot_cards.size();
        //if (!game_is_go_on)
            for(int i=0;i<size_bot_cards;i++)
            {
                if (0)
                {
                    ui->bot_cards->addItem(card_to_qstring(bot_cards[i]));
                    ui->bot_cards->item(i)->setForeground(card_color(bot_cards[i]));
                }
                else
                {
                    ui->bot_cards->addItem("***");
                }
            }
    }

    //buttons

    //drop card
    {
        bool b=false;
        if (the_player_s_turn_is_now)//if your turn
        {
            //if is current card in pair_cards
            card current_card=player_cards[ui->player_cards->currentRow()];
            int size_pair=pair_cards.size();

            if (size_pair==0)b=true;;
            for (int i=0;i<size_pair;i++)
            {
                if (current_card.value==pair_cards[i].first.value||current_card.value==pair_cards[i].second.value) //if you can drop card
                {
                    b=true;
                    i=size_pair;
                }
            }
            if (pair_cards.size()>=6-was_rubbish) b=false;
            if (bot_cards.isEmpty()) b=false;
            if (!ui->player_cards->currentItem()) b=false;
        }
        else//if bot turn
        {
            card current_card=player_cards[ui->player_cards->currentRow()];
            card card_need_to_be_beaten=pair_cards[pair_cards.size()-1].first;
            if (current_card>card_need_to_be_beaten)//suits same and your card>his card
               b=true;
            if (current_card.suit==trump&&card_need_to_be_beaten.suit!=trump)
               b=true;

        }
        if (!ui->player_cards->currentItem())b=false;
        if (!game_is_go_on)b=false;
        ui->drop_card->setVisible(b);

    }

    //pas card
    {
        ui->pas->setVisible(game_is_go_on);
        if (the_player_s_turn_is_now)
        {
            if (pair_cards.isEmpty())
            {
                ui->pas->setVisible(false);
            }
            else if (!!pair_cards[pair_cards.size()-1].second)//both card is there.
            {
                ui->pas->setText("Pas");
            }
            else if (bot_said_i_take)//if bot said (I take)
            {
                ui->pas->setText("Pas");
            }
            else  // if it dont said (I take)
            {
               ui->pas->setVisible(false);
            }

        }
        else//bot turn now
        {
            ui->pas->setText("Take");
        }

    }

    //check();

}

void MainWindow::you_win()
{
    game_is_go_on=false;
    timer->stop();
    this->close();
    win->win(true);

}

void MainWindow::you_lose()
{
    game_is_go_on=false;
    timer->stop();
    this->close();
    win->win(false);

}

void MainWindow::check()
{
    if(!deck_of_cards.isEmpty()) return;
    if(player_cards.isEmpty())
        you_win();
    if(bot_cards.isEmpty())
        you_lose();

}

//return true if player have to turn first; else - false
bool player_turn_first(QVector<card> player, QVector<card> bot, suit_cards trump)
{
    //if min trump is in
    for (card tmp(2, trump); tmp.value<15;tmp.value++)//from {2, trump} to {A, trump}
    {
        if(is_card_in_QVector(player, tmp)) return true;
        if(is_card_in_QVector(bot, tmp)) return false;
    }
    return false;//whu not?
}

void MainWindow::shufle_cards()
{
    int k=36;
    bot_said_i_take=false;
    player_said_i_take=false;
    was_rubbish=false;

    deck_of_all_card_for_bot.clear();//array of all cards for bot (memmory. which dont appeared)
    pair_cards.clear();

    //clear last vector of cards
    deck_of_cards.clear();
    bot_cards.clear();
    player_cards.clear();

    //create tmp vector of ALL cards
    QVector<card> tmp_cards;
    for (int i=0;i<k;i++)
    {
        card tmp(i%(k/4)+6,(suit_cards)(i/(k/4)));
        tmp_cards.push_back(tmp);
        deck_of_all_card_for_bot.push_back(tmp);
    }

    //create new vector of cards
    for (int i=0;i<k;i++)
    {
        int z=rand()%(k-i);
        deck_of_cards.push_back(tmp_cards[z]);
        tmp_cards.erase(tmp_cards.begin()+z);
        QString s=string_value[deck_of_cards[i].value]+' '+string_suit[deck_of_cards[i].suit];
        qDebug()<<i<<" :"<<s;
        ui->player_cards->addItem(s);
    }
}

void MainWindow::add_card_to_player()
{
    if (pair_cards.isEmpty())
    {
        //if smbd have not all cards
        if (!deck_of_cards.isEmpty())//if not all cards from deck were pull out
        {
            if (the_player_s_turn_is_now)//so, if it is time to player turn, he will pull cards first
                while (!deck_of_cards.isEmpty() && player_cards.size()<6)
                {
                    player_cards.push_back(deck_of_cards[0]);deck_of_cards.erase(deck_of_cards.begin());//pull one card to player
                }
            while (!deck_of_cards.isEmpty() && bot_cards.size()<6)
            {
                bot_cards.push_back(deck_of_cards[0]);deck_of_cards.erase(deck_of_cards.begin());// -//- to bot
            }
            while (!deck_of_cards.isEmpty() && player_cards.size()<6)
            {
                player_cards.push_back(deck_of_cards[0]);deck_of_cards.erase(deck_of_cards.begin());//pull one card to player
            }
        }
        sort(player_cards);
        sort(bot_cards);
    }
}

void MainWindow::game()
{
    //the game
    while (game_is_go_on)
    {
        qDebug()<<"the_player_s_turn_is_now"<<the_player_s_turn_is_now;
        add_card_to_player();//add card to bot and player
        if(player_cards.isEmpty())
        {
            check();
            game_is_go_on=false;
            return;
        }
        if (bot_cards.isEmpty())
        {
            check();
            game_is_go_on=false;
            return;
        }

        if (the_player_s_turn_is_now) return;//wait for player start

        if (bot_turn_to_attack())
        {
            //wait for player push smth
            return;
        }
        else
        {
            the_player_s_turn_is_now=true;
            //clear_space
            pair_cards.clear();
        }


    }
    //end game
    //smbd win(mb)

}

void MainWindow::start_game()
{
    this->show();
    timer->start(15);
    shufle_cards();//first of all wi have to shufle cards

    game_is_go_on=true;
    //pull cards to player and bot
    for(int i=0;i<6;i++)
    {
        player_cards.push_back(deck_of_cards[0]);deck_of_cards.erase(deck_of_cards.begin());//pull 1 card to player
        bot_cards.push_back(deck_of_cards[0]);deck_of_cards.erase(deck_of_cards.begin());// -//- to bot
    }

    trump_card=*deck_of_cards.end(); //for visible in deck
    trump=trump_card.suit;
    qDebug()<<"TRUMP"<<trump;
    //set who will turn first
    the_player_s_turn_is_now =player_turn_first(player_cards, bot_cards, trump);
    game();

}

void MainWindow::on_drop_card_clicked()//it is for your and bot turn
{
    card current_card=player_cards[ui->player_cards->currentRow()];
    if (the_player_s_turn_is_now)
    {
        std::pair<card, card> pair;
        pair.first=current_card;
        pair.second=card();
        player_cards.erase(ui->player_cards->currentRow()+player_cards.begin());
        pair_cards.push_back(pair);
        qDebug()<<card_to_qstring(pair.first);
        if (!bot_said_i_take)bot_turn_to_beat();//bot turn
    }
    else
    {
        pair_cards[pair_cards.size()-1].second=current_card;
        player_cards.erase(ui->player_cards->currentRow()+player_cards.begin());
        game();
    }

    all_write();

}

void MainWindow::on_pas_clicked()
{
    if (the_player_s_turn_is_now)//if your turn
    {
        if (!!pair_cards[pair_cards.size()-1].second)//if in last pair is both card(bot beat all card) and cards go to rubbish
        {
            //delete cards from vector with all cards for bot
            pair_cards.clear();
            the_player_s_turn_is_now=false;
        }
        else//if bot take away cards
        {
            while (!pair_cards.isEmpty())
            {
                bot_cards.push_back(pair_cards[0].first);
                if (!!pair_cards[0].second)//if is second card
                    bot_cards.push_back(pair_cards[0].second);
                pair_cards.erase(pair_cards.begin());
            }
            bot_said_i_take=false;
        }
    }
    else //if bot turn
    {
        qDebug()<<"take";
        player_said_i_take=true;
        while(bot_turn_to_attack()) {}
        while (!pair_cards.isEmpty())//TAKE ALL
        {
            player_cards.push_back(pair_cards[0].first);
            if (!!pair_cards[0].second)//if is second card
                player_cards.push_back(pair_cards[0].second);
            pair_cards.erase(pair_cards.begin());
        }

    }
    qDebug()<<2<<the_player_s_turn_is_now;
    game();

}

bool MainWindow::can_be_beaten_for_bot(card card_need_to_be_beaten)
{
    int size_card=bot_cards.size();
    double cur_sit=current_situation();
    for (int i=0;i<size_card;i++)
    {
        if (value_of_card(bot_cards[i])>cur_sit) continue;
        if (bot_cards[i]>card_need_to_be_beaten)
            return true;
        if (bot_cards[i].suit==trump&&card_need_to_be_beaten.suit!=trump)
            return true;
    }
    return false;
}

void MainWindow::bot_turn_to_beat()//or said "I take"
{
    int size_card=bot_cards.size();
    card card_need_to_be_beaten=pair_cards[pair_cards.size()-1].first;

    if (!can_be_beaten_for_bot(card_need_to_be_beaten))
    {
        bot_said_i_take=true;
        return;
    }
    double cur_sit=current_situation();
    QVector<int> index_cards_can_beat;
    int count_cards_which_is_bigger=0;
    //create qvector of cards whitch can beat your card
    for (int i=0;i<size_card;i++)
    {
        qDebug()<<value_of_card(bot_cards[i])<<card_to_qstring(bot_cards[i])<<cur_sit;
        if (value_of_card(bot_cards[i])>cur_sit) continue;

        if (bot_cards[i]>card_need_to_be_beaten)
        {
            index_cards_can_beat.push_back(i);
            count_cards_which_is_bigger++;
            qDebug()<<i;
        }
        else if (bot_cards[i].suit==trump&&card_need_to_be_beaten.suit!=trump)
        {
            index_cards_can_beat.push_back(i);
            count_cards_which_is_bigger++;
            qDebug()<<i;
        }
    }
    qDebug()<<111111111;
    for (int i=0;i<count_cards_which_is_bigger;i++)
        qDebug()<<card_to_qstring(bot_cards[index_cards_can_beat[i]]);

    for (int i=count_cards_which_is_bigger-1;i>0;i--)
    {
        //if bot can beat not trump card
        if (bot_cards[index_cards_can_beat[count_cards_which_is_bigger-1]].suit!=trump)
            if (bot_cards[index_cards_can_beat[i]].suit==trump) continue;

        int pair_size=pair_cards.size();
        for (int j=0;j<pair_size;j++)
        {
            //if card witn same value is in pair cards
            if (pair_cards[j].first.value==bot_cards[index_cards_can_beat[i]].value&&bot_cards[index_cards_can_beat[i]].suit!=trump)
            {
                pair_cards[pair_cards.size()-1].second=bot_cards[index_cards_can_beat[i]];
                bot_cards.erase(bot_cards.begin()+index_cards_can_beat[i]);
                return;
            }

            if (!!pair_cards[j].second)
            {
                if (pair_cards[j].second.value==bot_cards[index_cards_can_beat[i]].value&&bot_cards[index_cards_can_beat[i]].suit!=trump)
                {
                    pair_cards[pair_cards.size()-1].second=bot_cards[index_cards_can_beat[i]];
                    bot_cards.erase(bot_cards.begin()+index_cards_can_beat[i]);
                    return;
                }
            }

        }

    }


    pair_cards[pair_cards.size()-1].second=bot_cards[index_cards_can_beat[index_cards_can_beat.size()-1]];//last card of all them push
    qDebug()<<"both card"<<card_to_qstring(pair_cards[pair_cards.size()-1].first)<<card_to_qstring(pair_cards[pair_cards.size()-1].second);
    bot_cards.erase(bot_cards.begin()+index_cards_can_beat[index_cards_can_beat.size()-1]);


}

bool MainWindow::bot_can_put_card_for_attack(card card)
{
    if (pair_cards.isEmpty()) return true;
    int size=pair_cards.size();
    for (int i=0;i<size;i++)
    {
        if (pair_cards[i].first.value==card.value) return true;
        if (!!pair_cards[i].second)
        {
            if (pair_cards[i].second.value==card.value) return true;
        }
    }
    return false;
}

//return true - push card
bool MainWindow::bot_turn_to_attack()
{
    if (bot_cards.isEmpty())return false;
    if (player_cards.isEmpty())return false;
    if (pair_cards.size()==5+was_rubbish) return false;
    int count_cards=bot_cards.size();
    int index_min_card=0;
    double cur_sit=current_situation();
    for (int i=1;i<count_cards;i++)//create array of index start subaray of card(for suit)
    {
        if (bot_cards[i].value<bot_cards[index_min_card].value||(bot_cards[i].suit!=trump && bot_cards[index_min_card].suit==trump))
            if (cur_sit>value_of_card(bot_cards[i])&&bot_can_put_card_for_attack(bot_cards[i]))
            {
                index_min_card=i;
            }
    }

    if (bot_can_put_card_for_attack(bot_cards[index_min_card])&&(cur_sit>value_of_card(bot_cards[index_min_card])||pair_cards.isEmpty()))
    {
        std::pair<card, card> pair;
        pair.first=bot_cards[index_min_card];
        pair.second=card();
        bot_cards.erase(index_min_card+bot_cards.begin());
        pair_cards.push_back(pair);
        qDebug()<<card_to_qstring(pair.first);
        return true;
    }
    qDebug()<<"bot not put";
    return false;


}
