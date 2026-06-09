import React, { useEffect, useRef, useState } from 'react';

// Constants matching the C++ implementation
const ROWS = 20;
const COLS = 10;
const BLOCK_SIZE = 30;

// Tetromino definitions (same as in Tetris.cpp)
const SHAPES: number[][][] = [
  // I
  [[1, 1, 1, 1]],
  // O
  [[1, 1], [1, 1]],
  // T
  [[0, 1, 0], [1, 1, 1]],
  // S
  [[0, 1, 1], [1, 1, 0]],
  // Z
  [[1, 1, 0], [0, 1, 1]],
  // J
  [[1, 0, 0], [1, 1, 1]],
  // L
  [[0, 0, 1], [1, 1, 1]]
];
const COLORS = ['cyan', 'yellow', 'purple', 'green', 'red', 'blue', 'orange'];

function rotate(shape: number[][]): number[][] {
  const n = shape.length;
  const m = shape[0].length;
  const rotated: number[][] = Array.from({ length: m }, () => Array(n).fill(0));
  for (let i = 0; i < n; i++) {
    for (let j = 0; j < m; j++) {
      rotated[j][n - 1 - i] = shape[i][j];
    }
  }
  return rotated;
}

export default function TetrisGame() {
  const canvasRef = useRef<HTMLCanvasElement>(null);
  const [board, setBoard] = useState<number[][]>(Array.from({ length: ROWS }, () => Array(COLS).fill(0)));
  const [currentShape, setCurrentShape] = useState<number[][]>(SHAPES[0]);
  const [shapeColorIndex, setShapeColorIndex] = useState<number>(0);
  const [pos, setPos] = useState<{ x: number; y: number }>({ x: 3, y: -1 }); // start above board

  // Draw everything on canvas
  const draw = () => {
    const canvas = canvasRef.current;
    if (!canvas) return;
    const ctx = canvas.getContext('2d');
    if (!ctx) return;
    ctx.clearRect(0, 0, COLS * BLOCK_SIZE, ROWS * BLOCK_SIZE);

    // Draw settled blocks
    for (let r = 0; r < ROWS; r++) {
      for (let c = 0; c < COLS; c++) {
        if (board[r][c]) {
          ctx.fillStyle = COLORS[board[r][c] - 1];
          ctx.fillRect(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
          ctx.strokeRect(c * BLOCK_SIZE, r * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        }
      }
    }

    // Draw current falling piece
    for (let i = 0; i < currentShape.length; i++) {
      for (let j = 0; j < currentShape[i].length; j++) {
        if (!currentShape[i][j]) continue;
        const x = pos.x + j;
        const y = pos.y + i;
        ctx.fillStyle = COLORS[shapeColorIndex];
        ctx.fillRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
        ctx.strokeRect(x * BLOCK_SIZE, y * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
      }
    }
  };

  // Collision check
  const isValid = (shape: number[][], offsetX: number, offsetY: number) => {
    for (let i = 0; i < shape.length; i++) {
      for (let j = 0; j < shape[i].length; j++) {
        if (!shape[i][j]) continue;
        const x = offsetX + j;
        const y = offsetY + i;
        if (x < 0 || x >= COLS) return false;
        if (y >= ROWS) return false;
        if (y >= 0 && board[y][x]) return false;
      }
    }
    return true;
  };

  // Lock piece into board and spawn new one
  const lockPiece = () => {
    const newBoard = board.map(row => [...row]);
    for (let i = 0; i < currentShape.length; i++) {
      for (let j = 0; j < currentShape[i].length; j++) {
        if (!currentShape[i][j]) continue;
        const x = pos.x + j;
        const y = pos.y + i;
        if (y >= 0) newBoard[y][x] = shapeColorIndex + 1;
      }
    }
    setBoard(newBoard);
    spawnNew();
  };

  // Spawn a random piece
  const spawnNew = () => {
    const idx = Math.floor(Math.random() * SHAPES.length);
    setCurrentShape(SHAPES[idx]);
    setShapeColorIndex(idx);
    setPos({ x: 3, y: -SHAPES[idx].length });
  };

  // Game loop – drop every 500ms
  useEffect(() => {
    const interval = setInterval(() => {
      if (isValid(currentShape, pos.x, pos.y + 1)) {
        setPos(p => ({ ...p, y: p.y + 1 }));
      } else {
        lockPiece();
      }
    }, 500);
    return () => clearInterval(interval);
  }, [currentShape, pos]);

  // Keyboard controls
  useEffect(() => {
    const handle = (e: KeyboardEvent) => {
      if (e.key === 'ArrowLeft' && isValid(currentShape, pos.x - 1, pos.y)) setPos(p => ({ ...p, x: p.x - 1 }));
      if (e.key === 'ArrowRight' && isValid(currentShape, pos.x + 1, pos.y)) setPos(p => ({ ...p, x: p.x + 1 }));
      if (e.key === 'ArrowDown' && isValid(currentShape, pos.x, pos.y + 1)) setPos(p => ({ ...p, y: p.y + 1 }));
      if (e.key === 'ArrowUp') {
        const rotated = rotate(currentShape);
        if (isValid(rotated, pos.x, pos.y)) setCurrentShape(rotated);
      }
    };
    window.addEventListener('keydown', handle);
    return () => window.removeEventListener('keydown', handle);
  }, [currentShape, pos]);

  // Redraw on state change
  useEffect(() => draw(), [board, currentShape, pos]);

  return (
    <div style={{ display: 'flex', justifyContent: 'center' }}>
      <canvas ref={canvasRef} width={COLS * BLOCK_SIZE} height={ROWS * BLOCK_SIZE} style={{ border: '1px solid #000' }} />
    </div>
  );
}
