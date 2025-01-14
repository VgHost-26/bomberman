//funkcje wykorzystywane w pliku menu.cpp
#pragma once

//wyswietlanie logo na środku ekranu
void printLogo(int color, int place){      
    
    fstream plik;
    string line{};
    plik.open("logo.txt");
    SetConsoleTextAttribute(hConsole, color);
    cout<<endl<<endl;
    for(int i=0;i<13;i++){
        cout.width(place);
        
        getline(plik,line);
        cout<<line<<endl;
    }
    cout<<endl<<endl;
    plik.close();  
}

 //wyswietlanie kolorowej bomby w logo
void printBomob(){  
    
    fstream plik;
    string line{};
    plik.open("bomb.txt");
    SetConsoleTextAttribute(hConsole, _Yellow);
    cout<<endl<<endl;
    for(int i=0;i<12;i++){
        if (i<3) setCursorPosition(32,i+2);
        if (i>=3 & i<=6) setCursorPosition(32-i,i+2);
        if (i>6) setCursorPosition(26,i+2);
        
        getline(plik,line);
        cout<<line<<endl;
    }
    cout<<endl<<endl;
    plik.close();  
}

 //wyswietlanie animacji intra   
void printIntro(double winWidth, double winHeight, int time, int step){  
    
    fstream plik;
    string line{};
    SetConsoleTextAttribute(hConsole, defCol);

    double up_position=0;
    double up_move=0, left_move=0;
    
    bool cero=true, uno=true ,dos=false;

    while (cero) {
        plik.open("intro.txt");

        for(int i=0;i<94;i++) {

            getline(plik,line);

            if(line!=" ") {
                setCursorPosition((winWidth-left_move),((winHeight/2.0-(4.0+up_move))+up_position));
                cout<<line<<endl;
                up_position++;
            }
            else {
                up_position=0; // to jest po to żeby linie tekstu sie wyswietlały pod sobą
                
                if (left_move<=90) {
                    up_move+=0.5;
                    left_move+=step;  //ile klatek zmiesci sie w animacji (mniej = wiecej klatek)
                    } else {
                        uno=false; dos=true;
                    }

                if (uno)  Sleep(time); //przerwa czasowa miedzy klatkami

                else if (dos) {
                    Sleep(time*8);
                    dos=false;
                }
                system("cls");
            }
        }
        plik.close();

        if (uno==false & dos==false) cero=false;
    }  

    plik.open("intro2.txt");

    for (int i=0; i<44; i++) {
        SetConsoleTextAttribute(hConsole, _Orange);
        getline(plik,line);

        if(line!=" ") {
            setCursorPosition((winWidth-left_move),((winHeight/2.0-(4.0+up_move))+up_position));
            cout<<line<<endl;
            up_position++;
        }
        else {
            if (i==43) Sleep(time*5);
            up_position=0;
            Sleep(time*2);
            system("cls");
        }
    }

    plik.close();
}

//obliczanie miejsca na środku ekranu dla konkretnego elementu wzgledem szerokości ekranu
int middleCalc(int winWidth, int objWidth){     
    return winWidth-((winWidth-objWidth)/2);
}

//podswietlanie wybranego elementu menu
void select(string tab[], int dl, int kt, int baseColor, int selectedColor, int place, int offset=0){    
    
    for(int i=0;i<dl;i++){
        
        if(i==kt){
            SetConsoleTextAttribute(hConsole, selectedColor);
        }else{
            SetConsoleTextAttribute(hConsole, baseColor);
        }
        setCursorPosition(place-10,15+((i+offset)*2));
        cout<<tab[i];
    }
}

//wyswietla dostepne przyciski w prawym dolnym rogu
void helpButtons(int x, int y)
{
    SetConsoleTextAttribute(hConsole, _LightGrey);
    setCursorPosition(x,y);
    cout<<char(30)<<" gora / "<<char(31)<<" dol / "<<"<"<<char(217)<<" zatwierdz";
    //cout<<"▲ góra | ▼ dół | <┘ zatwierdź";
}

//czysci wybrana linie tekstu
void clearLine(int x, int y, int width){   
    setCursorPosition(x,y);
    for(int i=0;i<width;i++) cout<<" ";

}
//wypisanei na ekranie funkcjonalnego tak/nie z mo�liwoscia wyboru
bool confirm(int x, int y, int dCol, int sCol, bool border=0, string msg=""){ 
            // pozycja,     kolor,   kolor wybranego el, czy ramka, wiadomosc
    if(border){
        //rysowanie ramki jesli tak wybrano
        int tmp=1;
        if(msg!=""){
            setCursorPosition(x - 3, y - 1);
            cout.width( 16 - (16 - msg.length())/2 );
            cout<<msg;
            cout.width( (16 - msg.length())/2 +1 );
            tmp=2;
        }
    }

    setCursorPosition(x,y);
    SetConsoleTextAttribute(hConsole, dCol);
    cout<<"Tak"<<"   ";
    SetConsoleTextAttribute(hConsole, sCol);
    cout<<"Nie";
    int tn=0;
    int k{};
    while(1){
        k=getKey();
        if(k==77){   // w prawo
            setCursorPosition(x,y);
            SetConsoleTextAttribute(hConsole, dCol);
            cout<<"Tak   ";
            SetConsoleTextAttribute(hConsole, sCol);
            cout<<"Nie";
            tn=0;
        }
        if(k==75){   // w lewo
            setCursorPosition(x,y);
            SetConsoleTextAttribute(hConsole, sCol);
            cout<<"Tak   ";
            SetConsoleTextAttribute(hConsole, dCol);
            cout<<"Nie";
            tn=1;
        }
        if(k==13){   //enter
            clearLine(x-2,y,  17);
            clearLine(x-2,y-2,17);
            clearLine(x-2,y-1,17);
            clearLine(x-2,y+1,17);
            return tn;
        }
    }
    return 0;
}

//tworzy tabelke na bazie przekazanego stylu
void generateTable(string style[], int size, int place){    
    cout.width(place);
    cout<<style[0]<<endl;
    for(int i=0;i<size;i++){
        cout.width(place);
        cout<<style[1]<<endl;
        if(i!=size-1){
            cout.width(place);
            cout<<style[2]<<endl;
        }
    }
    cout.width(place);
    cout<<style[3]<<endl;
}

 //sprawdza czy "string st" zawiera znak "char z"
bool includeChar(string st, char z){   

    for(int i=0;i<st.length();i++){
        if(st[i]==z){
            return true;
        }
    }
    return false;

}

void coutGoBack(){

    int length = consoleScreenBufferInfo.dwMaximumWindowSize.Y;

    setCursorPosition(getCursorPosition().X, length-2);

    setCenter(36); cout<<"Kliknij dowolny klawisz, by wr�ci�"<<endl;
}