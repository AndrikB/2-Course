#include <gtest/gtest.h>

#include <QApplication>
#include <QTextCodec>

#include <mainwindow.h>

const QString first_name="tmp1.tmp";
const QString second_name="tmp2.tmp";
const int count_repeats=15;

TEST(TestCaseName, TestName) {

    for (int z=0;z<count_repeats;z++) {

        int text_size=abs(rand());
        qDebug()<<text_size;
        QString text;
        //text="qwertyuiopoihgfdsxcvbnjgrrrrrgrvcwxwww,o";
        for (int i=0;i<text_size;i++) {
            text+=static_cast<char>(rand()%255);

        }


        QFile f1(first_name);
        f1.open(QIODevice::WriteOnly);
        QTextStream out(&f1);
        out<<text;
        f1.close();

        int key_size=20;
        unsigned char *str = new unsigned char [static_cast<unsigned long long>(key_size)];
        RAND_bytes(str, key_size);

        EncryptSymmetric *enc=new EncryptSymmetric;
        enc->close();
        BF_set_key(enc->key, key_size, str);
        enc->last_name=first_name;
        enc->new_name=second_name;
        enc->on_convert_clicked();
        enc->on_exit_clicked();

        QFile::remove(first_name);


        DecryptSymmetric *dec=new DecryptSymmetric;
        dec->close();
        BF_set_key(dec->key, key_size, str);
        dec->last_name=second_name;
        dec->new_name=first_name;
        dec->on_convert_clicked();
        dec->on_exit_clicked();

        QString new_text;
        f1.open(QIODevice::ReadOnly);
        QTextStream in(&f1);
        char * new_text_c=new char[f1.size()];
        f1.read(new_text_c, f1.size());
        new_text=QString::fromUtf8(new_text_c, f1.size());
        //qDebug()<<"\n"<<text_size<<text<<"\n"<<new_text.size()<<new_text;

        EXPECT_EQ(new_text, text);
    }
}

int main(int argc,char*argv[])
{
    srand (time(0));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
