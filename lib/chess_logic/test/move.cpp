#include <catch2/catch_test_macros.hpp>

#include "chess_move.h"

TEST_CASE(
    "ChessMove: constructor with from and to should create a valid move") {
  ChessPosition from('a', 1);
  ChessPosition to('b', 2);
  ChessMove move(from, to);
  REQUIRE(move.getFrom().toData() == 0x11);
  REQUIRE(move.getTo().toData() == 0x22);
}

TEST_CASE(
    "ChessMove: constructor with from, to, and piece should create a valid "
    "move") {
  ChessPosition from('a', 1);
  ChessPosition to('b', 2);

  SECTION("Pawn") {
    ChessMove move(from, to, ChessPieceType::Pawn);
    REQUIRE(move.getPiece() == ChessPieceType::Pawn);
  }

  SECTION("Knight") {
    ChessMove move(from, to, ChessPieceType::Knight);
    REQUIRE(move.getPiece() == ChessPieceType::Knight);
  }

  SECTION("Bishop") {
    ChessMove move(from, to, ChessPieceType::Bishop);
    REQUIRE(move.getPiece() == ChessPieceType::Bishop);
  }

  SECTION("Rook") {
    ChessMove move(from, to, ChessPieceType::Rook);
    REQUIRE(move.getPiece() == ChessPieceType::Rook);
  }

  SECTION("Queen") {
    ChessMove move(from, to, ChessPieceType::Queen);
    REQUIRE(move.getPiece() == ChessPieceType::Queen);
  }

  SECTION("King") {
    ChessMove move(from, to, ChessPieceType::King);
    REQUIRE(move.getPiece() == ChessPieceType::King);
  }
}

TEST_CASE(
    "ChessMove: constructor with from, to, piece, and type should create a "
    "valid move") {
  ChessPosition from('a', 1);
  ChessPosition to('b', 2);
  ChessPieceType piece = ChessPieceType::Pawn;

  SECTION("Normal") {
    ChessMove move(from, to, piece, ChessMoveType::Normal);
    REQUIRE(move.getType() == ChessMoveType::Normal);
  }

  SECTION("Capture") {
    ChessMove move(from, to, piece, ChessMoveType::Capture);
    REQUIRE(move.getType() == ChessMoveType::Capture);
  }

  SECTION("Castling") {
    ChessMove move(from, to, piece, ChessMoveType::Castling);
    REQUIRE(move.getType() == ChessMoveType::Castling);
  }

  SECTION("Check") {
    ChessMove move(from, to, piece, ChessMoveType::Check);
    REQUIRE(move.getType() == ChessMoveType::Check);
  }

  SECTION("Checkmate") {
    ChessMove move(from, to, piece, ChessMoveType::Checkmate);
    REQUIRE(move.getType() == ChessMoveType::Checkmate);
  }

  SECTION("Promotion") {
    ChessMove move(from, to, piece, ChessMoveType::Promotion);
    REQUIRE(move.getType() == ChessMoveType::Promotion);
  }

  SECTION("EnPassant") {
    ChessMove move(from, to, piece, ChessMoveType::EnPassant);
    REQUIRE(move.getType() == ChessMoveType::EnPassant);
  }
}

TEST_CASE("ChessMove: isValid should return true if the move is valid") {
  SECTION("Pawn normal first move x1") {
    ChessPosition from('a', 2);
    ChessPosition to('a', 3);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Pawn normal first move x2") {
    ChessPosition from('a', 2);
    ChessPosition to('a', 4);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Pawn normal move") {
    ChessPosition from('c', 5);
    ChessPosition to('c', 6);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Pawn capture") {
    ChessPosition from('c', 5);
    ChessPosition to('d', 6);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Capture);
    REQUIRE(move.isValid());
  }

  SECTION("Pawn en passant") {
    ChessPosition from('c', 5);
    ChessPosition to('d', 6);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::EnPassant);
    REQUIRE(move.isValid());
  }

  SECTION("Knight normal move") {
    ChessPosition from('b', 1);
    ChessPosition to('c', 3);
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Knight capture") {
    ChessPosition from('b', 1);
    ChessPosition to('c', 3);
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Capture);
    REQUIRE(move.isValid());
  }

  SECTION("Bishop normal move") {
    ChessPosition from('c', 1);
    ChessPosition to('f', 4);
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Bishop capture") {
    ChessPosition from('c', 1);
    ChessPosition to('f', 4);
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Capture);
    REQUIRE(move.isValid());
  }

  SECTION("Rook normal move") {
    ChessPosition from('a', 1);
    ChessPosition to('a', 5);
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Rook capture") {
    ChessPosition from('a', 1);
    ChessPosition to('a', 5);
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Capture);
    REQUIRE(move.isValid());
  }

  SECTION("Queen normal move") {
    ChessPosition from('d', 1);
    ChessPosition to('d', 5);
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("Queen capture") {
    ChessPosition from('d', 1);
    ChessPosition to('d', 5);
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Capture);
    REQUIRE(move.isValid());
  }

  SECTION("King normal move") {
    ChessPosition from('e', 1);
    ChessPosition to('e', 2);
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Normal);
    REQUIRE(move.isValid());
  }

  SECTION("King capture") {
    ChessPosition from('e', 1);
    ChessPosition to('e', 2);
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Capture);
    REQUIRE(move.isValid());
  }

  SECTION("Castling") {
    ChessPosition from('e', 1);
    ChessPosition to('g', 1);
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Castling);
    REQUIRE(move.isValid());
  }

  SECTION("Promotion to Queen") {
    ChessPosition from('a', 7);
    ChessPosition to('a', 8);
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Promotion);
    REQUIRE(move.isValid());
  }

  SECTION("Promotion to Rook") {
    ChessPosition from('a', 7);
    ChessPosition to('a', 8);
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Promotion);
    REQUIRE(move.isValid());
  }

  SECTION("Promotion to Bishop") {
    ChessPosition from('a', 7);
    ChessPosition to('a', 8);
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Promotion);
    REQUIRE(move.isValid());
  }

  SECTION("Promotion to Knight") {
    ChessPosition from('a', 7);
    ChessPosition to('a', 8);
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Promotion);
    REQUIRE(move.isValid());
  }
}

TEST_CASE("ChessMove: isValid should return false if the move is invalid") {
  SECTION("Pawn capture as normal move") {
    ChessPosition from('a', 1);
    ChessPosition to('a', 2);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Pawn normal move x3") {
    ChessPosition from('a', 2);
    ChessPosition to('a', 5);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("En passant from invalid position") {
    ChessPosition from('a', 1);
    ChessPosition to('a', 2);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::EnPassant);
    REQUIRE(!move.isValid());
  }

  SECTION("Pawn normal move x2 from invalid position") {
    ChessPosition from('a', 4);
    ChessPosition to('a', 6);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Knight horizontal move") {
    ChessPosition from('b', 1);
    ChessPosition to('d', 1);
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Knight vertical move") {
    ChessPosition from('b', 1);
    ChessPosition to('b', 3);
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Bishop horizontal move") {
    ChessPosition from('c', 1);
    ChessPosition to('f', 1);
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Bishop vertical move") {
    ChessPosition from('c', 1);
    ChessPosition to('c', 4);
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Rook diagonal move") {
    ChessPosition from('a', 1);
    ChessPosition to('d', 4);
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Queen knight move") {
    ChessPosition from('d', 1);
    ChessPosition to('e', 3);
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("King more than one square move") {
    ChessPosition from('e', 1);
    ChessPosition to('e', 3);
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Normal);
    REQUIRE(!move.isValid());
  }

  SECTION("Castling from invalid position") {
    ChessPosition from('e', 2);
    ChessPosition to('g', 2);
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Castling);
    REQUIRE(!move.isValid());
  }

  SECTION("Promotion from invalid position") {
    ChessPosition from('a', 1);
    ChessPosition to('a', 8);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Promotion);
    REQUIRE(!move.isValid());
  }

  SECTION("Promotion to invalid piece") {
    ChessPosition from('a', 7);
    ChessPosition to('a', 8);
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Promotion);
    REQUIRE(!move.isValid());
  }
}

TEST_CASE("ChessMove: operator== should return true if the moves are equal") {
  ChessPosition from('a', 1);
  ChessPosition to('b', 2);
  ChessMove move1(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
  ChessMove move2(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
  REQUIRE(move1 == move2);
}

TEST_CASE(
    "ChessMove: operator== should return false if the moves are not equal") {
  ChessPosition from1('a', 1);
  ChessPosition to1('b', 2);
  ChessMove move1(from1, to1, ChessPieceType::Pawn, ChessMoveType::Normal);

  ChessPosition from2('a', 2);
  ChessPosition to2('b', 2);
  ChessMove move2(from2, to2, ChessPieceType::Pawn, ChessMoveType::Normal);
  REQUIRE(!(move1 == move2));
}

TEST_CASE(
    "ChessMode: operator!= should return true if the moves are not equal") {
  ChessPosition from1('a', 1);
  ChessPosition to1('b', 2);
  ChessMove move1(from1, to1, ChessPieceType::Pawn, ChessMoveType::Normal);

  ChessPosition from2('a', 2);
  ChessPosition to2('b', 2);
  ChessMove move2(from2, to2, ChessPieceType::Pawn, ChessMoveType::Normal);
  REQUIRE(move1 != move2);
}

TEST_CASE("ChessMove: operator!= should return false if the moves are equal") {
  ChessPosition from('a', 1);
  ChessPosition to('b', 2);
  ChessMove move1(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
  ChessMove move2(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
  REQUIRE(!(move1 != move2));
}

TEST_CASE(
    "ChessMove: toString should return a valid algebraic notation for pawn") {
  ChessPosition from('a', 2);
  ChessPosition to('a', 3);

  SECTION("Normal move") {
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Normal);
    REQUIRE(move.toString() == "Pa2a3");
  }

  SECTION("Capture move") {
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::Capture);
    REQUIRE(move.toString() == "Pa2xa3");
  }

  SECTION("En passant move") {
    ChessMove move(from, to, ChessPieceType::Pawn, ChessMoveType::EnPassant);
    REQUIRE(move.toString() == "Pa2a3e.p.");
  }

  SECTION("Promotion move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Promotion);
    REQUIRE(move.toString() == "Pa2a3=Q");
  }

  SECTION("Promotion capture move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Promotion);
    REQUIRE(move.toString() == "Pa2a3=Q");
  }

  SECTION("Castling move") {
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Castling);
    REQUIRE(move.toString() == "O-O");
  }

  SECTION("Castling queen side move") {
    ChessPosition from('e', 1);
    ChessPosition to('c', 1);
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Castling);
    REQUIRE(move.toString() == "O-O-O");
  }
}

TEST_CASE(
    "ChessMove: toString should return a valid algebraic notation for "
    "knight") {
  ChessPosition from('b', 1);
  ChessPosition to('c', 3);

  SECTION("Normal move") {
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Normal);
    REQUIRE(move.toString() == "Nb1c3");
  }

  SECTION("Capture move") {
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Capture);
    REQUIRE(move.toString() == "Nb1xc3");
  }

  SECTION("Check move") {
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Check);
    REQUIRE(move.toString() == "Nb1c3+");
  }

  SECTION("Checkmate move") {
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Checkmate);
    REQUIRE(move.toString() == "Nb1c3#");
  }

  SECTION("Promotion move") {
    ChessMove move(from, to, ChessPieceType::Knight, ChessMoveType::Promotion);
    REQUIRE(move.toString() == "Nb1c3=N");
  }
}

TEST_CASE(
    "ChessMove: toString should return a valid algebraic notation for bishop") {
  ChessPosition from('c', 1);
  ChessPosition to('f', 4);

  SECTION("Normal move") {
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Normal);
    REQUIRE(move.toString() == "Bc1f4");
  }

  SECTION("Capture move") {
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Capture);
    REQUIRE(move.toString() == "Bc1xf4");
  }

  SECTION("Check move") {
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Check);
    REQUIRE(move.toString() == "Bc1f4+");
  }

  SECTION("Checkmate move") {
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Checkmate);
    REQUIRE(move.toString() == "Bc1f4#");
  }

  SECTION("Promotion move") {
    ChessMove move(from, to, ChessPieceType::Bishop, ChessMoveType::Promotion);
    REQUIRE(move.toString() == "Bc1f4=B");
  }
}

TEST_CASE(
    "ChessMove: toString should return a valid algebraic notation for rook") {
  ChessPosition from('a', 1);
  ChessPosition to('a', 5);

  SECTION("Normal move") {
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Normal);
    REQUIRE(move.toString() == "Ra1a5");
  }

  SECTION("Capture move") {
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Capture);
    REQUIRE(move.toString() == "Ra1xa5");
  }

  SECTION("Check move") {
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Check);
    REQUIRE(move.toString() == "Ra1a5+");
  }

  SECTION("Checkmate move") {
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Checkmate);
    REQUIRE(move.toString() == "Ra1a5#");
  }

  SECTION("Promotion move") {
    ChessMove move(from, to, ChessPieceType::Rook, ChessMoveType::Promotion);
    REQUIRE(move.toString() == "Ra1a5=R");
  }
}

TEST_CASE(
    "ChessMove: toString should return a valid algebraic notation for queen") {
  ChessPosition from('d', 1);
  ChessPosition to('d', 5);

  SECTION("Normal move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Normal);
    REQUIRE(move.toString() == "Qd1d5");
  }

  SECTION("Capture move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Capture);
    REQUIRE(move.toString() == "Qd1xd5");
  }

  SECTION("Check move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Check);
    REQUIRE(move.toString() == "Qd1d5+");
  }

  SECTION("Checkmate move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Checkmate);
    REQUIRE(move.toString() == "Qd1d5#");
  }

  SECTION("Promotion move") {
    ChessMove move(from, to, ChessPieceType::Queen, ChessMoveType::Promotion);
    REQUIRE(move.toString() == "Qd1d5=Q");
  }
}

TEST_CASE(
    "ChessMove: toString should return a valid algebraic notation for king") {
  ChessPosition from('e', 1);
  ChessPosition to('e', 2);

  SECTION("Normal move") {
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Normal);
    REQUIRE(move.toString() == "Ke1e2");
  }

  SECTION("Capture move") {
    ChessMove move(from, to, ChessPieceType::King, ChessMoveType::Capture);
    REQUIRE(move.toString() == "Ke1xe2");
  }
}
