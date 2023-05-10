#include<iostream>
#include<conio.h>
#include<fstream>
#include<unistd.h>
#include<sstream>
#include<limits>
#include<windows.h>
#include<cstdlib>
#include<ctime>
#include<bits/stdc++.h>
using namespace std;

#define KEY_UP    72
#define KEY_DOWN  80

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void space(){
    cout<<"                    ";
}

class User{
public:
    string name,password;
    int highscore,level;
    string highscorename[11];
    int bestscore=0, totalhighscoresno, gamehighscore[11];
    int oldline=-1;
    //--------------------------------------------------------Welcome--------------------------------------------------------
    void welcome()
    {
        level=2;
        int passwordfail=0;
        int status =0, score;
        string line;
        string username, pass;
        system("CLS");
        space();
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"****************** Welcome to TypeRacer Game ******************\n";
        cout<<"\n\n\n";
        int usernamespace=0;
        do{
            usernamespace=0;
            space();
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"Enter Username: ";
            getline(cin, name);
            if(name.length()==0){
                space();
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Username can't be blank.\n\n";
                SetConsoleTextAttribute(hConsole, 10);
                continue;
            }
            for(int i=0; i<name.length(); i++)
            {
                if(name[i]==' '){
                    usernamespace=1;
                }
            }
            if(usernamespace==1){
                space();
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Username can't contain space.\n\n";
                SetConsoleTextAttribute(hConsole, 10);
                continue;
            }

            if(name.length()>20){
                space();
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Username can't be more than 20 characters.\n\n";
                SetConsoleTextAttribute(hConsole, 10);
                continue;
            }
            break;
        }while(name.length()>20 | usernamespace==1 | name.length()==0);
        fstream userdata("userdata.txt",ios::in);
        userdata.seekg(0, ios::beg);
        while(userdata>>username>>pass>>score){
            if(username == name){
                highscore=score;
                status = 1;
                userdata.close();
                break;
            }
        }
        if(status==1){
            do{
                int i=0;
                char dotpass[100];
                space();
                cout<<"Enter Password: ";
                while((dotpass[i]=getch())!='\r'){
                    if(int(dotpass[i])==8)
                    {
                        if(i==0){
                            continue;
                        }
                        cout<<char(8);
                        cout<<" ";
                        cout<<char(8);
                        password.erase(password.end()-1);
                        i--;
                        continue;
                    }
                    cout<<"*";
                    i++;
                    dotpass[i]='\0';
                    password = dotpass;
                }
                if(password==pass){
                    system("CLS");
                    cout<<endl;
                    cout<<endl;
                    space();
                    space();
                    cout<<"Welcome back "<<name<<"!";
                    sleep(1);
                    break;
                }
                else{
                    cout<<endl;
                    space();
                    SetConsoleTextAttribute(hConsole, 12);
                    cout<<"Invalid password!\n\n";
                    SetConsoleTextAttribute(hConsole, 10);
                    passwordfail++;
                    if(passwordfail==5){
                        space();
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"You have entered password wrong for 5 times.\n\n";
                        SetConsoleTextAttribute(hConsole, 10);
                        sleep(2);
                        this->welcome();
                    }
                }
            }while(true);
        }
        else{
            userdata.close();
            userdata.open("userdata.txt", ios::app);
            do{
                int i=0;
                char dotpass[100];
                space();
                cout<<"Create a new Password: ";
                while((dotpass[i]=getch())!='\r'){
                    if(int(dotpass[i])==8)
                    {
                        if(i==0){
                            continue;
                        }
                        cout<<char(8);
                        cout<<" ";
                        cout<<char(8);
                        i--;
                        continue;
                    }
                    cout<<"*";
                    i++;
                    dotpass[i]='\0';
                    password = dotpass;
                }
                if(i==0){
                    char dotpass[100];
                    password="";
                }
                int spacecheck=0;
                for(int j=0; j<password.length(); j++)
                {
                    if(password[j]==' '){
                        cout<<endl;
                        space();
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"Password can't contain space.\n\n";
                        SetConsoleTextAttribute(hConsole, 10);
                        spacecheck=1;
                        break;
                    }
                }

                if(password.length()>10)
                {
                    cout<<endl;
                    space();
                    SetConsoleTextAttribute(hConsole, 12);
                    cout<<"Password can't be more that 10 characters.\n\n";
                    SetConsoleTextAttribute(hConsole, 10);
                }

                if(spacecheck==1){
                    password="password with space";
                }

                if(password.length()==0){
                    cout<<endl;
                    space();
                    SetConsoleTextAttribute(hConsole, 12);
                    cout<<"Password can't be blank.\n\n";
                    SetConsoleTextAttribute(hConsole, 10);
                }
            }while(password.length()>10 | password.length()==0);
            highscore=0;
            userdata<<name<<" "<<password<<" "<<"0"<<endl;
            userdata.close();
            system("CLS");
            cout<<endl<<endl;
            space();
            space();
            cout<<"    Welcome "<<name<<"!";
            cout<<endl;
            space();
            cout<<"          Your id has been created successfully.";
            sleep(2);
        }

        //-----------------------------------------------highscore list------------------------------------------------------

        fstream highscores("highscores.txt", ios::in);
        totalhighscoresno=0;
        while(highscores>>highscorename[totalhighscoresno]>>gamehighscore[totalhighscoresno]){
            if(gamehighscore[totalhighscoresno]>bestscore){
                bestscore=gamehighscore[totalhighscoresno];
            }
            totalhighscoresno++;
        }
        highscores.close();

        //------------------------------------------------ end highscore list ----------------------------------------------
    }
    //--------------------------------------------------------end Welcome--------------------------------------------------------

    //--------------------------------------------------------game--------------------------------------------------------



    void game(){
        //--------------------------------------------generate random sentence----------------------------------
        string sentence;
        fstream text("textfile.txt",ios::in);
        int lineno;
        int linenocheck;
        int levelcheck=0;
        while(levelcheck==0){
            srand(time(0));
            lineno=rand()%176;
            linenocheck=0;
            text.seekg(0, ios::beg);
            while(getline(text,sentence)){
                if(linenocheck==lineno){
                    switch (level) {
                        case 1:
                        if(sentence.length()<=100){
                            levelcheck=1;
                        }
                        break;
                        case 2:
                        if(sentence.length()>100 && sentence.length()<=150){
                            levelcheck=1;
                        }
                        break;
                        case 3:
                        if(sentence.length()>150){
                            levelcheck=1;
                        }
                        break;
                    }
                    if(oldline==lineno){
                        text.close();
                        this->game();
                    }
                    else{
                        break;
                    }
                }
                linenocheck++;
            }
        }
        oldline=lineno;
        text.close();
        //----------------------------------------end random------------------------------------------------------

        //------------------------------------------Start countdown ---------------------------------------------

        for(int i=0;i<3;i++){
            system("CLS");
            space();
            cout<<"**************** Let's Check Your Typing Speed *****************\n\n";
            space();
            space();
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"           "<<3-i;
            SetConsoleTextAttribute(hConsole, 3);
            sleep(1);
        }
        system("CLS");
        space();
        cout<<"**************** Let's Check Your Typing Speed *****************\n\n";
        space();
        space();
        SetConsoleTextAttribute(hConsole, 10);
        cout<<"          GO";
        SetConsoleTextAttribute(hConsole, 3);
        sleep(1);

        //----------------------------------------end start countdown--------------------------------------------
        int oldhighscore=highscore, oldbestscore=bestscore;
        int right=0, cursorpos=0, rightcheck=0;
        int errors=0;
        string typedtext,wrongtext, currenttext;
        char typedchar;
        int redline=0;
        int sentence_length=sentence.length();
        int started = 0;
        int time_taken=0;
        float speed=0;
        int starttime=time(0);
        while(true){
            system("CLS");
            space();
            cout<<"**************** Let's Check Your Typing Speed *****************\n\n";
            space();
            cout<<"                     Game Highscore: ";
            SetConsoleTextAttribute(hConsole, 10);
            for(int i=0; i<3-to_string(bestscore).length(); i++){
                cout<<" ";
            }
            cout<<bestscore;
            cout<<" Wpm";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<endl<<endl;
            space();
            cout<<"User: ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<name;
            SetConsoleTextAttribute(hConsole, 3);
            for(int k=0; k<64-26-name.length()-3; k++)
            {
                cout<<" ";
            }
            cout<<"Your Highscore: ";
            SetConsoleTextAttribute(hConsole, 10);
            for(int i=0; i<3-to_string(highscore).length(); i++){
                cout<<" ";
            }
            cout<<highscore;
            cout<<" Wpm";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<endl<<endl;

            //---------------------------------------------progress bar--------------------------------------------

            space();
            float onebar=float(sentence_length)/64;
            float totalprogress=float(redline)/onebar;
            if(totalprogress>62)
            {
                totalprogress=62;
            }
            SetConsoleTextAttribute(hConsole, 650);
            if(typedtext==sentence){
                SetConsoleTextAttribute(hConsole, 301);
            }
            cout<<" ";
            SetConsoleTextAttribute(hConsole, 3);
            for(int i=0; i<int(totalprogress); i++)
            {
                SetConsoleTextAttribute(hConsole, 301);
                cout<<" ";
                SetConsoleTextAttribute(hConsole, 3);
            }
            for(int i=totalprogress; i<62; i++)
            {
                SetConsoleTextAttribute(hConsole, 0);
                cout<<" ";
                SetConsoleTextAttribute(hConsole, 3);
            }
            SetConsoleTextAttribute(hConsole, 650);
            if(typedtext==sentence){
                SetConsoleTextAttribute(hConsole, 301);
            }
            cout<<" ";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<endl<<endl;

            //--------------------------------------------end progressbar------------------------------------------

            //---------------------------------------------Time and speed ------------------------------------------


            space();
            cout<<"Time: ";
            SetConsoleTextAttribute(hConsole, 14);
            cout<<time_taken;
            cout<<" s";
            SetConsoleTextAttribute(hConsole, 3);
            for(int i=0; i<42-to_string(time_taken).length(); i++){
                cout<<" ";
            }
            cout<<"Speed: ";
            SetConsoleTextAttribute(hConsole, 14);
            for(int i=0; i<3-to_string(int(speed)).length(); i++){
                cout<<" ";
            }
            cout<<int(speed);
            cout<<" Wpm";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<endl;

            //---------------------------------------------end Time and speed ------------------------------------------

            //-------------------------------------------sentence print----------------------------------------------
            int linebreak=0;
            int nextspace, lastdot;

            space();
            cout<<"----------------------------------------------------------------";
            cout<<endl;
            //------------------------------------------red words----------------------------------------------------
            for(int i=0; i<redline; i++)
            {
                if(i==0){
                    space();
                    cout<<"| ";
                }
                if(right==0){
                    SetConsoleTextAttribute(hConsole, 2);
                }
                else{
                    SetConsoleTextAttribute(hConsole, 12);
                }
                cout<<sentence[i];
                if(sentence[i]==' '){
                    int lastcheck=0;
                    for(int j=i+1; j<sentence_length; j++)
                    {
                        if(sentence[j]==' '){
                            lastcheck=1;
                            break;
                        }
                    }
                    if(lastcheck==0){
                        lastdot=sentence_length-1;
                    }
                    else{
                        lastdot=0;
                    }
                    if((lastdot+1)==sentence_length){
                        lastdot=lastdot-i;
                        if(lastdot>(60-linebreak)){
                            for(int j=0; j<(60-linebreak); j++){
                                cout<<" ";
                            }
                            SetConsoleTextAttribute(hConsole, 3);
                            cout<<"|";
                            cout<<endl;
                            linebreak=-1;
                            space();
                            cout<<"| ";
                        }
                    }
                    else{
                        nextspace=i+1;
                        while(sentence[nextspace]!=' '){
                            nextspace++;
                        }
                        nextspace=nextspace-i;
                        if(nextspace>(60-linebreak)){
                            for(int j=0; j<(60-linebreak); j++){
                                cout<<" ";
                            }
                            SetConsoleTextAttribute(hConsole, 3);
                            cout<<"|";
                            cout<<endl;
                            linebreak=-1;
                            space();
                            cout<<"| ";
                        }
                    }
                }
                linebreak++;
                if(i==(sentence_length-1)){
                    SetConsoleTextAttribute(hConsole, 3);
                    for(int j=0; j<61-linebreak; j++)
                    {
                        cout<<" ";
                    }
                    cout<<"|";
                    cout<<endl;
                }
            }
            //--------------------------------------------------------green words----------------------------------
            for(int i=redline; i<sentence_length; i++)
            {
                if(i==0){
                    space();
                    cout<<"| ";
                }
                SetConsoleTextAttribute(hConsole, 15);
                cout<<sentence[i];
                if(sentence[i]==' '){
                    int lastcheck=0;
                    for(int j=i+1; j<sentence_length; j++)
                    {
                        if(sentence[j]==' '){
                            lastcheck=1;
                            break;
                        }
                    }
                    if(lastcheck==0){
                        lastdot=sentence_length-1;
                    }
                    else{
                        lastdot=0;
                    }
                    if((lastdot+1)==sentence_length){
                        lastdot=lastdot-i;
                        if(lastdot>(60-linebreak)){
                            for(int j=0; j<(60-linebreak); j++){
                                cout<<" ";
                            }
                            SetConsoleTextAttribute(hConsole, 3);
                            cout<<"|";
                            cout<<endl;
                            linebreak=-1;
                            space();
                            cout<<"| ";
                        }
                    }
                    else{
                        nextspace=i+1;
                        while(sentence[nextspace]!=' '){
                            nextspace++;
                        }
                        nextspace=nextspace-i;
                        if(nextspace>(60-linebreak)){
                            for(int j=0; j<(60-linebreak); j++){
                                cout<<" ";
                            }
                            SetConsoleTextAttribute(hConsole, 3);
                            cout<<"|";
                            cout<<endl;
                            linebreak=-1;
                            space();
                            cout<<"| ";
                        }
                    }
                }
                linebreak++;
                if(i==(sentence_length-1)){
                    SetConsoleTextAttribute(hConsole, 3);
                    for(int j=0; j<61-linebreak; j++)
                    {
                        cout<<" ";
                    }
                    cout<<"|";
                    cout<<endl;
                }

            }
            space();
            cout<<"----------------------------------------------------------------";
            cout<<endl;

            //--------------------------------------------end sentence print-----------------------------------------

            if(typedtext == sentence){
                break;
            }
            if(typedchar=='`'){
                break;
            }

            //------------------------------------------Type box---------------------------------------------------------

            cout<<endl;
            space();
            cout<<"----------------------------------------------------------------";


            cout<<endl;
            space();
            cout<<"| ";
            if(kbhit()){
                typedchar=getch();
                if(typedchar!='\r' && typedchar!='\t' && typedchar!='`'){
                    if(rightcheck==0){
                        if(sentence[redline]==typedchar){
                            if(typedchar==' '){
                                typedtext=typedtext+typedchar;
                                currenttext="";
                                redline++;
                                cursorpos=0;
                            }
                            else{
                                typedtext=typedtext+typedchar;
                                currenttext=currenttext+typedchar;
                                redline++;
                                cursorpos++;
                            }
                        }
                        else{
                            if(int(typedchar)==8){
                                if(cursorpos!=0){
                                    typedtext.erase(typedtext.end()-1);
                                    currenttext.erase(currenttext.end()-1);
                                    redline--;
                                    cursorpos--;
                                }
                            }
                            else{
                                rightcheck=1;
                            }
                        }
                    }
                    if(rightcheck==1){
                        if(int(typedchar)==8){
                            wrongtext.erase(wrongtext.end()-1);
                            right--;
                            cursorpos--;
                            if(right==0){
                                rightcheck=0;
                            }
                        }
                        else{
                            errors++;
                            if(cursorpos!=60){
                                wrongtext=wrongtext+typedchar;
                                right++;
                                cursorpos++;
                            }
                        }
                    }
                }
            }
            SetConsoleTextAttribute(hConsole, 10);
            cout<<currenttext;
            SetConsoleTextAttribute(hConsole, 71);
            cout<<wrongtext;
            SetConsoleTextAttribute(hConsole, 3);
            for(int i=0; i<(60-currenttext.length()-wrongtext.length()); i++){
                cout<<" ";
            }
            cout<<" |";
            cout<<endl;
            space();
            cout<<"----------------------------------------------------------------";

            //----------------------------------------End type box ------------------------------------------------------

            //----------------------------------------quit option-----------------------------------------------------

            cout<<endl;
            cout<<endl;
            space();
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Press ` to quit the play..";
            SetConsoleTextAttribute(hConsole, 3);

            //----------------------------------------end quit option-------------------------------------------------


            time_taken=time(0)-starttime;
            if(typedtext.length()==0){
                speed=0;
            }
            else{
                speed=float(typedtext.length())/float(time_taken)*60/5;
            }
            if(typedtext==sentence){
                if(int(speed)>highscore){
                    highscore=int(speed);
                }
                if(int(speed)>bestscore){
                    bestscore=int(speed);
                }
            }
        }

        //----------------------------------------------Result--------------------------------------------------------

        if(typedtext==sentence){
            cout<<endl<<endl;
            space();
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Result: \n";
            space();
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"Total time taken: ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<time_taken<<" s";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<endl;
            space();
            cout<<"Typing speed: ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<int(speed)<<" Wpm";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<endl;
            space();
            cout<<"Accuracy : ";
            SetConsoleTextAttribute(hConsole, 10);
            float accuracy;
            int len=sentence.length();
            if(errors==0){
                accuracy=100;
            }
            else{
                accuracy = float(len-errors)*100/float(sentence.length());
            }
            cout<<fixed<<setprecision(2)<<accuracy<<"%";
            SetConsoleTextAttribute(hConsole, 3);
            //-------------------------------------update user highscore---------------------------------------
            if(int(speed)>oldhighscore){
                string username,pass;
                int score;
                fstream userdata("userdata.txt", ios::in);
                fstream temp("temp.dat", ios::out);
                while(userdata>>username>>pass>>score){
                    if(name==username){
                        score=highscore;
                    }
                    temp<<username<<" "<<pass<<" "<<score<<endl;
                }
                userdata.close();
                temp.close();
                userdata.open("userdata.txt", ios::out);
                temp.open("temp.dat", ios::in);
                while(temp>>username>>pass>>score){
                    userdata<<username<<" "<<pass<<" "<<score<<endl;
                }
                userdata.close();
                temp.close();
                cout<<endl;
                space();
                if(int(speed)>oldbestscore){
                    cout<<"Congratulations For Making New Game Highscore!";
                }
                else{
                    cout<<"Congratulations For Your New Highscore!";
                }
            }
            //-------------------------------------end update user highscore-----------------------------------

            //------------------------------------update game highscore------------------------------------------

            int temphighscore, temphighscoreno=totalhighscoresno;
            string temphighscorename;
            fstream highscore("highscores.txt", ios::out);
            if(totalhighscoresno==10){
                highscorename[10]=name;
                gamehighscore[10]=int(speed);
                for(int i=0; i<10; i++)
                {
                    for(int j=i+1; j<11; j++)
                    {
                        if(gamehighscore[i]<gamehighscore[j]){
                            temphighscore=gamehighscore[i];
                            temphighscorename=highscorename[i];
                            gamehighscore[i]=gamehighscore[j];
                            highscorename[i]=highscorename[j];
                            gamehighscore[j]=temphighscore;
                            highscorename[j]=temphighscorename;
                        }
                    }
                }
                for(int i=0; i<10; i++)
                {
                    highscore<<highscorename[i]<<" "<<gamehighscore[i]<<endl;
                }
                highscore.close();
            }
            else{
                highscorename[totalhighscoresno]=name;
                gamehighscore[totalhighscoresno]=int(speed);
                for(int i=0; i<totalhighscoresno; i++)
                {
                    for(int j=i+1; j<totalhighscoresno+1; j++)
                    {
                        if(gamehighscore[i]<gamehighscore[j]){
                            temphighscore=gamehighscore[i];
                            temphighscorename=highscorename[i];
                            gamehighscore[i]=gamehighscore[j];
                            highscorename[i]=highscorename[j];
                            gamehighscore[j]=temphighscore;
                            highscorename[j]=temphighscorename;
                        }
                    }
                }
                totalhighscoresno++;
                for(int i=0; i<totalhighscoresno; i++)
                {
                    highscore<<highscorename[i]<<" "<<gamehighscore[i]<<endl;
                }
                highscore.close();
            }

            //------------------------------end update game highscore--------------------------------------------
        }
        else{
            cout<<endl<<endl;
            space();
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Game left...";
            SetConsoleTextAttribute(hConsole, 3);
        }

        //-------------------------------------------End Result------------------------------------------------------

        //--------------------------------------------play again?----------------------------------------------------

        cout<<endl<<endl;
        space();
        cout<<"Do you want to play again?(";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<"y";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"/";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"n";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<")";
        char again;
        while(again=getch()){
            if(again=='y' | again=='Y'){
                this->game();
            }
            if(again=='n' | again=='N'){
                break;
            }
        }

        //------------------------------------------end play again---------------------------------------------------

    }

    //--------------------------------------------------------end game--------------------------------------------------------

    //--------------------------------------------------Highscores-------------------------------------------------------------------------

    void displayhighscores(){
        system("CLS");
        fstream highscore("highscores.txt", ios::in);
        string hname;
        int hscore;
        space();
        cout<<"************************** Highscores **************************\n\n";
        space();
        cout<<"                ";
        SetConsoleTextAttribute(hConsole, 48);
        cout<<" Name"<<"                    Speed  \n";
        SetConsoleTextAttribute(hConsole, 3);
        while(highscore>>hname>>hscore){
            space();
            cout<<"                ";
            SetConsoleTextAttribute(hConsole, 1713); //2015
            if(hname==name){
                SetConsoleTextAttribute(hConsole, 1999); //2016
            }
            cout<<" "<<hname;
            for(int i=0; i<24-hname.length(); i++)
            {
                cout<<" ";
            }
            cout<<hscore<<" Wpm "<<endl;
            SetConsoleTextAttribute(hConsole, 3);
        }
        highscore.close();
        cout<<endl;
        space();
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"                   Press any key to return...";
        SetConsoleTextAttribute(hConsole, 3);
        getch();
    }

    //----------------------------------------------------end highscores-----------------------------------------------------------------

    //---------------------------------------------------change level---------------------------------------------------------------------

    void changelevel(){
        int nav,key;
        do{
            system("CLS");
            space();
            cout<<"************************* Change Level *************************\n";
            cout<<endl<<endl;
            space();
            space();
            cout<<"        ";
            if(level==1){
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"> ";
            }
            else{
                cout<<" ";
            }
            cout<<"Easy\n";
            SetConsoleTextAttribute(hConsole, 3);
            space();
            space();
            cout<<"        ";
            if(level==2){
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"> ";
            }
            else{
                cout<<" ";
            }
            cout<<"Medium\n";
            SetConsoleTextAttribute(hConsole, 3);
            space();
            space();
            cout<<"        ";
            if(level==3){
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"> ";
            }
            else{
                cout<<" ";
            }
            cout<<"Hard\n";
            SetConsoleTextAttribute(hConsole, 3);
            nav=getch();
            if(nav==224)
            {
                key=getch();
                switch(key){
                    case KEY_UP:
                        level-=1;
                        if(level==0){
                            level=3;
                        }
                        break;
                    case KEY_DOWN:
                        level+=1;
                        if(level==4){
                            level=1;
                        }
                        break;
                    default:
                        break;
                }
            }
            if(nav==13)
            {
                switch(level)
                {
                    case 1:
                    level=1;
                    break;

                    case 2:
                    level=2;
                    break;

                    case 3:
                    level=3;
                    break;
                }
            }
        }while(nav!=13);
    }

    //--------------------------------------------------end change level------------------------------------------------------------------

    //-----------------------------------------------------------credits--------------------------------------------------------------------

    void credits(){
        for(int i=0; i<7; i++)
        {
            system("CLS");
            space();
            cout<<"*************************** Credits ****************************\n";
            for(int j=0; j<i+1; j++){
                space();
                cout<<"|                                                              |\n";
                sleep(0.3);
            }
        }
        for(int i=0; i<33;i++)
        {
            system("CLS");
            space();
            cout<<"*************************** Credits ****************************\n";
            for(int i=0; i<7; i++)
            {
                space();
                cout<<"|                                                              |\n";
            }
            space();
            for(int j=32; j>i+1; j--){
                cout<<" ";
            }
            for(int j=0; j<i; j++)
            {
                cout<<"*";
            }
            for(int j=0; j<i; j++)
            {
                cout<<"*";
            }
            sleep(0.1);
        }
        system("CLS");
        space();
        cout<<"*************************** Credits ****************************\n";
        space();
        cout<<"|                          ";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"Created By";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        for(int i=0; i<6; i++)
        {
            space();
            cout<<"|                                                              |\n";
        }
        space();
        for(int i=0; i<64;i++)
        {
            cout<<"*";
        }
        sleep(0.2);

        system("CLS");
        space();
        cout<<"*************************** Credits ****************************\n";
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                          ";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"Created By";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        for(int i=0; i<5; i++)
        {
            space();
            cout<<"|                                                              |\n";
        }
        space();
        for(int i=0; i<64;i++)
        {
            cout<<"*";
        }
        sleep(0.8);

        string name[4]={"Sandeep Chhetri", "Samriddha Singh", "Sulav Thapa", "Rajendra Rawal"};
        for(int i=0; i<15; i++)
        {
            system("CLS");
            space();
            cout<<"*************************** Credits ****************************\n";
            space();
            cout<<"|                                                              |\n";
            space();
            cout<<"|                          ";
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Created By";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"                          |\n";
            space();
            cout<<"|";
            SetConsoleTextAttribute(hConsole, 10);
            for(int j=14-i; j<15; j++){
                cout<<name[0][j];
            }
            SetConsoleTextAttribute(hConsole, 3);
            for(int j=0; j<61-i; j++){
                cout<<" ";
            }
            cout<<"|\n";
            space();
            cout<<"|";
            for(int j=0; j<61-i; j++){
                cout<<" ";
            }
            SetConsoleTextAttribute(hConsole, 10);
            for(int j=0; j<i+1; j++){
                cout<<name[1][j];
            }
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"|\n";
            for(int i=0; i<3; i++)
            {
                space();
                cout<<"|                                                              |\n";
            }
            space();
            for(int i=0; i<64;i++)
            {
                cout<<"*";
            }
            sleep(0.1);
        }

        for(int i=0; i<23; i++)
        {
            system("CLS");
            space();
            cout<<"*************************** Credits ****************************\n";
            space();
            cout<<"|                                                              |\n";
            space();
            cout<<"|                          ";
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"Created By";
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"                          |\n";
            space();
            cout<<"|";
            for(int j=0; j<i+1; j++)
            {
                cout<<" ";
            }
            SetConsoleTextAttribute(hConsole, 10);
            cout<<name[0];
            SetConsoleTextAttribute(hConsole, 3);
            for(int j=0; j<61-i-15; j++){
                cout<<" ";
            }
            cout<<"|\n";
            space();
            cout<<"|";
            for(int j=0; j<60-i-15; j++)
            {
                cout<<" ";
            }
            SetConsoleTextAttribute(hConsole, 10);
            cout<<name[1];
            SetConsoleTextAttribute(hConsole, 3);
            for(int j=0; j<i+2; j++){
                cout<<" ";
            }
            cout<<"|\n";
            for(int i=0; i<3; i++)
            {
                space();
                cout<<"|                                                              |\n";
            }
            space();
            for(int i=0; i<64;i++)
            {
                cout<<"*";
            }
            sleep(0.1);
        }

        system("CLS");
        space();
        cout<<"*************************** Credits ****************************\n";
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                          ";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"Created By";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        for(int i=0; i<2; i++)
        {
            space();
            cout<<"|                       ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<name[i];
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"                        |\n";
        }
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                         ";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<name[2];
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";

        space();
        for(int i=0; i<64;i++)
        {
            cout<<"*";
        }
        sleep(0.2);

        system("CLS");
        space();
        cout<<"*************************** Credits ****************************\n";
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                          ";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"Created By";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        for(int i=0; i<2; i++)
        {
            space();
            cout<<"|                       ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<name[i];
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"                        |\n";
        }
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                         ";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<name[2];
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        space();
        cout<<"|                       ";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<name[3];
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                         |\n";
        space();
        for(int i=0; i<64;i++)
        {
            cout<<"*";
        }
        sleep(0.2);

        system("CLS");
        space();
        cout<<"*************************** Credits ****************************\n";
        space();
        cout<<"|                                                              |\n";
        space();
        cout<<"|                          ";
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"Created By";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        for(int i=0; i<2; i++)
        {
            space();
            cout<<"|                       ";
            SetConsoleTextAttribute(hConsole, 10);
            cout<<name[i];
            SetConsoleTextAttribute(hConsole, 3);
            cout<<"                        |\n";
        }
        space();
        cout<<"|                         ";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<name[2];
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                          |\n";
        space();
        cout<<"|                       ";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<name[3];
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"                         |\n";
        space();
        cout<<"|                                                              |\n";
        space();
        for(int i=0; i<64;i++)
        {
            cout<<"*";
        }
        sleep(0.8);

        cout<<endl<<endl;
        space();
        SetConsoleTextAttribute(hConsole, 12);
        cout<<"                   Press any key to return...";
        SetConsoleTextAttribute(hConsole, 13);
        getch();

    }

    //---------------------------------------------------------end credits-----------------------------------------------------------------


    //--------------------------------------------------------Change Password--------------------------------------------------------

    void change_password(){
        system("CLS");
        string username, pass[2], opass;
        int score;
        space();
        cout<<"********************* Change Your Password *********************\n\n";
        for(int j=0;j<2;j++)
        {
            do{
                int i=0;
                char dotpass[100];
                cout<<endl<<endl;
                space();
                SetConsoleTextAttribute(hConsole, 10);
                if(j==0){
                    cout<<"                   Enter New Password: ";
                }
                else{
                    cout<<"                   Enter New Password(again): ";
                }
                while((dotpass[i]=getch())!='\r'){
                    if(int(dotpass[i])==8)
                    {
                        if(i==0){
                            continue;
                        }
                        cout<<char(8);
                        cout<<" ";
                        cout<<char(8);
                        i--;
                        continue;
                    }
                    cout<<"*";
                    i++;
                    dotpass[i]='\0';
                    pass[j] = dotpass;
                }
                if(i==0){
                    char dotpass[100];
                    pass[j]="";
                }
                int spacecheck=0;
                for(int k=0; k<pass[j].length(); k++)
                {
                    if(pass[j][k]==' '){
                        cout<<endl;
                        space();
                        SetConsoleTextAttribute(hConsole, 12);
                        cout<<"                   Password can't contain space.";
                        SetConsoleTextAttribute(hConsole, 10);
                        spacecheck=1;
                        break;
                    }
                }
                if(spacecheck==1){
                    pass[j]="space";
                }
                if(pass[j].length()>10)
                {
                    cout<<endl;
                    space();
                    SetConsoleTextAttribute(hConsole, 12);
                    cout<<"                   Password can't be more that 10 characters.";
                    SetConsoleTextAttribute(hConsole, 10);
                }
                if(spacecheck==1){
                    pass[j]="password with space";
                }

                if(pass[j].length()==0){
                    cout<<endl;
                    space();
                    SetConsoleTextAttribute(hConsole, 12);
                    cout<<"                   Password can't be blank.";
                    SetConsoleTextAttribute(hConsole, 10);
                }
            }while(pass[j].length()>10 | pass[j].length()==0);
        }
        if(pass[0]==pass[1]){
            fstream userdata("userdata.txt", ios::in);
            fstream temp("temp.dat", ios::out);
            while(userdata>>username>>opass>>score){
                if(name==username){
                    opass=pass[0];
                }
                temp<<username<<" "<<opass<<" "<<score<<endl;
            }
            userdata.close();
            temp.close();
            userdata.open("userdata.txt", ios::out);
            temp.open("temp.dat", ios::in);
            while(temp>>username>>opass>>score){
                userdata<<username<<" "<<opass<<" "<<score<<endl;
            }
            userdata.close();
            temp.close();
            cout<<endl<<endl;
            space();
            cout<<"                   Password Changed successfully.";
            sleep(1);
        }
        else{
            cout<<endl<<endl;
            space();
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"                   Password didn't match.";
            SetConsoleTextAttribute(hConsole, 10);
            sleep(1);
            this->change_password();
        }
    }

    //--------------------------------------------------------end change password--------------------------------------------------------
};

int main()
{
    CONSOLE_CURSOR_INFO CursoInfo;
    CursoInfo.dwSize = 1;
    CursoInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &CursoInfo);
    SetConsoleTextAttribute(hConsole, 3);

    User user;
    user.welcome();
    int cursor=1;  //for navigation
    int nav,key;
    int exit=0;
    do{
        system("CLS");
        //------------------------------------------------------------menu-----------------------------------------------------------
        space();
        SetConsoleTextAttribute(hConsole, 3);
        cout<<"********************** TypeRace Game Menu **********************\n\n";
        space();
        cout<<"                     Game Highscore: ";
        SetConsoleTextAttribute(hConsole, 10);
        for(int i=0; i<3-to_string(user.bestscore).length(); i++){
            cout<<" ";
        }
        cout<<user.bestscore;
        cout<<" Wpm";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<endl<<endl;
        space();
        cout<<"User: ";
        SetConsoleTextAttribute(hConsole, 10);
        cout<<user.name;
        SetConsoleTextAttribute(hConsole, 3);
        for(int k=0; k<64-26-user.name.length()-3; k++)
        {
            cout<<" ";
        }
        cout<<"Your Highscore: ";
        SetConsoleTextAttribute(hConsole, 10);
        for(int i=0; i<3-to_string(user.highscore).length(); i++){
            cout<<" ";
        }
        cout<<user.highscore;
        cout<<" Wpm";
        SetConsoleTextAttribute(hConsole, 3);
        cout<<endl<<endl;
        space();
        space();
        cout<<"    ";
        if(cursor==1){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"Start Game\n";
        SetConsoleTextAttribute(hConsole, 3);
        space();
        space();
        cout<<"    ";
        if(cursor==2){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"High Scores\n";
        SetConsoleTextAttribute(hConsole, 3);
        space();
        space();
        cout<<"    ";
        if(cursor==3){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"Level\n";
        SetConsoleTextAttribute(hConsole, 3);
        space();
        space();
        cout<<"    ";
        if(cursor==4){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"Credits\n";
        SetConsoleTextAttribute(hConsole, 3);
        space();
        space();
        cout<<"    ";
        if(cursor==5){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"Change Password\n";
        SetConsoleTextAttribute(hConsole, 3);
        space();
        space();
        cout<<"    ";
        if(cursor==6){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"Log Out\n";
        SetConsoleTextAttribute(hConsole, 3);
        space();
        space();
        cout<<"    ";
        if(cursor==7){
            SetConsoleTextAttribute(hConsole, 12);
            cout<<"> ";
        }
        else{
            cout<<" ";
        }
        cout<<"Exit\n";
        SetConsoleTextAttribute(hConsole, 3);
        //------------------------------------------------------------end menu----------------------------------------------------------------

        //------------------------------------------------------------navigation---------------------------------------------------------------

        nav=getch();
        if(nav==224)
        {
            key=getch();
            switch(key){
                case KEY_UP:
                    cursor-=1;
                    if(cursor==0){
                        cursor=7;
                    }
                    break;
                case KEY_DOWN:
                    cursor+=1;
                    if(cursor==8){
                        cursor=1;
                    }
                    break;
                default:
                    break;
            }
        }
        if(nav==13)
        {
            switch(cursor)
            {
                case 1:
                user.game();
                break;

                case 2:
                user.displayhighscores();
                break;

                case 3:
                user.changelevel();
                break;

                case 4:
                user.credits();
                break;

                case 5:
                user.change_password();
                cursor = 1;
                break;

                case 6:
                user.password="";
                cout<<endl;
                space();
                space();
                cout<<"     ";
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"Logging out.";
                sleep(1);
                cout<<".";
                SetConsoleTextAttribute(hConsole, 3);
                user.welcome();
                cursor = 1;
                break;

                case 7:
                system("CLS");
                cout<<endl<<endl;
                space();
                SetConsoleTextAttribute(hConsole, 12);
                cout<<"********************** Thank you For Playing **********************\n\n";
                SetConsoleTextAttribute(hConsole, 0);
                exit=1;
                break;
            }
        }

        //------------------------------------------------------------end navigation-------------------------------------------------------------

    }while(exit==0);
}
