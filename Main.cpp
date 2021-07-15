#undef UNICODE
#undef _UNICODE

#include <Windows.h>
#include <tchar.h>

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Sprites.hpp"
#include "Chess.hpp"

#include "Connector.hpp"

int main(void) {
        BoardPiece_t board[64]= { 0 };

        FreeConsole();
        MessageBox(nullptr, TEXT("Per giocare:\n- Premi invio per far giocare il computer contro il computer per 100 mosse;\n- Premi un altro tasto per far muovere il computer;\n- trascina un pezzo per muoverlo;\n- Per chiudere il gioco, premi F4;\n- una mossa invalida rompe il computer;\n- Il gioco si chiude automaticamente quando la partita e' finita.\nBuona fortuna!"), TEXT("Informazioni sul gioco"), MB_ICONINFORMATION | MB_OK);

        sf::RenderWindow CWindow(sf::VideoMode(512, 512), "Chess simulator", sf::Style::Titlebar);

        if (!LoadSprites()) {
                MessageBox(nullptr, TEXT("Impossibile caricare tutte le texture!"), TEXT("Errore fatale"), MB_ICONERROR | MB_OK);
                return -1;
        }

        SetUpBoard(board);

        CWindow.setFramerateLimit(60);

        ConnectToEngine("bin\\stockfish.exe");

        while (CWindow.isOpen()) {
                sf::Event event;

                while (CWindow.pollEvent(event)) {
                        switch (event.type) {
                        case sf::Event::Closed:
                                CWindow.close();
                                break;

                        case sf::Event::KeyPressed:
                                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                                        for (int i = 0; i < 99; i++) {
                                                std::cout << "Mossa " << i + 1 << std::endl;
                                                NextMoveByComputer("computer", &CWindow, board);
                                                DrawBoard(&CWindow, board);

                                                CWindow.setActive();
                                                CWindow.display();
                                        }
                                } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F4)) {
                                        CWindow.close();
                                }
                                break;

                        case sf::Event::KeyReleased:
                                NextMoveByComputer("computer", &CWindow, board);
                                break;
                        
                        case sf::Event::MouseButtonPressed:
                                MovePieceFromCurrentMousePosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), false, &CWindow, board);
                                break;

                        case sf::Event::MouseButtonReleased:
                                MovePieceFromCurrentMousePosition(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), true, &CWindow, board);
                                break;
                        }
                }

                DrawBoard(&CWindow, board);

                CWindow.setActive();
                CWindow.display();
        }

        CloseConnection();
        return 0;
}