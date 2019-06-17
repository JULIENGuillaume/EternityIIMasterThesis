//
// Created by Guillaume on 03/06/2019.
//

#pragma once
#ifndef ETERNITYII_IBOARD_HH
#define ETERNITYII_IBOARD_HH

#include <Size2D.hh>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <Position2D.hh>
#include <memory>
#include "IPiece.hh"

namespace etm {
	/**
	 * Interface abstracting the logic of the board. It allows to retrieve information,
	 * play the game, add state observers and evaluate the final result. It also store
	 * all information relevant to pieces.
	 *
	 * @author Guillaume Julien
	 * @date 04 June 2019
	 *
	 * @interface IBoard IBoard.hh "IBoard.hh"
	 */
	class IBoard {
	public:
		/**
		 * Virtual default destructor.
		 */
		virtual ~IBoard() = default;

		/**
		 * Get the size of the board, in a width and height format (default should be 16x16).
		 *
		 * @return A Size2D class containing the size information of the current board.
		 */
		virtual Size2D const &getSize() const = 0;

		/**
		 * Get the dimension of the pieces of the board, which represent the number of  edges that connect with neighbours (default should be 4).
		 *
		 * @return An uint32_t representing the dimension of the pieces.
		 */
		virtual uint32_t getPieceDimension() const = 0;

		/**
		 * Get the list of pieces on the board. The list is ordered from top left to bottom right of the board.
		 * It contain the id of each piece, but not its current rotation. 0 mark an empty spot.
		 *
		 * @return A vector of uint32_t containing the ordered pieces present on the board.
		 */
		virtual std::vector<uint32_t> const &getCurrentBoardPieces() const = 0;

		/**
		 * Get the list of pieces present on the board.
		 *
		 * @return An unordered_set containing the ids of the pieces present on the board.
		 */
		virtual std::unordered_set<uint32_t> const &getPlayedPieces() const = 0;

		/**
		 * Get the list of position of the pieces present on the board.
		 *
		 * @return An unordered_map mapping the id of a piece to its position on the board.
		 */
		virtual std::unordered_map<uint32_t, uint32_t> const &getPlayedPiecesPosition() const = 0;

		/**
		 * Get the list of pieces that are not currently on the board.
		 *
		 * @return An unordered_set containing the ids of the pieces absent from the board.
		 */
		virtual std::unordered_set<uint32_t> const &getRemainingPieces() const = 0;

		/**
		 * Get the list of rotations for the pieces present on the board. The rotation is clockwise.
		 * The value of the rotation is comprised between 0 and the value returned by getPieceDimension().
		 *
		 * @return An unordered_map mapping the id of a piece to its current rotation.
		 */
		virtual std::unordered_map<uint32_t, uint32_t> const &getPiecesRotation() const = 0;

		/**
		 * Get the information of a specific piece.
		 *
		 * @param pieceId	The id of the piece.
		 * @return A const reference to an IPiece interface containing the information of the piece.
		 *
		 * @throw NonExistingPieceException	The piece id is invalid.
		 */
		virtual IPiece const &getPiece(uint32_t pieceId) const = 0;

		/**
		 * Get the full mapping of id to pieces, both played and remaining.
		 *
		 * @return An unordered map of const references to IPiece interfaces.
		 */
		virtual std::unordered_map<uint32_t, IPiece const &> const &getAllPieces() const = 0;

		/**
		 * Place a piece on the board at the specified position.
		 *
		 * @param pieceId 		The id of the piece to be placed.
		 * @param pos 			The position at which the piece will be placed.
		 * @param forceRemove	If true and another piece is present at the position, call removePiece() on it first.
		 * 
		 * @throw OutOfBoardException		The position is invalid.
		 * @throw NonExistingPieceException	The piece id is invalid.
		 * @throw PieceOverlapException		forceRemove is set to false, and a piece is already at pos.
		 */
		virtual void placePiece(uint32_t pieceId, Position2D const &pos, bool forceRemove) = 0;

		/**
 		 * Place a piece on the board at the specified position.
		 *
		 * @param pieceId 		The id of the piece to be placed.
		 * @param pos 			The position at which the piece will be placed.
		 * @param forceRemove	If true and another piece is present at the position, call removePiece() on it first.
		 *
		 * @throw OutOfBoardException		The position is invalid.
		 * @throw NonExistingPieceException	The piece id is invalid.
		 * @throw PieceOverlapException		forceRemove is set to false, and a piece is already at pos.
 		 */
		virtual void placePiece(uint32_t pieceId, uint32_t pos, bool forceRemove) = 0;

		/**
		 * Remove a piece from a specified position. Succeed even if there is no piece at the position.
		 *
		 * @param pos	The position from which the piece will be removed
		 *
		 * @throw OutOfBoardException		The position is invalid.
		 */
		virtual void removePiece(Position2D const &pos) = 0;

		/**
		 * Remove a piece from a specified position. Succeed even if there is no piece at the position.
		 *
		 * @param pos	The position from which the piece will be removed
		 *
		 * @throw OutOfBoardException		The position is invalid.
		 */
		virtual void removePiece(uint32_t pos) = 0;

		/**
		 * Rotate a piece by a specified amount of clockwise step.
		 *
		 * @param pos 		The position of the piece to rotate.
		 * @param rotation	The value of the rotation.
		 *
		 * @throw OutOfBoardException		The position is invalid.
		 * @throw NonExistingPieceException	There is no piece to rotate at the position.
		 */
		virtual void rotatePiece(Position2D const &pos, uint32_t rotation) = 0;

		/**
		 * Rotate a piece by a specified amount of clockwise step.
		 *
		 * @param pos 		The position of the piece to rotate.
		 * @param rotation	The value of the rotation.
		 *
		 * @throw OutOfBoardException		The position is invalid.
		 * @throw NonExistingPieceException	There is no piece to rotate at the position.
		 */
		virtual void rotatePiece(uint32_t pos, uint32_t rotation) = 0;

		/**
		 * Convert a Position2D class to the linear position used on the board.
		 *
		 * @param pos The standard format position.
		 * @return An uint32_t representing the equivalent linear position.
		 */
		virtual uint32_t getLinearPosition(Position2D const& pos) const = 0;

		/**
		 * Return a vector containing the edges of the piece at pos, applying the current rotation on them
		 *
		 * @param pos The position from which we get the edges
		 * @return A vector of size piece dimension containing ordered edges
		 */
		virtual std::vector<uint32_t> getRotatedEdges(Position2D const& pos) const = 0;

		/**
		 * Return a vector containing the edges of the piece at pos, applying the current rotation on them
		 *
		 * @param pos The position from which we get the edges
		 * @return A vector of size piece dimension containing ordered edges
		 */
		virtual std::vector<uint32_t> getRotatedEdges(uint32_t const& pos) const = 0;

		/**
		 * Validate the board by checking the number of pieces, their uniqueness, that no invalid id or edges are present
		 * and basic solvability properties.
		 *
		 * @throw BoardValidationException	Detail what failed during validation
		 */
		virtual void validate() const = 0;

		/**
		 * Get the default edge color of the board for the outline of the board.
		 *
		 * @return an uint32_t containing the default color
		 */
		virtual uint32_t getDefaultEdgeColor() const = 0;
	};
}

#endif //ETERNITYII_IBOARD_HH
