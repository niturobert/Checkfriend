#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <math.h>

#include "Connector.hpp"

#define CELL_SIZE 43
#define OFFSET 84

#define BLACK -
#define WHITE +

struct BoardPiece_t {
        int stockfishPieceID;

        sf::Sprite pieceSprite;
};

enum PIECES {
        ROOK = 1,
        KNIGHT = 2,
        BISHOP = 3,
        QUEEN = 4,
        KING = 5,
        PAWN = 6
};

void SetUpBoard(BoardPiece_t[64]);
void MovePieceFromPosToPos(int, int, sf::RenderWindow *, BoardPiece_t *);
void MoveFromChessNotation(std::string, sf::RenderWindow *, BoardPiece_t*);
void NextMoveByComputer(std::string = "computer", sf::RenderWindow * = nullptr, BoardPiece_t * = nullptr);
void MovePieceFromCurrentMousePosition(sf::Vector2f, bool, sf::RenderWindow *, BoardPiece_t*);
int GetCellIdFromPosition(sf::Vector2f);
sf::Vector2f GetPositionFromCellId(int);
std::string ConvertMoveToCoordinateNotation(int, int);

bool MovePieceFromMouse(sf::Window window, sf::Vector2f VectorStartToEndPosition) {
        return true;
}

void SetUpBoard(BoardPiece_t board[64]) {
        // Setting up Black's pieces.
        board[0].stockfishPieceID = BLACK ROOK;
        board[1].stockfishPieceID = BLACK KNIGHT;
        board[2].stockfishPieceID = BLACK BISHOP;
        board[3].stockfishPieceID = BLACK QUEEN;
        board[4].stockfishPieceID = BLACK KING;
        board[5].stockfishPieceID = BLACK BISHOP;
        board[6].stockfishPieceID = BLACK KNIGHT;
        board[7].stockfishPieceID = BLACK ROOK;

        for (int i = 0; i < 8; i++) {
                board[8 + i].stockfishPieceID = BLACK PAWN;
        }

        // Setting up White's pieces.
        board[63-7].stockfishPieceID = WHITE ROOK;
        board[63-6].stockfishPieceID = WHITE KNIGHT;
        board[63-5].stockfishPieceID = WHITE BISHOP;
        board[63-4].stockfishPieceID = WHITE QUEEN;
        board[63-3].stockfishPieceID = WHITE KING;
        board[63-2].stockfishPieceID = WHITE BISHOP;
        board[63-1].stockfishPieceID = WHITE KNIGHT;
        board[63].stockfishPieceID  = WHITE ROOK;

        for (int i = 0; i < 8; i++) {
                board[63 - 8 - i].stockfishPieceID = WHITE PAWN;
        }
}

void MovePieceFromPosToPos(int old_position, int new_position, sf::RenderWindow *window, BoardPiece_t *board) {
        if (old_position == new_position) { return; }
        board[new_position].pieceSprite = board[old_position].pieceSprite;
        board[new_position].stockfishPieceID = board[old_position].stockfishPieceID;
        board[old_position].pieceSprite = sf::Sprite();
        board[old_position].stockfishPieceID = 0;
}

void MoveFromChessNotation(std::string move, sf::RenderWindow *window, BoardPiece_t *board) {
        int old_pos = (move[0] - 'a') + (('8' - move[1]) * 8);
        int new_pos = (move[2] - 'a') + (('8' - move[3]) * 8);

        MovePieceFromPosToPos(old_pos, new_pos, window, board);
}

void NextMoveByComputer(std::string next_move, sf::RenderWindow *window, BoardPiece_t *board) {
        static std::string moves = "";

        std::string new_move = next_move;

        if (next_move == "computer") {
                std::cout << "Next move is being calculated by the computer." << std::endl;
                std::string next_move = getNextMove(moves);
                std::cout << "Computer's choice: " << next_move << std::endl;

                new_move = next_move;
        }

        moves += " " + new_move;

        std::cout << "Moves: " << moves << std::endl;

        MoveFromChessNotation(new_move, window, board);
}

void MovePieceFromCurrentMousePosition(sf::Vector2f position, bool final, sf::RenderWindow *window, BoardPiece_t *board) {
        static int static_cell = 0;

        if (final) {
                NextMoveByComputer(
                        ConvertMoveToCoordinateNotation(
                                static_cell,
                                GetCellIdFromPosition(position)
                        ),
                        window,
                        board
                );
        } else {
                static_cell = GetCellIdFromPosition(position);
        }
}

int GetCellIdFromPosition(sf::Vector2f position) {
        position.x = position.x - OFFSET;
        position.y = position.y - OFFSET;
        
        position.x = (int) position.x / CELL_SIZE;
        position.y = (int) position.y / CELL_SIZE;

        int cell_id = position.y * 8 + position.x;

        return cell_id;
}

sf::Vector2f GetPositionFromCellId(int cell_id) {
        return sf::Vector2f(OFFSET + (cell_id % 8) * CELL_SIZE, OFFSET + (cell_id / 8) * CELL_SIZE);
}

std::string ConvertMoveToCoordinateNotation(int old_position, int new_position) {
        std::string cols = "hgfedcba";

        return cols[7 - old_position % 8]
             + std::to_string(8 - old_position / 8)
             + cols[7 - new_position % 8]
             + std::to_string(8 - new_position / 8);
}