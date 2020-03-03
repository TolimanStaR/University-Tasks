#ifndef CASINO_DATA_H
#define CASINO_DATA_H

// Все неизменяемые значения для удобства хранятся здесь:

enum gameTypes {

    // Представленные в программе типы игры:

    Fool,
    Holdem,
    TwentyOne,

} gameType;

int numberOfCardsForGame[3] = {

        // Количество карт у каждого игрока для разных типов игры:

        6,  // Fool
        5,  // Holdem
        2,  // 21

};

int deckSizeForGame[3] = {

        // Количество карт в колоде для каждой игры:

        52,  // Fool
        54,  // Holdem
        36,  // 21

};

const char class[5][9] = {
        "Diamonds",
        "Hearts  ",
        "Clubs   ",
        "Spades  ",
        "Joker   ",
};

const wchar_t id[14][6] = {
        L"Two  ",
        L"Three",
        L"Four ",
        L"Five ",
        L"Six  ",
        L"Seven",
        L"Eight",
        L"Nine ",
        L"Ten  ",
        L"Jack ",
        L"Queen",
        L"King ",
        L"Ace  ",
        L"Card ",
};

const int wClass[5] = {
        0x2663,
        0x2662,
        0x2661,
        0x2660,
        0x2660,
};

const int container[] = {
        0x2589,  // border div
        0x25AD,  // stats div
};

const wchar_t casinoPlayers[][25] = {
        L"Edna Mode ",
        L"Randle McMurphy ",
        L"Optimus Prime ",
        L"Norman Bates ",
        L"The Minions ",
        L"Maximus ",
        L"Legolas ",
        L"Wednesday Addams ",
        L"Inspector Clouseau ",
        L"Inigo Montoya ",
        L"Hal ",
        L"Groot ",
        L"Gromit ",
        L"Ethan Hunt ",
        L"Red ",
        L"Walker ",
        L"Corporal Hicks ",
        L"Bane ",
        L"Woody ",
        L"Withnail ",
        L"Vendetta ",
        L"Roy Batty ",
        L"Martin Blank ",
        L"Samwise Gamgee ",
        L"William Hudson ",
        L"Lisbeth Salander ",
        L"Frank Drebin ",
        L"Donnie Darko ",
        L"Captain Kirk ",
        L"Star-Lord ",
        L"Tony Montana ",
        L"Marge Gunderson ",
        L"Neo ",
        L"Harry Potter ",
        L"Gollum ",
        L"Hans Landa ",
        L"George Bailey ",
        L"Wolverine ",
        L"E.T. ",
        L"Bilbo Baggins ",
        L"Dr. King Schultz ",
        L"Ace Ventura ",
        L"Sarah Connor ",
        L"Katniss Everdeen ",
        L"Jack Burton ",
        L"Axel Foley ",
        L"Amélie Poulain ",
        L"Vito Corleone ",
        L"Shaun Riley ",
        L"Obi-Wan Kenobi ",
        L"Luke Skywalker ",
        L"Harry Callahan ",
        L"Lester Burnham ",
        L"Rick Deckard ",
        L"Captain America ",
        L"Tommy DeVito ",
        L"Anton Chigurh ",
        L"Amy Dunne ",
        L"Lou Bloom ",
        L"Keyser Söze ",
        L"Ferris Bueller ",
        L"Driver ",
        L"Yoda ",
        L"Walter Sobchak ",
        L"Rocky Balboa ",
        L"Atticus Finch ",
        L"Captain Mal Reynolds ",
        L"The Man With No Name ",
        L"Jules Winnfield ",
        L"Peter Venkman ",
        L"Gandalf ",
        L"Snake Plissken ",
        L"The Terminator ",
        L"Forrest Gump ",
        L"Patrick Bateman ",
        L"Ash ",
        L"Daniel Plainview ",
        L"The Bride ",
        L"Travis Bickle ",
        L"Hannibal Lecter ",
        L"Doc Brown ",
        L"Loki ",
        L"Rick Blaine ",
        L"M. Gustave ",
        L"Ron Burgundy ",
        L"Aragorn ",
        L"Captain Jack Sparrow ",
        L"Iron Man ",
        L"Marty McFly ",
        L"Michael Corleone ",
        L"The Dude ",
        L"Darth Vader ",
        L"Tyler Durden ",
        L"John McClane ",
        L"The Joker ",
        L"Ellen Ripley ",
        L"Batman ",
        L"Han Solo ",
        L"James Bond ",
        L"Indiana Jones ",
};

#endif //CASINO_DATA_H
