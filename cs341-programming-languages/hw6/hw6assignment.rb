# University of Washington, Programming Languages, Homework 6, hw6runner.rb

# This is the only file you turn in, so do not modify the other files as
# part of your solution.

class MyPiece < Piece

  # @override
  # Choose the next piece
  def self.next_piece (board)
    Piece.new(All_My_Pieces.sample, board)
  end

  # Creates the cheat piece
  def self.cheat (board)
    Piece.new([[[0, 0]]], board)
  end

  All_My_Pieces = All_Pieces +
    [[[[-2, 0], [-1, 0], [0, 0], [1, 0], [2, 0]], [[0, -2], [0, -1], [0, 0], [0, 1], [0, 2]]]] +
    [rotations([[0, 0], [1, 0], [0, 1], [1, 1], [2, 1]])] +
    [rotations([[0, 0], [0, 1], [1, 1]])]

end

class MyBoard < Board

  def initialize (game)
    super
    @current_block = MyPiece.next_piece(self)
    @cheat_pieces  = 0
  end

  # @override
  # Gets the next piece
  def next_piece
    if @cheat_pieces > 0
      @current_block = MyPiece.cheat(self)
      @cheat_pieces -= 1
    else
      @current_block = MyPiece.next_piece(self)
    end

    @current_pos = nil
  end

  # Rotates the current piece 180 degress
  def rotate_180
    self.rotate_clockwise
    self.rotate_clockwise
  end

  # Cheat game
  def cheat
    if @cheat_pieces == 0 and @score >= 100
      @cheat_pieces += 1
      @score        -= 100
    end
  end

  # @override
  # Gets the information from the current piece about where it is and uses this
  # to store the piece on the board itself.  Then calls remove_filled.
  def store_current
    locations    = @current_block.current_rotation
    displacement = @current_block.position
    last         = locations.size - 1

    (0..last).each { |index|
      current = locations[index];
      @grid[current[1]+displacement[1]][current[0]+displacement[0]] =
      @current_pos[index]
    }

    remove_filled
    @delay = [@delay - 2, 80].max
  end

end

class MyTetris < Tetris

  # @override
  # Creates a canvas and the board that interacts with it
  def set_board
    @canvas = TetrisCanvas.new
    @board  = MyBoard.new(self)

    @canvas.place(
      @board.block_size * @board.num_rows + 3,
      @board.block_size * @board.num_columns + 6,
      24,
      80)

    @board.draw
  end

  # @override
  # Binds keyboard key to functions.
  def key_bindings
    super
    @root.bind('u', proc {@board.rotate_180})
    @root.bind('c', proc {@board.cheat})
  end

  protected :key_bindings

end
