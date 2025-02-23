#include <iostream>
#include <chrono>

using namespace std;

const int MAIN_ARRAY_SIZE = 6;
const int QUARTER_ARRAY_SIZE = 9;
const int CONSOLE_HEIGHT = 25;

// struktura graczy
struct players {
    string name[2];
    char token1 = 'X';
    char token2 = 'O';
};

// historia ruchów (tur)
struct history {
    int mainarray[MAIN_ARRAY_SIZE][MAIN_ARRAY_SIZE];
};

// zmiana żetonów
void changeToken(players& plrs, int i) {
    char newToken;

    do {

        cout << endl << "GRACZ " << plrs.name[i] << ", wybierz żeton:" << endl;
        cout << "O X / \\ * - + < > ?" << endl;
        cout << "0 1 2 3 4 5 6 7 8 9" << endl;
        cin >> newToken;

    } while (newToken == plrs.token1 || newToken == plrs.token2);

    switch (newToken)
    {
    case '0':
        newToken = '0';
        break;

    case '1':
        newToken = 'X';
        break;

    case '2':
        newToken = '/';
        break;

    case '3':
        newToken = '\\';
        break;

    case '4':
        newToken = '*';
        break;

    case '5':
        newToken = '-';
        break;

    case '6':
        newToken = '+';
        break;

    case '7':
        newToken = '<';
        break;

    case '8':
        newToken = '>';
        break;

    case '9':
        newToken = '?';
        break;

    default:
        if (i == 0) newToken = plrs.token1;
        else newToken = plrs.token2;
        break;
    }

    if (i == 0) plrs.token1 = newToken;
    else plrs.token2 = newToken;
}

// wyświetlanie głównej tablicy
void displayMainArray(int tab[][MAIN_ARRAY_SIZE], players plrs) {
    for (int i = 0; i < MAIN_ARRAY_SIZE; i++) {
        if (i == 3)
            cout << endl << endl;
        for (int j = 0; j < MAIN_ARRAY_SIZE; j++) {

            if (j == MAIN_ARRAY_SIZE / 2) {
                if (tab[i][j] == 1)
                    cout << "  |" << plrs.token1 << "|";
                else if (tab[i][j] == 2)
                    cout << "  |" << plrs.token2 << "|";
                else
                    cout << "  | |";

            }
            else {
                if (tab[i][j] == 1)
                    cout << "|" << plrs.token1 << "|";

                else if (tab[i][j] == 2)
                    cout << "|" << plrs.token2 << "|";

                else
                    cout << "| |";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

// inicjacja głównej tablicy (wypełnienie jej zerami - polami z brakiem żetonów jakiegokolwiek gracza)
void initArr(int arr[][MAIN_ARRAY_SIZE]) {
    for (int i = 0; i < MAIN_ARRAY_SIZE; i++) {
        for (int j = 0; j < MAIN_ARRAY_SIZE; j++) {
            arr[i][j] = 0;
        }
    }
}

// warunek zwycięstwa
bool isWin(int arr[][MAIN_ARRAY_SIZE], int player, bool isPentago) {
    int check = 0;

    for (int i = 0; i < MAIN_ARRAY_SIZE; i++) {
        if (isPentago == true) {
            if (check >= 5) return true;
            else check = 0;
        }
        else {
            if (check == 6) return true;
            else check = 0;
        }

        for (int j = 0; j < MAIN_ARRAY_SIZE; j++) {
            if (arr[i][j] == player)
                check += 1;
        }
    }

    for (int a = 0; a < MAIN_ARRAY_SIZE; a++) {
        if (isPentago == true) {
            if (check >= 5) return true;
            else check = 0;
        }
        else {
            if (check == 6) return true;
            else check = 0;
        }

        for (int b = 0; b < MAIN_ARRAY_SIZE; b++) {
            if (arr[b][a] == player)
                check += 1;
        }
    }

    if (isPentago == true) {
        if (arr[0][0] == player && arr[1][1] == player && arr[2][2] == player && arr[3][3] == player && arr[4][4] == player || arr[1][1] == player && arr[2][2] == player && arr[3][3] == player && arr[4][4] == player && arr[5][5] == player || arr[0][5] == player && arr[1][4] == player && arr[2][3] == player && arr[3][2] == player && arr[4][1] == player || arr[1][4] == player && arr[2][3] == player && arr[3][2] == player && arr[4][1] == player && arr[5][0] == player || arr[0][1] == player && arr[1][2] == player && arr[2][3] == player && arr[3][4] == player && arr[4][5] == player || arr[1][0] == player && arr[2][1] == player && arr[3][2] == player && arr[4][3] == player && arr[5][4] == player || arr[0][4] == player && arr[1][3] == player && arr[2][2] == player && arr[3][1] == player && arr[4][0] == player || arr[1][5] == player && arr[2][4] == player && arr[3][3] == player && arr[4][2] == player && arr[5][1] == player)
            return true;
    }
    else {
        if (arr[0][0] == player && arr[1][1] == player && arr[2][2] == player && arr[3][3] == player && arr[4][4] == player && arr[5][5] == player || arr[0][5] == player && arr[1][4] == player && arr[2][3] == player && arr[3][2] == player && arr[4][1] == player && arr[5][0] == player)
            return true;
    }
}

// konwersja wybranej ćwiartki głównej tablicy na tablicę zawierającą jedynie tę ćwiartkę
void convertToQuarter(int mainArray[][MAIN_ARRAY_SIZE], int quarterArray[], char quarterChoice) {

    if (quarterChoice == 'q') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                quarterArray[i * 3 + j] = mainArray[i][j];
            }
        }
    }

    if (quarterChoice == 'w') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                quarterArray[i * 3 + j] = mainArray[i][j + 3];
            }
        }
    }

    if (quarterChoice == 'a') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                quarterArray[i * 3 + j] = mainArray[i + 3][j];
            }
        }
    }

    if (quarterChoice == 's') {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                quarterArray[i * 3 + j] = mainArray[i + 3][j + 3];
            }
        }
    }
}

// kopiowanie elementów jednej tablicy do drugiej (przydatne do zapisu historii tur)
void saveArray(int arrayTo[][MAIN_ARRAY_SIZE], int arrayFrom[][MAIN_ARRAY_SIZE]) {
    for (int i = 0; i < MAIN_ARRAY_SIZE; i++) {
        for (int j = 0; j < MAIN_ARRAY_SIZE; j++) {
            arrayTo[i][j] = arrayFrom[i][j];
        }
    }
}

// zapis historii
void saveHistory(int mainArray[][MAIN_ARRAY_SIZE], history memory[], int& move) {
    saveArray(memory[move].mainarray, mainArray);
}

// zapis tablicy ćwiartki do głownej tablicy (aby można było wyczyścić tablicę ćwiartkową)
void savequarter(int arr[][MAIN_ARRAY_SIZE], int quarterArr[], char quarter) {
    if (quarter == 'q') {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) {
                arr[i][j] = quarterArr[i * 3 + j];
            }
        }
    }

    if (quarter == 'w') {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) {
                arr[i][j + 3] = quarterArr[i * 3 + j];
            }
        }
    }

    if (quarter == 'a') {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) {
                arr[i + 3][j] = quarterArr[i * 3 + j];
            }
        }
    }

    if (quarter == 's') {
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++) {
                arr[i + 3][j + 3] = quarterArr[i * 3 + j];
            }
        }
    }

}

// obrót ćwiartki
void rotate(int mainArray[][MAIN_ARRAY_SIZE], int quarterArray[], char direction, char quarter) {
    int quartArrSup[9];
    int counter = 0;
    if (direction == 'z') {
        for (int i = 0; i < 3; i++) {
            for (int j = 1; j < 4; j++) {
                quartArrSup[counter] = quarterArray[9 + i - 3 * j];
                counter++;
            }
        }
    }
    else if (direction == 'x') {
        for (int i = 2; i > -1; i--) {
            for (int j = 0; j < 3; j++) {
                quartArrSup[counter] = quarterArray[i + 3 * j];
                counter++;
            }
        }
    }

    for (int i = 0; i < 9; i++) {
        quarterArray[i] = quartArrSup[i];
    }

    savequarter(mainArray, quarterArray, quarter);
}

// predefiniowana tablica
void predefArray(int mainArray[][MAIN_ARRAY_SIZE]) {
    mainArray[0][1] = 1;
    mainArray[1][4] = 1;
    mainArray[2][5] = 1;
    mainArray[4][5] = 1;
    mainArray[2][3] = 1;
    mainArray[4][0] = 1;
    mainArray[5][5] = 2;
    mainArray[5][0] = 2;
    mainArray[5][4] = 2;
    mainArray[1][1] = 2;
    mainArray[5][1] = 2;
    mainArray[5][2] = 2;
}

// ruch po wybranej ćwiartce
void move(int mainArray[][MAIN_ARRAY_SIZE], int quarterArray[], int& space, char choice, int player) {

    bool valid = true;
    switch (space)
    {
    case 1:
        if (valid == true) quarterArray[6] = player;
        break;

    case 2:
        if (valid == true) quarterArray[7] = player;
        break;

    case 3:
        if (valid == true) quarterArray[8] = player;
        break;

    case 4:
        if (valid == true) quarterArray[3] = player;
        break;

    case 5:
        if (valid == true) quarterArray[4] = player;
        break;

    case 6:
        if (valid == true) quarterArray[5] = player;
        break;

    case 7:
        if (valid == true) quarterArray[0] = player;
        break;

    case 8:
        if (valid == true) quarterArray[1] = player;
        break;

    case 9:
        if (valid == true) quarterArray[2] = player;
        break;

    default:
        cout << "Nie istnieje pole 0!" << endl;
        cin >> space;
    }
    savequarter(mainArray, quarterArray, choice);
}

// sprawdzanmie czy można postawić żeton
bool checkIfValid(int quarterArray[], int& space) {

    switch (space)
    {
    case 1:
        if (quarterArray[6] == 0) return true;
        else return false;
        break;
    case 2:
        if (quarterArray[7] == 0) return true;
        else return false;
        break;

    case 3:
        if (quarterArray[8] == 0) return true;
        else return false;
        break;

    case 4:
        if (quarterArray[3] == 0) return true;
        else return false;
        break;

    case 5:
        if (quarterArray[4] == 0) return true;
        else return false;
        break;

    case 6:
        if (quarterArray[5] == 0) return true;
        else return false;
        break;

    case 7:
        if (quarterArray[0] == 0) return true;
        else return false;
        break;

    case 8:
        if (quarterArray[1] == 0) return true;
        else return false;
        break;

    case 9:
        if (quarterArray[2] == 0) return true;
        else return false;
        break;

    default:
        cout << "Nie istnieje takie pole!" << endl;
        cin >> space;
    }
}

// wyświetlanie historii tur
void displayMemory(int mainArray[][MAIN_ARRAY_SIZE], history memory[], players plrs, int turnCounterVar, int& trueTurnCounter) {
    char choice;

    do {
        cout << "PODGLĄD TURY " << turnCounterVar + 1 << endl << "Wybierz akcję:" << endl << "[z] - wcześniejszy ruch" << endl << "[x] - następny ruch" << endl;
        
        // wyświetla się póki nazwa gracza 1 nie jest równa "
        if (plrs.name[0] != "\"") cout << "[c] - cofnij do tego ruchu" << endl;
        cout << "[v] - anuluj" << endl << endl;

        displayMainArray(memory[turnCounterVar].mainarray, plrs);
        cin >> choice;
        cout << endl << endl;
        if (choice == 'z' && turnCounterVar != 0) displayMemory(mainArray, memory, plrs, turnCounterVar - 1, trueTurnCounter);
        else if (choice == 'x' && turnCounterVar != trueTurnCounter) displayMemory(mainArray, memory, plrs, turnCounterVar + 1, trueTurnCounter);
        else if (choice == 'c') {
            saveArray(mainArray, memory[turnCounterVar].mainarray);
            trueTurnCounter = turnCounterVar;
        }

    } while (choice != 'z' && choice != 'x' && choice != 'c' && choice != 'v');

}

// wyświetlanie opcji
void navMenu(int mainArray[][MAIN_ARRAY_SIZE], char choice, players& plrs, int i, int& turnCounter, history memory[]) {
    cout << endl << endl << "MENU OPCJI" << endl << "[p] - pauza" << endl << "[u] - undo" << endl << "[o] - wczytanie predefiniowanej planszy" << endl << "[h] - opis programu" << endl << "[n] - zmiana żetonów" << endl << "[m] - wyjście z menu opcji" << endl << endl << "Wybór:";
    cin >> choice;
    switch (choice)
    {
    case 'p':
        for (int i = 0; i < CONSOLE_HEIGHT; i++) {
            if (i == CONSOLE_HEIGHT / 2) cout << "PAUZA - naciśnij dowolny przycisk by wznowić grę";
            cout << endl;
        }
        cin >> choice;
        cout << endl << endl;
        break;

    case 'u':
        displayMemory(mainArray, memory, plrs, turnCounter, turnCounter);
        break;

    case 'o':
        cout << endl << endl;
        predefArray(mainArray);
        displayMainArray(mainArray, plrs);
        break;

    case 'm':
        cout << "Wychodzę z menu opcji" << endl << endl;
        break;

    case 'h':
        cout << "Pentago jest grą dwuosobową na planszy. Plansza składa się z 4 ruchomych części, które można obracać. Każda część zawiera 9 miejsc na żetony. Gracze po kolei oddają ruch składający się z 2 części:" << endl << "- dołożenia swojego żetonu na niezajęte pole planszy;" << endl << "- obrót jednej z części planszy o 90 stopni w dowolnym kierunku." << endl << "Nie można zrezygnować z żadnej części ruchu.Wygrywa osoba, której 5 żetonów, po pełnym ruchu, są ułożone w rzędzie / kolumnie / po skosach(podobnie do gry kółko krzyżyk)." << endl << endl;
        break;

    case 'n':
        changeToken(plrs, i);
        cout << endl << endl;
    default:
        break;
    }
}

// wczytanie ćwiartki (do tablicy ćwiartkowej) by na niej działać
void switchBetweenQuarters(int mainArray[][MAIN_ARRAY_SIZE], int quarterArray[], char choice) {
    switch (choice)
    {
    case 'q':
        convertToQuarter(mainArray, quarterArray, 'q');
        break;
    case 'w':
        convertToQuarter(mainArray, quarterArray, 'w');
        break;
    case 'a':
        convertToQuarter(mainArray, quarterArray, 'a');
        break;
    case 's':
        convertToQuarter(mainArray, quarterArray, 's');
        break;
    default:
        break;
    }
}

// część ruchu (wybór ćwiartki, pola i ew. opcji)
void turnChoose(int mainArray[][MAIN_ARRAY_SIZE], int quarterArray[], players& plrs, char& quarter, int& space, int i, int turnCounter, history memory[]) {
    do
    {
        cout << endl << endl << "Ruch nr " << turnCounter + 1 << endl << "Ruch gracza " << i + 1 << ": " << plrs.name[i];

        if (i == 0) cout << " ( " << plrs.token1 << " )";
        else cout << " ( " << plrs.token2 << " )";

        cout << endl << endl << "Wybierz cwiartkę i pole, lub wejdź do menu opcji [m]" << endl << endl;

        displayMainArray(mainArray, plrs);
        cin >> quarter;
        if (quarter == 'm') navMenu(mainArray, quarter, plrs, i, turnCounter, memory);
        else cin >> space;
    } while (quarter != 'q' && quarter != 'w' && quarter != 'a' && quarter != 's');
}

// część ruchu (wybór ćwiartki do obrotu)
void turnChooseRotation(int quarterArray[], char& quarter, char& rotate) {
    do
    {
        cout << "Wybierz ćwiartkę(q/w/a/s)" << endl;
        cin >> quarter;
        cout << "Wybierz kierunek obrotu(z/x)" << endl;
        cin >> rotate;
    } while (quarter != 'q' && quarter != 'w' && quarter != 'a' && quarter != 's' && rotate != 'z' && rotate != 'x');
}

// ruch
void turn(int mainArray[][MAIN_ARRAY_SIZE], int quarterArray[], players& plrs, int i, bool isPentago, history memory[], int& turnCounter) {
    char quarter;
    char rotateDirection;
    int space = 0;
    saveHistory(mainArray, memory, turnCounter);

    do {
        turnChoose(mainArray, quarterArray, plrs, quarter, space, i, turnCounter, memory);
        switchBetweenQuarters(mainArray, quarterArray, quarter);
    } while (!checkIfValid(quarterArray, space));

    move(mainArray, quarterArray, space, quarter, i + 1);

    cout << endl << endl;
    displayMainArray(mainArray, plrs);
    cout << endl << endl;

    if (isPentago == true) {
        do
        {
            turnChooseRotation(quarterArray, quarter, rotateDirection);
            switchBetweenQuarters(mainArray, quarterArray, quarter);
        } while (rotateDirection != 'z' && rotateDirection != 'x');
        rotate(mainArray, quarterArray, rotateDirection, quarter);
    }

    saveHistory(mainArray, memory, turnCounter);
    turnCounter++;
}

// wstęp przed właściwą częścią gry (ma wykonać się tylko na początku działania programu) - m. in. wprowadzanie nazw graczy, wybór gry
void intro(players& plrs, bool& isPentago) {
    char choice;
    cout << "GRACZ 1, jak się nazywasz: ";
    cin >> plrs.name[0];
    cout << endl;
    changeToken(plrs, 0);
    cout << endl << endl;
    cout << "GRACZ 2, jak się nazywasz: ";
    cin >> plrs.name[1];
    cout << endl;
    changeToken(plrs, 1);
    cout << endl << endl;

    do {

        cout << "Wybierz grę:" << endl << "[p] - pentago" << endl << "[k] - kółko i krzyżyk " << endl << endl << "Wybór: ";
        cin >> choice;
        if (choice == 'k') isPentago = false;
        else isPentago = true;

    } while (choice != 'k' && choice != 'p');

    cout << endl << endl;
}

// inicjalizacja gry (inicjowanie potrzebnych elementów i zmiennych)
void initGame() {
    players plrs;
    history memory[MAIN_ARRAY_SIZE * MAIN_ARRAY_SIZE];
    int mainArray[MAIN_ARRAY_SIZE][MAIN_ARRAY_SIZE];
    int quarterArray[QUARTER_ARRAY_SIZE];
    int turnCounter = 0;
    bool game = true;
    bool isPentago;
    initArr(mainArray);
    intro(plrs, isPentago);

    // dopóki gra trwa (nikt jeszcze nie wygrał) wykonuje się funkcja odpowiedzialna za prowadzenie tury
    while (game) {
        for (int i = 0; i < 2; i++) {
            turn(mainArray, quarterArray, plrs, i, isPentago, memory, turnCounter);
            if (isWin(mainArray, i + 1, isPentago) == true) {
                cout << endl << endl << "KONIEC GRY!" << endl << "ZWYCIĘŻYŁ GRACZ " << i + 1 << ": " << plrs.name[i] << endl;
                displayMainArray(mainArray, plrs);
                i = 1;
                game = false;
            }
        }
    }

    initArr(memory[turnCounter].mainarray);
    
    // zmniejszanie licznika ruchów o 1 - ostatni ruch był zwycięski
    turnCounter--;

    // nazwa gracza jest równa " - oznaczenie czego nie wyświetlać w menu historii po końcu gry
    plrs.name[0] = "\"";
    displayMemory(mainArray, memory, plrs, turnCounter, turnCounter);
}



int main() {

    // polskie znaki
    setlocale(LC_ALL, "");
    initGame();
    return 0;

}