#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>
#include <string>

#include "Chess.hpp"

sf::Texture CTextureBoard;
sf::Texture CTexturePieces[13];

sf::Sprite CSpriteBoard;
sf::Sprite CSpritePieces[13];

bool LoadSprites();

void DrawBoard(sf::RenderWindow *window, BoardPiece_t *);

sf::Sprite GetSpriteFromStockfishId(int);

bool LoadSprites() {
        if (!CTextureBoard.loadFromFile("images\\scacchiera.png")) {
                return false;
        }

        std::string pieces[] = {"rook", "knight", "bishop", "queen", "king", "pawn"};

        // Load BLACK pieces.
        for (int i = 0; i < 6; i++) {
                if (!CTexturePieces[1 + i].loadFromFile("images\\black_" + pieces[i] + ".png")) {
                        std::cerr << "Failed to load a piece!" << std::endl;
                        return false;
                }

                CSpritePieces[1 + i].setTexture(CTexturePieces[1 + i]);
        }
        
        // Load WHITE pieces.
        for (int i = 0; i < 6; i++) {
                if (!CTexturePieces[7 + i].loadFromFile("images\\white_" + pieces[i] + ".png")) {
                        std::cerr << "Failed to load a piece!" << std::endl;
                        return false;
                }

                CSpritePieces[7 + i].setTexture(CTexturePieces[7 + i]);
        }
        
        CSpriteBoard.setTexture(CTextureBoard);

        return true;
}

sf::Sprite GetSpriteFromStockfishId(int pieceId) {
        if (pieceId < 0) {
                return CSpritePieces[-pieceId];
        }

        return CSpritePieces[6 + pieceId];
}

void DrawBoard(sf::RenderWindow *window, BoardPiece_t *board) {
        window->clear();

        window->draw(CSpriteBoard);

        for (int i = 0; i < 64; i++) {
                if (board[i].stockfishPieceID == 0) {
                        continue;
                }
                
                board[i].pieceSprite = GetSpriteFromStockfishId(board[i].stockfishPieceID);
                board[i].pieceSprite.setPosition(GetPositionFromCellId(i));

                window->draw(board[i].pieceSprite);
        }
}